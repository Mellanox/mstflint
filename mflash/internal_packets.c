    /*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) June 2000, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 *  End of legal section ......................................................
 *
*/
/***
 *** This file was generated at "Mon May 30 15:06:41 2011"
 *** by:
 ***    % csp_pack_unpack.pm ../xml_files/packets_st.csp
 ***/

#include "packets_common.h"
#include "internal_packets_types.h"
#include "internal_packets.h"
#include <stdlib.h>



/*************************************/
/* Name: mfpa
 * Size: 288 bits
 * Description: mfpa */


u_int32_t mfpa_pack(struct mfpa *data_to_pack, u_int8_t *packed_buffer) {
    push_to_buff(packed_buffer, 28, 4, data_to_pack->reserved0);
    push_to_buff(packed_buffer, 26, 2, data_to_pack->fs);
    push_to_buff(packed_buffer, 24, 2, data_to_pack->reserved1);
    push_to_buff(packed_buffer, 23, 1, data_to_pack->p);
    push_to_buff(packed_buffer, 0, 23, data_to_pack->reserved2);
    push_to_buff(packed_buffer, 40, 24, data_to_pack->boot_address);
    push_to_buff(packed_buffer, 32, 8, data_to_pack->reserved3);
    push_to_buff(packed_buffer, 64, 64, data_to_pack->reserved4);
    push_to_buff(packed_buffer, 156, 4, data_to_pack->flash_num);
    push_to_buff(packed_buffer, 128, 28, data_to_pack->reserved5);
    push_to_buff(packed_buffer, 168, 24, data_to_pack->jedec_id);
    push_to_buff(packed_buffer, 160, 8, data_to_pack->reserved6);
    push_to_buff(packed_buffer, 214, 10, data_to_pack->sector_size);
    push_to_buff(packed_buffer, 208, 6, data_to_pack->reserved7);
    push_to_buff(packed_buffer, 200, 8, data_to_pack->block_allighment);
    push_to_buff(packed_buffer, 192, 8, data_to_pack->reserved8);
    push_to_buff_32(packed_buffer, 224, data_to_pack->capability_mask);
    push_to_buff_32(packed_buffer, 256, data_to_pack->reserved9);
    return 36;
}

void mfpa_unpack(struct mfpa *unpacked_data, u_int8_t *buffer_to_unpack) {
    unpacked_data->reserved0 = pop_from_buff(buffer_to_unpack, 28, 4);
    unpacked_data->fs = pop_from_buff(buffer_to_unpack, 26, 2);
    unpacked_data->reserved1 = pop_from_buff(buffer_to_unpack, 24, 2);
    unpacked_data->p = pop_from_buff(buffer_to_unpack, 23, 1);
    unpacked_data->reserved2 = pop_from_buff(buffer_to_unpack, 0, 23);
    unpacked_data->boot_address = pop_from_buff(buffer_to_unpack, 40, 24);
    unpacked_data->reserved3 = pop_from_buff(buffer_to_unpack, 32, 8);
    unpacked_data->reserved4 = pop_from_buff(buffer_to_unpack, 64, 64);
    unpacked_data->flash_num = pop_from_buff(buffer_to_unpack, 156, 4);
    unpacked_data->reserved5 = pop_from_buff(buffer_to_unpack, 128, 28);
    unpacked_data->jedec_id = pop_from_buff(buffer_to_unpack, 168, 24);
    unpacked_data->reserved6 = pop_from_buff(buffer_to_unpack, 160, 8);
    unpacked_data->sector_size = pop_from_buff(buffer_to_unpack, 214, 10);
    unpacked_data->reserved7 = pop_from_buff(buffer_to_unpack, 208, 6);
    unpacked_data->block_allighment = pop_from_buff(buffer_to_unpack, 200, 8);
    unpacked_data->reserved8 = pop_from_buff(buffer_to_unpack, 192, 8);
    unpacked_data->capability_mask = pop_from_buff_32(buffer_to_unpack, 224);
    unpacked_data->reserved9 = pop_from_buff_32(buffer_to_unpack, 256);
}

void mfpa_dump(struct mfpa *data_to_print, FILE *out_port) {
    fprintf(out_port, "mfpa::reserved0: "U32D_FMT"\n", data_to_print->reserved0);
    fprintf(out_port, "mfpa::fs: "U32D_FMT"\n", data_to_print->fs);
    fprintf(out_port, "mfpa::reserved1: "U32D_FMT"\n", data_to_print->reserved1);
    fprintf(out_port, "mfpa::p: "U32D_FMT"\n", data_to_print->p);
    fprintf(out_port, "mfpa::reserved2: "U32D_FMT"\n", data_to_print->reserved2);
    fprintf(out_port, "mfpa::boot_address: "U32D_FMT"\n", data_to_print->boot_address);
    fprintf(out_port, "mfpa::reserved3: "U32D_FMT"\n", data_to_print->reserved3);
    fprintf(out_port, "mfpa::reserved4: "U32D_FMT"\n", data_to_print->reserved4);
    fprintf(out_port, "mfpa::flash_num: "U32D_FMT"\n", data_to_print->flash_num);
    fprintf(out_port, "mfpa::reserved5: "U32D_FMT"\n", data_to_print->reserved5);
    fprintf(out_port, "mfpa::jedec_id: "U32D_FMT"\n", data_to_print->jedec_id);
    fprintf(out_port, "mfpa::reserved6: "U32D_FMT"\n", data_to_print->reserved6);
    fprintf(out_port, "mfpa::sector_size: "U32D_FMT"\n", data_to_print->sector_size);
    fprintf(out_port, "mfpa::reserved7: "U32D_FMT"\n", data_to_print->reserved7);
    fprintf(out_port, "mfpa::block_allighment: "U32D_FMT"\n", data_to_print->block_allighment);
    fprintf(out_port, "mfpa::reserved8: "U32D_FMT"\n", data_to_print->reserved8);
    fprintf(out_port, "mfpa::capability_mask: "U32D_FMT"\n", data_to_print->capability_mask);
    fprintf(out_port, "mfpa::reserved9: "U32D_FMT"\n", data_to_print->reserved9);
}


/**************************************/
/* Name: mfbe
 * Size: 96 bits
 * Description: mfbe */


u_int32_t mfbe_pack(struct mfbe *data_to_pack, u_int8_t *packed_buffer) {
    push_to_buff(packed_buffer, 28, 4, data_to_pack->reserved0);
    push_to_buff(packed_buffer, 26, 2, data_to_pack->fs);
    push_to_buff(packed_buffer, 24, 2, data_to_pack->reserved1);
    push_to_buff(packed_buffer, 23, 1, data_to_pack->p);
    push_to_buff(packed_buffer, 0, 23, data_to_pack->reserved2);
    push_to_buff_32(packed_buffer, 32, data_to_pack->reserved3);
    push_to_buff(packed_buffer, 72, 24, data_to_pack->address);
    push_to_buff(packed_buffer, 64, 8, data_to_pack->reserved4);
    return 12;
}

void mfbe_unpack(struct mfbe *unpacked_data, u_int8_t *buffer_to_unpack) {
    unpacked_data->reserved0 = pop_from_buff(buffer_to_unpack, 28, 4);
    unpacked_data->fs = pop_from_buff(buffer_to_unpack, 26, 2);
    unpacked_data->reserved1 = pop_from_buff(buffer_to_unpack, 24, 2);
    unpacked_data->p = pop_from_buff(buffer_to_unpack, 23, 1);
    unpacked_data->reserved2 = pop_from_buff(buffer_to_unpack, 0, 23);
    unpacked_data->reserved3 = pop_from_buff_32(buffer_to_unpack, 32);
    unpacked_data->address = pop_from_buff(buffer_to_unpack, 72, 24);
    unpacked_data->reserved4 = pop_from_buff(buffer_to_unpack, 64, 8);
}

void mfbe_dump(struct mfbe *data_to_print, FILE *out_port) {
    fprintf(out_port, "mfbe::reserved0: "U32D_FMT"\n", data_to_print->reserved0);
    fprintf(out_port, "mfbe::fs: "U32D_FMT"\n", data_to_print->fs);
    fprintf(out_port, "mfbe::reserved1: "U32D_FMT"\n", data_to_print->reserved1);
    fprintf(out_port, "mfbe::p: "U32D_FMT"\n", data_to_print->p);
    fprintf(out_port, "mfbe::reserved2: "U32D_FMT"\n", data_to_print->reserved2);
    fprintf(out_port, "mfbe::reserved3: "U32D_FMT"\n", data_to_print->reserved3);
    fprintf(out_port, "mfbe::address: "U32D_FMT"\n", data_to_print->address);
    fprintf(out_port, "mfbe::reserved4: "U32D_FMT"\n", data_to_print->reserved4);
}




/*************************************/
/* Name: OperationTlv
 * Size: 128 bits
 * Description:  */


u_int32_t OperationTlv_pack(struct OperationTlv *data_to_pack, u_int8_t *packed_buffer) {
    push_to_buff(packed_buffer, 24, 8, data_to_pack->reserved0);
    push_to_buff(packed_buffer, 17, 7, data_to_pack->status);
    push_to_buff(packed_buffer, 16, 1, data_to_pack->dr);
    push_to_buff(packed_buffer, 5, 11, data_to_pack->len);
    push_to_buff(packed_buffer, 0, 5, data_to_pack->Type);
    push_to_buff(packed_buffer, 56, 8, data_to_pack->class);
    push_to_buff(packed_buffer, 49, 7, data_to_pack->method);
    push_to_buff(packed_buffer, 48, 1, data_to_pack->r);
    push_to_buff(packed_buffer, 32, 16, data_to_pack->register_id);
    push_to_buff_64(packed_buffer, 64, data_to_pack->tid);
    return 16;
}

void OperationTlv_unpack(struct OperationTlv *unpacked_data, u_int8_t *buffer_to_unpack) {
    unpacked_data->reserved0 = pop_from_buff(buffer_to_unpack, 24, 8);
    unpacked_data->status = pop_from_buff(buffer_to_unpack, 17, 7);
    unpacked_data->dr = pop_from_buff(buffer_to_unpack, 16, 1);
    unpacked_data->len = pop_from_buff(buffer_to_unpack, 5, 11);
    unpacked_data->Type = pop_from_buff(buffer_to_unpack, 0, 5);
    unpacked_data->class = pop_from_buff(buffer_to_unpack, 56, 8);
    unpacked_data->method = pop_from_buff(buffer_to_unpack, 49, 7);
    unpacked_data->r = pop_from_buff(buffer_to_unpack, 48, 1);
    unpacked_data->register_id = pop_from_buff(buffer_to_unpack, 32, 16);
    unpacked_data->tid = pop_from_buff_64(buffer_to_unpack, 64);
}

void OperationTlv_dump(struct OperationTlv *data_to_print, FILE *out_port) {
    fprintf(out_port, "OperationTlv::reserved0: "U32D_FMT"\n", data_to_print->reserved0);
    fprintf(out_port, "OperationTlv::status: "U32D_FMT"\n", data_to_print->status);
    fprintf(out_port, "OperationTlv::dr: "U32D_FMT"\n", data_to_print->dr);
    fprintf(out_port, "OperationTlv::len: "U32D_FMT"\n", data_to_print->len);
    fprintf(out_port, "OperationTlv::Type: "U32D_FMT"\n", data_to_print->Type);
    fprintf(out_port, "OperationTlv::class: "U32D_FMT"\n", data_to_print->class);
    fprintf(out_port, "OperationTlv::method: "U32D_FMT"\n", data_to_print->method);
    fprintf(out_port, "OperationTlv::r: "U32D_FMT"\n", data_to_print->r);
    fprintf(out_port, "OperationTlv::register_id: "U32D_FMT"\n", data_to_print->register_id);
    fprintf(out_port, "OperationTlv::tid: "U64D_FMT"\n", data_to_print->tid);
}

/*************************************/
/* Name: reg_tlv
 * Size: 32 bits
 * Description: reg_tlv */


u_int32_t reg_tlv_pack(struct reg_tlv *data_to_pack, u_int8_t *packed_buffer) {
    push_to_buff(packed_buffer, 16, 16, data_to_pack->reserved0);
    push_to_buff(packed_buffer, 5, 11, data_to_pack->len);
    push_to_buff(packed_buffer, 0, 5, data_to_pack->Type);
    return 4;
}

void reg_tlv_unpack(struct reg_tlv *unpacked_data, u_int8_t *buffer_to_unpack) {
    unpacked_data->reserved0 = pop_from_buff(buffer_to_unpack, 16, 16);
    unpacked_data->len = pop_from_buff(buffer_to_unpack, 5, 11);
    unpacked_data->Type = pop_from_buff(buffer_to_unpack, 0, 5);
}

void reg_tlv_dump(struct reg_tlv *data_to_print, FILE *out_port) {
    fprintf(out_port, "reg_tlv::reserved0: "U32D_FMT"\n", data_to_print->reserved0);
    fprintf(out_port, "reg_tlv::len: "U32D_FMT"\n", data_to_print->len);
    fprintf(out_port, "reg_tlv::Type: "U32D_FMT"\n", data_to_print->Type);
}

/*************************************/
/* Name: mfba_mad
 * Size: 352 bits
 * Description: mfba_mad */
/*

u_int32_t mfba_mad_pack(struct mfba_mad *data_to_pack, u_int8_t *packed_buffer) {
    push_to_buff(packed_buffer, 28, 4, data_to_pack->reserved0);
    push_to_buff(packed_buffer, 26, 2, data_to_pack->fs);
    push_to_buff(packed_buffer, 24, 2, data_to_pack->reserved1);
    push_to_buff(packed_buffer, 23, 1, data_to_pack->p);
    push_to_buff(packed_buffer, 0, 23, data_to_pack->reserved2);
    push_to_buff(packed_buffer, 55, 9, data_to_pack->size);
    push_to_buff(packed_buffer, 32, 23, data_to_pack->reserved3);
    push_to_buff(packed_buffer, 72, 24, data_to_pack->address);
    push_to_buff(packed_buffer, 64, 8, data_to_pack->reserved4);
    push_to_buff_32(packed_buffer, 96, data_to_pack->data[0]);
    push_to_buff_32(packed_buffer, 128, data_to_pack->data[1]);
    push_to_buff_32(packed_buffer, 160, data_to_pack->data[2]);
    push_to_buff_32(packed_buffer, 192, data_to_pack->data[3]);
    push_to_buff_32(packed_buffer, 224, data_to_pack->data[4]);
    push_to_buff_32(packed_buffer, 256, data_to_pack->data[5]);
    push_to_buff_32(packed_buffer, 288, data_to_pack->data[6]);
    push_to_buff_32(packed_buffer, 320, data_to_pack->data[7]);
    return 44;
}

void mfba_mad_unpack(struct mfba_mad *unpacked_data, u_int8_t *buffer_to_unpack) {
    unpacked_data->reserved0 = pop_from_buff(buffer_to_unpack, 28, 4);
    unpacked_data->fs = pop_from_buff(buffer_to_unpack, 26, 2);
    unpacked_data->reserved1 = pop_from_buff(buffer_to_unpack, 24, 2);
    unpacked_data->p = pop_from_buff(buffer_to_unpack, 23, 1);
    unpacked_data->reserved2 = pop_from_buff(buffer_to_unpack, 0, 23);
    unpacked_data->size = pop_from_buff(buffer_to_unpack, 55, 9);
    unpacked_data->reserved3 = pop_from_buff(buffer_to_unpack, 32, 23);
    unpacked_data->address = pop_from_buff(buffer_to_unpack, 72, 24);
    unpacked_data->reserved4 = pop_from_buff(buffer_to_unpack, 64, 8);
    unpacked_data->data[0] = pop_from_buff_32(buffer_to_unpack, 96);
    unpacked_data->data[1] = pop_from_buff_32(buffer_to_unpack, 128);
    unpacked_data->data[2] = pop_from_buff_32(buffer_to_unpack, 160);
    unpacked_data->data[3] = pop_from_buff_32(buffer_to_unpack, 192);
    unpacked_data->data[4] = pop_from_buff_32(buffer_to_unpack, 224);
    unpacked_data->data[5] = pop_from_buff_32(buffer_to_unpack, 256);
    unpacked_data->data[6] = pop_from_buff_32(buffer_to_unpack, 288);
    unpacked_data->data[7] = pop_from_buff_32(buffer_to_unpack, 320);
}
*/

u_int32_t mfba_mad_pack(struct mfba_mad *data_to_pack, u_int8_t *packed_buffer) {
    push_to_buff(packed_buffer, 28, 4, data_to_pack->reserved0);
    push_to_buff(packed_buffer, 26, 2, data_to_pack->fs);
    push_to_buff(packed_buffer, 24, 2, data_to_pack->reserved1);
    push_to_buff(packed_buffer, 23, 1, data_to_pack->p);
    push_to_buff(packed_buffer, 0, 23, data_to_pack->reserved2);
    push_to_buff(packed_buffer, 55, 9, data_to_pack->size);
    push_to_buff(packed_buffer, 32, 23, data_to_pack->reserved3);
    push_to_buff(packed_buffer, 72, 24, data_to_pack->address);
    push_to_buff(packed_buffer, 64, 8, data_to_pack->reserved4);
    push_to_buff_32(packed_buffer, 96, data_to_pack->data[0]);
    push_to_buff_32(packed_buffer, 128, data_to_pack->data[1]);
    push_to_buff_32(packed_buffer, 160, data_to_pack->data[2]);
    push_to_buff_32(packed_buffer, 192, data_to_pack->data[3]);
    push_to_buff_32(packed_buffer, 224, data_to_pack->data[4]);
    push_to_buff_32(packed_buffer, 256, data_to_pack->data[5]);
    push_to_buff_32(packed_buffer, 288, data_to_pack->data[6]);
    push_to_buff_32(packed_buffer, 320, data_to_pack->data[7]);
    push_to_buff_32(packed_buffer, 352, data_to_pack->data[8]);
    push_to_buff_32(packed_buffer, 384, data_to_pack->data[9]);
    push_to_buff_32(packed_buffer, 416 , data_to_pack->data[10]);
    push_to_buff_32(packed_buffer, 448, data_to_pack->data[11]);
    push_to_buff_32(packed_buffer, 480, data_to_pack->data[12]);
    push_to_buff_32(packed_buffer, 512, data_to_pack->data[13]);
    push_to_buff_32(packed_buffer, 544, data_to_pack->data[14]);
    push_to_buff_32(packed_buffer, 576, data_to_pack->data[15]);
    push_to_buff_32(packed_buffer, 608, data_to_pack->data[16]);
    push_to_buff_32(packed_buffer, 640, data_to_pack->data[17]);
    push_to_buff_32(packed_buffer, 672, data_to_pack->data[18]);
    push_to_buff_32(packed_buffer, 704, data_to_pack->data[19]);
    push_to_buff_32(packed_buffer, 736, data_to_pack->data[20]);
    push_to_buff_32(packed_buffer, 768, data_to_pack->data[21]);
    push_to_buff_32(packed_buffer, 800, data_to_pack->data[22]);
    push_to_buff_32(packed_buffer, 832, data_to_pack->data[23]);
    push_to_buff_32(packed_buffer, 864, data_to_pack->data[24]);
    push_to_buff_32(packed_buffer, 896, data_to_pack->data[25]);
    push_to_buff_32(packed_buffer, 928, data_to_pack->data[26]);
    push_to_buff_32(packed_buffer, 960, data_to_pack->data[27]);
    push_to_buff_32(packed_buffer, 992, data_to_pack->data[28]);
    push_to_buff_32(packed_buffer, 1024, data_to_pack->data[29]);
    push_to_buff_32(packed_buffer, 1056, data_to_pack->data[30]);
    push_to_buff_32(packed_buffer, 1088, data_to_pack->data[31]);
    return 140;
}

void mfba_mad_unpack(struct mfba_mad *unpacked_data, u_int8_t *buffer_to_unpack) {
    unpacked_data->reserved0 = pop_from_buff(buffer_to_unpack, 28, 4);
    unpacked_data->fs = pop_from_buff(buffer_to_unpack, 26, 2);
    unpacked_data->reserved1 = pop_from_buff(buffer_to_unpack, 24, 2);
    unpacked_data->p = pop_from_buff(buffer_to_unpack, 23, 1);
    unpacked_data->reserved2 = pop_from_buff(buffer_to_unpack, 0, 23);
    unpacked_data->size = pop_from_buff(buffer_to_unpack, 55, 9);
    unpacked_data->reserved3 = pop_from_buff(buffer_to_unpack, 32, 23);
    unpacked_data->address = pop_from_buff(buffer_to_unpack, 72, 24);
    unpacked_data->reserved4 = pop_from_buff(buffer_to_unpack, 64, 8);
    unpacked_data->data[0] = pop_from_buff_32(buffer_to_unpack, 96);
    unpacked_data->data[1] = pop_from_buff_32(buffer_to_unpack, 128);
    unpacked_data->data[2] = pop_from_buff_32(buffer_to_unpack, 160);
    unpacked_data->data[3] = pop_from_buff_32(buffer_to_unpack, 192);
    unpacked_data->data[4] = pop_from_buff_32(buffer_to_unpack, 224);
    unpacked_data->data[5] = pop_from_buff_32(buffer_to_unpack, 256);
    unpacked_data->data[6] = pop_from_buff_32(buffer_to_unpack, 288);
    unpacked_data->data[7] = pop_from_buff_32(buffer_to_unpack, 320);
    unpacked_data->data[8] = pop_from_buff_32(buffer_to_unpack, 352);
    unpacked_data->data[9] = pop_from_buff_32(buffer_to_unpack, 384);
    unpacked_data->data[10] = pop_from_buff_32(buffer_to_unpack, 416);
    unpacked_data->data[11] = pop_from_buff_32(buffer_to_unpack, 448);
    unpacked_data->data[12] = pop_from_buff_32(buffer_to_unpack, 480);
    unpacked_data->data[13] = pop_from_buff_32(buffer_to_unpack, 512);
    unpacked_data->data[14] = pop_from_buff_32(buffer_to_unpack, 544);
    unpacked_data->data[15] = pop_from_buff_32(buffer_to_unpack, 576);
    unpacked_data->data[16] = pop_from_buff_32(buffer_to_unpack, 608);
    unpacked_data->data[17] = pop_from_buff_32(buffer_to_unpack, 640);
    unpacked_data->data[18] = pop_from_buff_32(buffer_to_unpack, 672);
    unpacked_data->data[19] = pop_from_buff_32(buffer_to_unpack, 704);
    unpacked_data->data[20] = pop_from_buff_32(buffer_to_unpack, 736);
    unpacked_data->data[21] = pop_from_buff_32(buffer_to_unpack, 768);
    unpacked_data->data[22] = pop_from_buff_32(buffer_to_unpack, 800);
    unpacked_data->data[23] = pop_from_buff_32(buffer_to_unpack, 832);
    unpacked_data->data[24] = pop_from_buff_32(buffer_to_unpack, 864);
    unpacked_data->data[25] = pop_from_buff_32(buffer_to_unpack, 896);
    unpacked_data->data[26] = pop_from_buff_32(buffer_to_unpack, 928);
    unpacked_data->data[27] = pop_from_buff_32(buffer_to_unpack, 960);
    unpacked_data->data[28] = pop_from_buff_32(buffer_to_unpack, 992);
    unpacked_data->data[29] = pop_from_buff_32(buffer_to_unpack, 1024);
    unpacked_data->data[30] = pop_from_buff_32(buffer_to_unpack, 1056);
    unpacked_data->data[31] = pop_from_buff_32(buffer_to_unpack, 1088);
}

void mfba_mad_dump(struct mfba_mad *data_to_print, FILE *out_port) {
    fprintf(out_port, "mfba_mad::reserved0: "U32D_FMT"\n", data_to_print->reserved0);
    fprintf(out_port, "mfba_mad::fs: "U32D_FMT"\n", data_to_print->fs);
    fprintf(out_port, "mfba_mad::reserved1: "U32D_FMT"\n", data_to_print->reserved1);
    fprintf(out_port, "mfba_mad::p: "U32D_FMT"\n", data_to_print->p);
    fprintf(out_port, "mfba_mad::reserved2: "U32D_FMT"\n", data_to_print->reserved2);
    fprintf(out_port, "mfba_mad::size: "U32D_FMT"\n", data_to_print->size);
    fprintf(out_port, "mfba_mad::reserved3: "U32D_FMT"\n", data_to_print->reserved3);
    fprintf(out_port, "mfba_mad::address: "U32H_FMT"\n", data_to_print->address);
    fprintf(out_port, "mfba_mad::reserved4: "U32D_FMT"\n", data_to_print->reserved4);
    fprintf(out_port, "mfba_mad::data[0]: "U32H_FMT"\n", data_to_print->data[0]);
    fprintf(out_port, "mfba_mad::data[1]: "U32H_FMT"\n", data_to_print->data[1]);
    fprintf(out_port, "mfba_mad::data[2]: "U32H_FMT"\n", data_to_print->data[2]);
    fprintf(out_port, "mfba_mad::data[3]: "U32H_FMT"\n", data_to_print->data[3]);
    fprintf(out_port, "mfba_mad::data[4]: "U32H_FMT"\n", data_to_print->data[4]);
    fprintf(out_port, "mfba_mad::data[5]: "U32H_FMT"\n", data_to_print->data[5]);
    fprintf(out_port, "mfba_mad::data[6]: "U32H_FMT"\n", data_to_print->data[6]);
    fprintf(out_port, "mfba_mad::data[7]: "U32H_FMT"\n", data_to_print->data[7]);
    fprintf(out_port, "mfba_mad::data[8]: "U32H_FMT"\n", data_to_print->data[8]);
    fprintf(out_port, "mfba_mad::data[9]: "U32H_FMT"\n", data_to_print->data[9]);
    fprintf(out_port, "mfba_mad::data[10]: "U32H_FMT"\n", data_to_print->data[10]);
    fprintf(out_port, "mfba_mad::data[11]: "U32H_FMT"\n", data_to_print->data[11]);
    fprintf(out_port, "mfba_mad::data[12]: "U32H_FMT"\n", data_to_print->data[12]);
    fprintf(out_port, "mfba_mad::data[13]: "U32H_FMT"\n", data_to_print->data[13]);
    fprintf(out_port, "mfba_mad::data[14]: "U32H_FMT"\n", data_to_print->data[14]);
    fprintf(out_port, "mfba_mad::data[15]: "U32H_FMT"\n", data_to_print->data[15]);
    fprintf(out_port, "mfba_mad::data[16]: "U32H_FMT"\n", data_to_print->data[16]);
    fprintf(out_port, "mfba_mad::data[17]: "U32H_FMT"\n", data_to_print->data[17]);
    fprintf(out_port, "mfba_mad::data[18]: "U32H_FMT"\n", data_to_print->data[18]);
    fprintf(out_port, "mfba_mad::data[19]: "U32H_FMT"\n", data_to_print->data[19]);
    fprintf(out_port, "mfba_mad::data[20]: "U32H_FMT"\n", data_to_print->data[20]);
    fprintf(out_port, "mfba_mad::data[21]: "U32H_FMT"\n", data_to_print->data[21]);
    fprintf(out_port, "mfba_mad::data[22]: "U32H_FMT"\n", data_to_print->data[22]);
    fprintf(out_port, "mfba_mad::data[23]: "U32H_FMT"\n", data_to_print->data[23]);
    fprintf(out_port, "mfba_mad::data[24]: "U32H_FMT"\n", data_to_print->data[24]);
    fprintf(out_port, "mfba_mad::data[25]: "U32H_FMT"\n", data_to_print->data[25]);
    fprintf(out_port, "mfba_mad::data[26]: "U32H_FMT"\n", data_to_print->data[26]);
    fprintf(out_port, "mfba_mad::data[27]: "U32H_FMT"\n", data_to_print->data[27]);
    fprintf(out_port, "mfba_mad::data[28]: "U32H_FMT"\n", data_to_print->data[28]);
    fprintf(out_port, "mfba_mad::data[29]: "U32H_FMT"\n", data_to_print->data[29]);
    fprintf(out_port, "mfba_mad::data[30]: "U32H_FMT"\n", data_to_print->data[30]);
    fprintf(out_port, "mfba_mad::data[31]: "U32H_FMT"\n", data_to_print->data[31]);
}
