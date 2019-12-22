#pragma once
#include <stdio.h>
#include "flint_base.h"
#include "mtcr.h"

class Fs3Operations;
class Flash;


class ISignatureManager : public FlintErrMsg
{
public:
    virtual bool AddSignature(mfile* mf, Fs3Operations* imageOps, Flash *f, u_int32_t imageOffset) = 0;
    virtual bool GetSecureBootInfo() = 0;
    virtual ~ISignatureManager() {}
};

class AbstractSignatureManager : public ISignatureManager {
public:
    AbstractSignatureManager() {}
    virtual ~AbstractSignatureManager() {}
};

class FwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    FwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~FwOperationsSignatureManager() {}
    virtual bool AddSignature(mfile*, Fs3Operations*, Flash*, u_int32_t)
    {
        return true;//not relevant here
    }
    virtual bool GetSecureBootInfo()
    {
        return false;
    }
};


class BluefieldFwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    BluefieldFwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~BluefieldFwOperationsSignatureManager() {}
    virtual bool AddSignature(mfile* mf, Fs3Operations*, Flash*, u_int32_t);
    virtual bool GetSecureBootInfo()
    {
        return false;
    }
};


class ConnectX6FwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    ConnectX6FwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~ConnectX6FwOperationsSignatureManager() {}
    virtual bool AddSignature(mfile* mf, Fs3Operations*, Flash*, u_int32_t);
    virtual bool GetSecureBootInfo()
    {
        return false;
    }
};


class ConnectX6DXFwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    ConnectX6DXFwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~ConnectX6DXFwOperationsSignatureManager() {}
    virtual bool AddSignature(mfile* mf, Fs3Operations*, Flash*, u_int32_t);
    virtual bool GetSecureBootInfo();
};
