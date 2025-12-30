/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 */

#pragma once

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "mft_core/mft_core_utils/logger/Logger.h"

namespace mft_core
{
class MftGeneralException : public std::exception
{
public:
    virtual const char* what() const throw();
    MftGeneralException(const std::string& oExceptionMessage, int iErrorCode = 0);
    virtual ~MftGeneralException() throw(){};
    int GetErrorCode() const throw();

private:
    std::string m_oExceptionMessage;
    int m_iErrorCode;
};

#define LOG_AND_THROW_MFT_ERROR(oMessage) \
    std::stringstream oBuffer;            \
    oBuffer << oMessage << std::endl;     \
    LOG.Error(oBuffer.str());             \
    throw mft_core::MftGeneralException(oBuffer.str());

}; // namespace mft_core
