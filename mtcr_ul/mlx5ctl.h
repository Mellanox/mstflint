/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */
#ifndef __MLX5CTL_H__
#define __MLX5CTL_H__

#include <sys/types.h>
#include <endian.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef u8    __u8;
typedef u16   __u16;
typedef u32   __u32;
typedef __u16       __be16;
typedef __u32       __be32;

#define BIT(nr)     (1UL << (nr))
#define BIT_ULL(nr)     (1ULL << (nr))
#define __packed
#define gcm

#include "mlx5_ifc_stub.h"

/* helper macros */
#define __mlx5_nullp(typ) ((struct mlx5_ifc_##typ##_bits *)0)
#define __mlx5_bit_sz(typ, fld) sizeof(__mlx5_nullp(typ)->fld)
#define __mlx5_bit_off(typ, fld) (offsetof(struct mlx5_ifc_##typ##_bits, fld))
#define __mlx5_16_off(typ, fld) (__mlx5_bit_off(typ, fld) / 16)
#define __mlx5_dw_off(typ, fld) (__mlx5_bit_off(typ, fld) / 32)
#define __mlx5_64_off(typ, fld) (__mlx5_bit_off(typ, fld) / 64)
#define __mlx5_16_bit_off(typ, fld) (16 - __mlx5_bit_sz(typ, fld) - (__mlx5_bit_off(typ, fld) & 0xf))
#define __mlx5_dw_bit_off(typ, fld) (32 - __mlx5_bit_sz(typ, fld) - (__mlx5_bit_off(typ, fld) & 0x1f))
#define __mlx5_mask(typ, fld) ((u32)((1ull << __mlx5_bit_sz(typ, fld)) - 1))
#define __mlx5_dw_mask(typ, fld) (__mlx5_mask(typ, fld) << __mlx5_dw_bit_off(typ, fld))
#define __mlx5_mask16(typ, fld) ((u16)((1ull << __mlx5_bit_sz(typ, fld)) - 1))
#define __mlx5_16_mask(typ, fld) (__mlx5_mask16(typ, fld) << __mlx5_16_bit_off(typ, fld))
#define __mlx5_st_sz_bits(typ) sizeof(struct mlx5_ifc_##typ##_bits)

#define MLX5_FLD_SZ_BYTES(typ, fld) (__mlx5_bit_sz(typ, fld) / 8)
#define MLX5_ST_SZ_BYTES(typ) (sizeof(struct mlx5_ifc_##typ##_bits) / 8)
#define MLX5_ST_SZ_DW(typ) (sizeof(struct mlx5_ifc_##typ##_bits) / 32)
#define MLX5_ST_SZ_QW(typ) (sizeof(struct mlx5_ifc_##typ##_bits) / 64)
#define MLX5_UN_SZ_BYTES(typ) (sizeof(union mlx5_ifc_##typ##_bits) / 8)
#define MLX5_UN_SZ_DW(typ) (sizeof(union mlx5_ifc_##typ##_bits) / 32)
#define MLX5_BYTE_OFF(typ, fld) (__mlx5_bit_off(typ, fld) / 8)
#define MLX5_ADDR_OF(typ, p, fld) ((void *)((uint8_t *)(p) + MLX5_BYTE_OFF(typ, fld)))

#define be32_to_cpu(x) be32toh(x)
#define cpu_to_be32(x) htobe32(x)
#define be16_to_cpu(x) be16toh(x)
#define cpu_to_be16(x) htobe16(x)


#define MLX5_GET(typ, p, fld) ((be32_to_cpu(*((__be32 *)(p) +\
	__mlx5_dw_off(typ, fld))) >> __mlx5_dw_bit_off(typ, fld)) & \
	__mlx5_mask(typ, fld))

/* insert a value to a struct */
#define MLX5_SET(typ, p, fld, v) do { \
	u32 _v = v; \
	*((__be32 *)(p) + __mlx5_dw_off(typ, fld)) = \
	cpu_to_be32((be32_to_cpu(*((__be32 *)(p) + __mlx5_dw_off(typ, fld))) & \
		     (~__mlx5_dw_mask(typ, fld))) | (((_v) & __mlx5_mask(typ, fld)) \
		     << __mlx5_dw_bit_off(typ, fld))); \
} while (0)

#endif
