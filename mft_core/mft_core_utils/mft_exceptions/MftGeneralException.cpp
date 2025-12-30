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

#include "MftGeneralException.h"

namespace mft_core
{
MftGeneralException::MftGeneralException(const std::string& oExceptionMessage, int iErrorCode) :
    m_oExceptionMessage(oExceptionMessage), m_iErrorCode(iErrorCode)
{
}

const char* MftGeneralException::what() const throw()
{
    return m_oExceptionMessage.c_str();
}

int MftGeneralException::GetErrorCode() const throw()
{
    return m_iErrorCode;
}

} // namespace mft_core
