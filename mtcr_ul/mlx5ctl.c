#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include "mlx5ctl.h"
#include "mlx5ctl_ioctl.h"




static int mlx5_cmd_ioctl(int fd, struct mlx5ctl_cmd_inout *cmd)
{
	return ioctl(fd, MLX5CTL_IOCTL_CMD_INOUT, cmd);
}

/*
static void hexdump(void *data, int size)
{
	u8 *p = data;
	int i;

	for (i = 0; i < size; i++)
		printf("%02x ", p[i]);
	printf("\n");
};
*/

int mlx5_control_access_register(int fd, void *data_in,
                                 int size_in, __u16 reg_id,
                                 int method)
{
	int outlen = MLX5_ST_SZ_BYTES(access_register_out) + size_in;
	int inlen = MLX5_ST_SZ_BYTES(access_register_in) + size_in;
	struct mlx5ctl_cmd_inout cmd = {};
	int err = -ENOMEM;
	u32 *out = NULL;
	u32 *in = NULL;
	void *data;

	in = malloc(inlen);
	out = malloc(outlen);
	if (!in || !out)
		goto out;

    memset(in, 0, inlen);
    memset(out, 0, outlen);

	cmd = (struct mlx5ctl_cmd_inout){
		.in = in,
		.inlen = inlen,
		.out = out,
		.outlen = outlen,
	};
	data = MLX5_ADDR_OF(access_register_in, in, register_data);
	memcpy(data, data_in, size_in);

	MLX5_SET(access_register_in, in, opcode, MLX5_CMD_OP_ACCESS_REG);
	MLX5_SET(access_register_in, in, op_mod, method);
	MLX5_SET(access_register_in, in, argument, 0);
	MLX5_SET(access_register_in, in, register_id, reg_id);

	err = mlx5_cmd_ioctl(fd, &cmd);
	if (err)
		goto out;
    data = MLX5_ADDR_OF(access_register_out, out, register_data);
	memcpy(data_in, data, size_in);
out:
	free(out);
	free(in);
	return err;
}
