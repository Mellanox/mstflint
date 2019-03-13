/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2019, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 * pldm_utils.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Samer Deeb
 */

#ifndef _PLDM_BUFF_H_
#define _PLDM_BUFF_H_
#include <string>
#include <compatibility.h>

class PldmBuffer {
public:
    PldmBuffer();
    virtual ~PldmBuffer();

    bool loadFile(const std::string& fname);

    void read(u_int8_t & val);
    void read(u_int16_t & val);
    void read(u_int32_t & val);
    void read(std::string& str, size_t str_size);
    void read(u_int8_t *arr, size_t arr_size);

    int seek(long offset, int whence);
    long tell();
    void rewind();

private:
    u_int8_t * m_buff;
    long m_pos;
    long m_size;
};

#endif /* _PLDM_BUFF_H_ */

