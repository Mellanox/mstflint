#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <stdlib.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <infiniband/verbs.h>
#include <infiniband/mlx5dv.h>
#include <reg_access/reg_access.h>
#include <dlfcn.h>
#include <linux/swab.h>
#include "resource_dump.h"

/* to_mpd always returns the real mlx5_pd object ie the protection domain. */
static inline struct mlx5_pd* to_mpd(struct ibv_pd* ibpd)
{
    struct mlx5_pd* mpd = to_mxxx(pd, pd);

    if (mpd->mprotection_domain)
        return mpd->mprotection_domain;

    return mpd;
}

struct ibv_context* init_my_device_c(char device_name[], void* handler, void* handler_2)
{
    struct ibv_device** d_list = NULL;
    int n = 0;
    int i = 0;
    struct ibv_context* context;
    struct mlx5dv_context_attr* my_context_attr;
    my_context_attr = (struct mlx5dv_context_attr*)malloc(sizeof(struct mlx5dv_context_attr));
    memset(my_context_attr, 0, sizeof(struct mlx5dv_context_attr));

    my_context_attr->flags = MLX5DV_CONTEXT_FLAGS_DEVX;
    my_context_attr->comp_mask = 0;
    f_ibv_get_device_list ibv_get_device_list_func = (f_ibv_get_device_list)dlsym(handler, GET_DEVICE_LIST_FUNC);
    d_list = ibv_get_device_list_func(&n);
    f_ibv_get_device_name ibv_get_device_name_func = (f_ibv_get_device_name)dlsym(handler, GET_DEVICE_NAME_FUNC);
    f_mlx5dv_open_device mlx5dv_open_device_func = (f_mlx5dv_open_device)dlsym(handler_2, OPEN_DEVICE_FUNC);

    if (d_list)
    {
        for (i = 0; i < n; i++)
        {
            if (d_list[i] != NULL && strcmp(ibv_get_device_name_func(d_list[i]), device_name) == 0)
            {
                context = mlx5dv_open_device_func(d_list[i], my_context_attr);
                if (!context)
                {
                    ibv_get_device_name_func(d_list[i]);
                    return NULL;
                }
                return context;
            }
        }
    }
    else
    {
        printf("ibv_get_device_list failed\n");
        return NULL;
    }

    f_ibv_free_device_list ibv_free_device_list_func = (f_ibv_free_device_list)dlsym(handler, FREE_DEVICE_LIST);
    ibv_free_device_list_func(d_list);
    free(my_context_attr);

    return NULL;
}

struct mlx5dv_mkey* create_mkey_c(struct mlx5_mkey* mkey,
                                  struct ibv_context* context,
                                  uint32_t pdn,
                                  uint32_t umem_id,
                                  uint64_t addr,
                                  uint32_t buff_size,
                                  void* handler)
{
    uint32_t out[DEVX_ST_SZ_DW(create_mkey_out)] = {};
    uint32_t in[DEVX_ST_SZ_DW(create_mkey_in)] = {};
    void* mkc;

    DEVX_SET(create_mkey_in, in, opcode, MLX5_CMD_OP_CREATE_MKEY);
    mkc = DEVX_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
    DEVX_SET(mkc, mkc, access_mode_1_0, 0x1);
    DEVX_SET(mkc, mkc, umr_en, 0);
    DEVX_SET(mkc, mkc, pd, pdn);
    DEVX_SET(mkc, mkc, lr, 1);
    DEVX_SET(mkc, mkc, lw, 1);
    DEVX_SET(mkc, mkc, qpn, 0xffffff);
    DEVX_SET64(mkc, mkc, start_addr, addr);
    DEVX_SET64(mkc, mkc, len, buff_size);

    DEVX_SET(create_mkey_in, in, mkey_umem_valid, 1);
    DEVX_SET(create_mkey_in, in, mkey_umem_id, umem_id);

    f_mlx5dv_devx_obj_create mlx5dv_devx_obj_create_func = (f_mlx5dv_devx_obj_create)dlsym(handler, OBJECT_CREATE);

    mkey->devx_obj = mlx5dv_devx_obj_create_func(context, in, sizeof(in), out, sizeof(out));

    if (!mkey->devx_obj)
    {
        printf("mlx5dv_devx_obj_create failed\n");
        printf("status: %u\n", DEVX_GET(create_mkey_out, out, status));
        printf("syndrome: %u\n", DEVX_GET(create_mkey_out, out, syndrome));
        return NULL;
    }

    // printf("MKEY_INDEX: %x\n", DEVX_GET(create_mkey_out, out, mkey_index));
    mkey->dv_mkey.lkey = (DEVX_GET(create_mkey_out, out, mkey_index) << 8) | 0;
    mkey->dv_mkey.rkey = mkey->dv_mkey.lkey;

    return &mkey->dv_mkey;
}

struct ibv_pd* ibv_allocate_pd(struct ibv_context* ctx, void* handler)
{
    f_ibv_alloc_pd ibv_alloc_pd_func = (f_ibv_alloc_pd)dlsym(handler, ALLOCATE_PD);
    struct ibv_pd* st = ibv_alloc_pd_func(ctx);

    return st;
}

struct mlx5dv_devx_umem* mlx5dv_devx_umem_register_ex(struct ibv_context* ctx,
                                                      void* buff,
                                                      uint32_t buff_al_size,
                                                      struct mlx5dv_devx_umem_in* umem_in,
                                                      void* handler)
{
    umem_in->addr = buff;
    umem_in->size = buff_al_size;
    umem_in->access = IBV_ACCESS_LOCAL_WRITE;
    umem_in->pgsz_bitmap = sysconf(_SC_PAGESIZE);
    f_mlx5dv_devx_umem_reg_ex mlx5dv_devx_umem_reg_ex_func = (f_mlx5dv_devx_umem_reg_ex)dlsym(handler, UMEM_REG);

    struct mlx5dv_devx_umem* umem = mlx5dv_devx_umem_reg_ex_func(ctx, umem_in);

    return umem;
}

int generate_lkey(char device_name[], struct result* res)
{
    void* buff;
    struct mlx5dv_mkey* mkey;
    struct mlx5dv_devx_umem_in* umem_in;
    umem_in = (struct mlx5dv_devx_umem_in*)malloc(sizeof(struct mlx5dv_devx_umem_in));
    memset(umem_in, 0, sizeof(struct mlx5dv_devx_umem_in));

    int ret = -1;
    void* handler = dlopen(LIB_VERBS_LINUX_PATH, RTLD_LOCAL | RTLD_LAZY);
    if (!handler)
    {
        handler = dlopen(LIB_VERBS_UBUNTU_PATH, RTLD_LOCAL | RTLD_LAZY);
        if (!handler)
        {
            handler = dlopen(LIB_VERBS_BLUEFIELD_PATH, RTLD_LOCAL | RTLD_LAZY);
            if (!handler)
            {
                printf("Failed to load the libibverbs shared library");
                return ret;
            }
        }
    }

    void* handler_2 = dlopen(LIB_MLX5_LINUX_PATH, RTLD_LOCAL | RTLD_LAZY);
    if (!handler_2)
    {
        handler_2 = dlopen(LIB_MLX5_UBUNTU_PATH, RTLD_LOCAL | RTLD_LAZY);
        if (!handler_2)
        {
            handler_2 = dlopen(LIB_MLX5_BLUEFIELD_PATH, RTLD_LOCAL | RTLD_LAZY);
            if (!handler_2)
            {
                printf("Failed to load the libmlx5 shared library");
                dlclose(handler);
                return ret;
            }
        }
    }

    struct ibv_context* context = init_my_device_c(device_name, handler, handler_2);
    if (!context)
    {
        printf("init_my_device_c failed\n");
        dlclose(handler);
        dlclose(handler_2);
        return ret;
    }

    f_ibv_close_device ibv_close_device_func = (f_ibv_close_device)dlsym(handler, CLOSE_DEVICE);
    struct ibv_pd* pd = ibv_allocate_pd(context, handler);
    if (!pd)
    {
        printf("ibv_alloc_pd failed\n");
        ibv_close_device_func(context);
        dlclose(handler);
        return ret;
    }

    f_ibv_dealloc_pd ibv_dealloc_pd_func = (f_ibv_dealloc_pd)dlsym(handler, DEALLOCATE_PD);
    uint32_t buff_al_size = align(BUFF_SIZE, sysconf(_SC_PAGESIZE));
    if (posix_memalign(&buff, sysconf(_SC_PAGESIZE), buff_al_size))
    {
        printf("posix_memalign failed\n");
        ibv_dealloc_pd_func(pd);
        dlclose(handler);
        return ret;
    }

    memset(buff, 0, buff_al_size);

    struct mlx5dv_devx_umem* umem = mlx5dv_devx_umem_register_ex(context, buff, buff_al_size, umem_in, handler_2);
    if (!umem)
    {
        printf("mlx5dv_devx_umem_reg failed\n");
        free(buff);
        dlclose(handler);
        return ret;
    }

    f_mlx5dv_devx_umem_dereg mlx5dv_devx_umem_dereg_func = (f_mlx5dv_devx_umem_dereg)dlsym(handler, UMEM_DEREG);
    
    struct mlx5_mkey* mmkey = calloc(1, sizeof(*mkey));
    if (!mmkey)
    {
        printf("calloc Failed\n");
        mlx5dv_devx_umem_dereg_func(umem);
        dlclose(handler);
        return ret;
    }

    mkey = create_mkey_c(mmkey, context, to_mpd(pd)->pdn, umem->umem_id, (uint64_t)buff, buff_al_size, handler_2);
    if (!mkey)
    {
        printf("create_mkey failed\n");
        free(mmkey);
        dlclose(handler);
        return ret;
    }
    else
    {
        // printf("Mkey: lkey: %u, rkey: %u\n", mkey->lkey, mkey->rkey);
        // printf("%" PRIu64 "buff2-\n", (uint64_t)buff);
        res->lkey = mkey->lkey;
        res->umem_addr = (uint64_t)buff;
        // printf("%d",res->lkey);
        // printf("%" PRIu64 "\n", res->umem_addr);

        dlclose(handler);
    }

    ret = 0;
    free(umem_in);
    return ret;
}

int bit_extracted_32(uint64_t add, int offset, struct extract* ex)
{
    // FILE *fp;
    // fp = fopen("/tmp/test.log", "w+");
    // fprintf(fp,"0x%llX\n", (long long unsigned int)add);
    // fprintf(fp, "offset-%d\n",offset);
    // fclose(fp);

    uint64_t* p;
    p = (uint64_t*)add;
    // printf("p=%zu\n", (size_t)p);

    p += offset / 2;

    u_int32_t* data = (u_int32_t*)p;
    // printf("val=0x%016x\n",*p);

    // printf("1st-32: 0x%08x\n", __swab32(data[0]));
    // printf("2nd-32: 0x%08x\n", __swab32(data[1]));

    uint32_t idx = (offset + 1) % 2 == 0 ? 1 : 0;
    ex->val = __swab32(data[idx]);

    return 0;
}

int extrac_all(uint64_t add, int size, char* list)
{
    // int i = 0;
    // u_int8_t *p;
    // p =  (u_int8_t*)add;

    memcpy(list, (void*)add, sizeof(char) * size);

    // for( ; i < size; i++)
    // {
    // 	memcpy(list + i, p + i, sizeof(char));
    // }

    return 0;
}

