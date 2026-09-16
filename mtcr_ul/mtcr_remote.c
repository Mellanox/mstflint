/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "mtcr_remote.h"

#ifdef ENABLE_MTCR_REMOTE

#include "mtcr_mf.h" /* full struct mfile_t; mtcr_com_defs.h only forward-declares it */
#include "mtcr_int_defs.h"
#include "mtcr_ul_com.h"
#include "mtcr.h" /* get_force_i2c_address() */
#include "mst_server/client/mst_http_client_c_api.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Remote name grammar (MFT-compatible):
 *
 *     <host>:<port>,<device>
 *
 * with '@' standing for '/' inside <device>. A leading path is stripped, so
 * "/dev/mstflint/10.0.0.7:23108,@dev@mst@x" works too. */
#define PORT_DELIMITER ':'
#define DEVICE_DELIMITER ','

#define MTCR_REMOTE_HOST_SZ 1024

/* Session token dropped by "mstremote add". The directory and the name format
 * have to match mstremote.cpp's RunDir()/TokenPath() exactly - including the
 * $MSTFLINT_RUN_DIR override, which is how the feature is exercised without
 * write access to /var/run. Reading a fixed path here while mstremote honoured
 * the override made every open fail with a 401. */
#define MTCR_REMOTE_TOKEN_DIR "/var/run/mst"
#define MTCR_REMOTE_TOKEN_PATH_FMT "%s/.token.%s_%d"
#define MTCR_REMOTE_TOKEN_ENV "MSTFLINT_REMOTE_TOKEN"
#define MTCR_REMOTE_RUN_DIR_ENV "MSTFLINT_RUN_DIR"

typedef struct mtcr_remote_ctx
{
    mst_http_client_t client;
    char device[DEV_NAME_SZ]; /* device path as the server knows it */
} mtcr_remote_ctx;

static mtcr_remote_ctx* remote_ctx_of(mfile* mf)
{
    ul_ctx_t* ctx = mf ? (ul_ctx_t*)mf->ul_ctx : NULL;

    return ctx ? (mtcr_remote_ctx*)ctx->remote_ctx : NULL;
}

/* ======================================================================== */
/* Name parsing                                                             */
/* ======================================================================== */

/* Split `name` into host / port / device. `host` must hold MTCR_REMOTE_HOST_SZ
 * bytes and `device` DEV_NAME_SZ. Returns 0 on success, -1 otherwise.
 *
 * This is the single definition of "is a remote name": the predicate below is
 * just this parse with the results thrown away, so a name can never be routed
 * to the remote path and then fail to parse. */
static int remote_parse_name(const char* name, char* host, int* port, char* device)
{
    const char* body;
    const char* colon;
    const char* comma;
    size_t host_len;
    size_t i;
    char* end = NULL;
    long parsed_port;

    if (!name)
    {
        return -1;
    }
    body = strrchr(name, '/');
    body = body ? body + 1 : name;

    comma = strchr(body, DEVICE_DELIMITER);
    colon = strchr(body, PORT_DELIMITER);
    /* Both delimiters must be present, in order, and neither the host nor the
     * port may be empty. Local names fall out here: a PCI BDF
     * ("0000:af:00.0") has colons but no comma, and a sysfs path's basename
     * ("config") has neither. */
    if (!comma || !colon || (colon >= comma) || (colon == body) || (comma == colon + 1))
    {
        return -1;
    }

    host_len = (size_t)(colon - body);
    if (host_len >= MTCR_REMOTE_HOST_SZ)
    {
        return -1;
    }
    memcpy(host, body, host_len);
    host[host_len] = '\0';

    parsed_port = strtol(colon + 1, &end, 10);
    if (!end || (end != comma) || (parsed_port <= 0) || (parsed_port > 65535))
    {
        return -1;
    }
    *port = (int)parsed_port;

    /* Device part, with '@' decoded back to '/'. */
    if (!comma[1] || (strlen(comma + 1) >= DEV_NAME_SZ))
    {
        return -1;
    }
    for (i = 0; comma[1 + i]; i++)
    {
        device[i] = (comma[1 + i] == '@') ? '/' : comma[1 + i];
    }
    device[i] = '\0';
    return 0;
}

const char* mtcr_remote_dev_dir(void)
{
    const char* dir = getenv("MSTFLINT_REMOTE_DEV_DIR");

    return (dir && *dir) ? dir : MTCR_REMOTE_DEV_DIR;
}

int mtcr_remote_is_remote_name(const char* name)
{
    char host[MTCR_REMOTE_HOST_SZ];
    char device[DEV_NAME_SZ];
    int port = 0;

    return remote_parse_name(name, host, &port, device) == 0;
}

/* ======================================================================== */
/* Authentication                                                           */
/* ======================================================================== */

static void remote_load_token(mst_http_client_t client, const char* host, int port)
{
    char path[256];
    char token[128];
    const char* env;
    const char* run;
    FILE* f;
    size_t len;

    env = getenv(MTCR_REMOTE_TOKEN_ENV);
    if (env && *env)
    {
        mst_http_client_set_token(client, env);
        return;
    }

    run = getenv(MTCR_REMOTE_RUN_DIR_ENV);
    if (!run || !*run)
    {
        run = MTCR_REMOTE_TOKEN_DIR;
    }

    if (snprintf(path, sizeof(path), MTCR_REMOTE_TOKEN_PATH_FMT, run, host, port) >= (int)sizeof(path))
    {
        return;
    }
    f = fopen(path, "r");
    if (!f)
    {
        return;
    }
    memset(token, 0, sizeof(token));
    if (fgets(token, sizeof(token), f))
    {
        len = strlen(token);
        while (len > 0 && ((token[len - 1] == '\n') || (token[len - 1] == '\r')))
        {
            token[--len] = '\0';
        }
        if (len > 0)
        {
            mst_http_client_set_token(client, token);
        }
    }
    fclose(f);
}

/* ======================================================================== */
/* ul_ctx access functions                                                  */
/* ======================================================================== */

static int mtcr_remote_mread4(mfile* mf, unsigned int offset, u_int32_t* value)
{
    mtcr_remote_ctx* rctx = remote_ctx_of(mf);

    if (!rctx || !value)
    {
        errno = EINVAL;
        return -1;
    }
    if (mst_http_client_read32(rctx->client, rctx->device, offset, value) != 0)
    {
        errno = EIO;
        return -1;
    }
    return 4;
}

static int mtcr_remote_mwrite4(mfile* mf, unsigned int offset, u_int32_t value)
{
    mtcr_remote_ctx* rctx = remote_ctx_of(mf);

    if (!rctx)
    {
        errno = EINVAL;
        return -1;
    }
    if (mst_http_client_write32(rctx->client, rctx->device, offset, value) != 0)
    {
        errno = EIO;
        return -1;
    }
    return 4;
}

static int mtcr_remote_mread4_block(mfile* mf, unsigned int offset, void* data, int byte_len)
{
    mtcr_remote_ctx* rctx = remote_ctx_of(mf);

    if (!rctx || !data || (byte_len <= 0) || (byte_len % 4))
    {
        errno = EINVAL;
        return -1;
    }
    if (mst_http_client_read_block(rctx->client, rctx->device, offset, (u_int32_t*)data, byte_len / 4) != 0)
    {
        errno = EIO;
        return -1;
    }
    return byte_len;
}

static int mtcr_remote_mwrite4_block(mfile* mf, unsigned int offset, void* data, int byte_len)
{
    mtcr_remote_ctx* rctx = remote_ctx_of(mf);

    if (!rctx || !data || (byte_len <= 0) || (byte_len % 4))
    {
        errno = EINVAL;
        return -1;
    }
    if (mst_http_client_write_block(rctx->client, rctx->device, offset, (u_int32_t*)data, byte_len / 4) != 0)
    {
        errno = EIO;
        return -1;
    }
    return byte_len;
}

static int mtcr_remote_mclose(mfile* mf)
{
    ul_ctx_t* ctx = mf ? (ul_ctx_t*)mf->ul_ctx : NULL;
    mtcr_remote_ctx* rctx = remote_ctx_of(mf);

    if (!rctx)
    {
        return 0;
    }
    /* Best-effort: the server drops the device from its table. A failure here
     * is not actionable, the local handle goes away regardless. */
    (void)mst_http_client_close_device(rctx->client, rctx->device);
    mst_http_client_destroy(rctx->client);
    free(rctx);
    if (ctx)
    {
        ctx->remote_ctx = NULL;
    }
    return 0;
}

/* ======================================================================== */
/* Open                                                                     */
/* ======================================================================== */

int mtcr_remote_open(mfile* mf, const char* name)
{
    ul_ctx_t* ctx;
    mtcr_remote_ctx* rctx;
    char host[MTCR_REMOTE_HOST_SZ] = {0};
    int port = 0;

    if (!mf || !mf->ul_ctx)
    {
        errno = EINVAL;
        return -1;
    }
    ctx = (ul_ctx_t*)mf->ul_ctx;

    rctx = (mtcr_remote_ctx*)malloc(sizeof(*rctx));
    if (!rctx)
    {
        errno = ENOMEM;
        return -1;
    }
    memset(rctx, 0, sizeof(*rctx));

    if (remote_parse_name(name, host, &port, rctx->device))
    {
        free(rctx);
        errno = EINVAL;
        return -1;
    }

    rctx->client = mst_http_client_create(host, port);
    if (!rctx->client)
    {
        free(rctx);
        errno = ENOMEM;
        return -1;
    }
    if (!mst_http_client_is_available(rctx->client))
    {
        /* A refused identity is a decision, not an absent server. Reporting it
         * as "connection refused" would send the user looking for a network
         * fault instead of at the key the client just declined - and the client
         * has already explained the refusal on stderr. */
        const char* trust_error = mst_http_client_get_trust_error(rctx->client);

        mst_http_client_destroy(rctx->client);
        free(rctx);
        errno = trust_error ? EACCES : ECONNREFUSED;
        return -1;
    }

    remote_load_token(rctx->client, host, port);

    /* The forced I2C address rides with the open: mtcr consumes it while
     * opening the device and never afterwards, so the server has to receive it
     * here rather than on an already-open handle. */
    if (mst_http_client_open_device(rctx->client, rctx->device, 0, get_force_i2c_address()) != 0)
    {
        /* /health already answered, so the server is there and speaking the
         * protocol; a 401 means the stored session token is stale rather than
         * that the device is missing. Saying so saves the user from hunting a
         * device name that was never the problem. */
        int refused = mst_http_client_get_last_status(rctx->client) == 401;

        if (refused)
        {
            fprintf(stderr, "-E- %s:%d rejected the session token; re-run 'mstremote add %s:%d'\n", host, port, host,
                    port);
        }
        mst_http_client_destroy(rctx->client);
        free(rctx);
        errno = refused ? EACCES : ENODEV;
        return -1;
    }

    ctx->remote_ctx = rctx;
    ctx->mread4 = mtcr_remote_mread4;
    ctx->mwrite4 = mtcr_remote_mwrite4;
    ctx->mread4_block = mtcr_remote_mread4_block;
    ctx->mwrite4_block = mtcr_remote_mwrite4_block;
    ctx->mclose = mtcr_remote_mclose;

    mf->tp = MST_REMOTE;
    mf->flags = MDEVS_TAVOR_CR;
    mf->is_remote = 1;
    mf->address_space = AS_CR_SPACE;
    mf->sock = -1; /* not the legacy socket transport */
    return 0;
}

/* ======================================================================== */
/* Forwarded operations outside the ul_ctx table                            */
/* ======================================================================== */

int mtcr_remote_set_addr_space(mfile* mf, int space)
{
    mtcr_remote_ctx* rctx = remote_ctx_of(mf);

    if (!rctx)
    {
        errno = EINVAL;
        return -1;
    }
    if (mst_http_client_set_address_space(rctx->client, rctx->device, space) != 0)
    {
        return -1;
    }
    /* Mirror locally so mget_addr_space() agrees with the server. */
    mf->address_space = space;
    return 0;
}

int mtcr_remote_maccess_reg(mfile* mf,
                            u_int16_t reg_id,
                            maccess_reg_method_t reg_method,
                            void* reg_data,
                            u_int32_t reg_size,
                            int* reg_status)
{
    mtcr_remote_ctx* rctx = remote_ctx_of(mf);
    int is_write = (reg_method == MACCESS_REG_METHOD_SET) ? 1 : 0;
    int status = 0;
    int rc;

    if (!rctx || !reg_data || !reg_status)
    {
        errno = EINVAL;
        return ME_ERROR;
    }
    rc = mst_http_client_access_register(rctx->client, rctx->device, (u_int32_t)reg_id, (char*)reg_data,
                                         (int)reg_size, is_write, &status);
    /* Propagate the FW status either way so the caller can report the exact
     * device error rather than a generic transport failure. */
    *reg_status = status;
    return (rc == 0) ? ME_OK : ME_ERROR;
}

int mtcr_remote_icmd_send_command(mfile* mf, int opcode, void* data, int data_size, int skip_write)
{
    mtcr_remote_ctx* rctx = remote_ctx_of(mf);
    u_int32_t syndrome = 0;
    int rc;

    if (!rctx || (data_size < 0))
    {
        errno = EINVAL;
        return ME_ERROR;
    }
    rc = mst_http_client_send_icmd(rctx->client, rctx->device, (u_int32_t)opcode, (char*)data, data_size,
                                   skip_write, &syndrome);
    mf->icmd.syndrome = (int)syndrome;
    if (rc == 0)
    {
        return ME_OK;
    }
    return syndrome ? (int)syndrome : ME_ERROR;
}

#else /* !ENABLE_MTCR_REMOTE */

/* Built without --enable-remote: only the name predicate exists, and it never
 * matches, so mopen() treats every name as local. */
const char* mtcr_remote_dev_dir(void)
{
    return MTCR_REMOTE_DEV_DIR;
}

int mtcr_remote_is_remote_name(const char* name)
{
    (void)name;
    return 0;
}

#endif /* ENABLE_MTCR_REMOTE */
