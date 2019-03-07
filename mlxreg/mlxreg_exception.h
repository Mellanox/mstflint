/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */

#ifndef MLXREG_EXCEPTION_H
#define MLXREG_EXCEPTION_H
#include <string>
#include <exception>

namespace mlxreg {

class MlxRegException : public std::exception
{
public:
    MlxRegException(const char *fmt, ...);
    MlxRegException(const std::string & msg);
    virtual ~MlxRegException() throw();

    virtual std::string what_s() const;
    virtual const char* what() const throw();

protected:
    std::string _msg;
};

}

#endif /* MLXREG_EXCEPTION_H */
