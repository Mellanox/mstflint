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

#ifndef internal_packets_functions_H
#define internal_packets_functions_H

#include "internal_packets_types.h"
#include <stdlib.h>

/*************************************/
/* Name: mfbe
 * Size: 96 bits
 * Description: mfbe */

u_int32_t mfbe_pack(struct mfbe *data_to_pack, u_int8_t *packed_buffer);
void mfbe_unpack(struct mfbe *unpacked_data, u_int8_t *buffer_to_unpack);
void mfbe_dump(struct mfbe *data_to_print, FILE *out_port);


/*************************************/
/* Name: mfpa
 * Size: 256 bits
 * Description: mfpa */

u_int32_t mfpa_pack(struct mfpa *data_to_pack, u_int8_t *packed_buffer);
void mfpa_unpack(struct mfpa *unpacked_data, u_int8_t *buffer_to_unpack);
void mfpa_dump(struct mfpa *data_to_print, FILE *out_port);


/*************************************/
/* Name: reg_tlv
 * Size: 32 bits
 * Description: reg_tlv */

u_int32_t reg_tlv_pack(struct reg_tlv *data_to_pack, u_int8_t *packed_buffer);
void reg_tlv_unpack(struct reg_tlv *unpacked_data, u_int8_t *buffer_to_unpack);
void reg_tlv_dump(struct reg_tlv *data_to_print, FILE *out_port);

/*************************************/
/* Name: mfba_mad
 * Size: 352 bits
 * Description: mfba_mad */

u_int32_t mfba_mad_pack(struct mfba_mad *data_to_pack, u_int8_t *packed_buffer);
void mfba_mad_unpack(struct mfba_mad *unpacked_data, u_int8_t *buffer_to_unpack);
void mfba_mad_dump(struct mfba_mad *data_to_print, FILE *out_port);


/*************************************/
/* Name: OperationTlv
 * Size: 128 bits
 * Description:  */

u_int32_t OperationTlv_pack(struct OperationTlv *data_to_pack, u_int8_t *packed_buffer);
void OperationTlv_unpack(struct OperationTlv *unpacked_data, u_int8_t *buffer_to_unpack);
void OperationTlv_dump(struct OperationTlv *data_to_print, FILE *out_port);


#endif /* internal_packets_functions_H */
