/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef IPL_ERROR_STORAGES_H
#define IPL_ERROR_STORAGES_H

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>
#include <common/error/ErrorStorage.hxx>

namespace IPL_NAMESPACE
{

//! If an un-handled error is detected it will be dumped to stdout.
class IPLCOMMON_EXPORT StdoutDumpErrorStorage : public ErrorStorage
{
public:
    StdoutDumpErrorStorage() IPL_NOEXCEPT;
};

//! If an un-handled error is detected it will be dumped to stdout and abort will be called
class IPLCOMMON_EXPORT AbortErrorStorage : public ErrorStorage
{
public:
    AbortErrorStorage() IPL_NOEXCEPT;
};

//! If an un-handled error is detected it will be output using the system's tracing facility
class IPLCOMMON_EXPORT TraceErrorStorage : public ErrorStorage
{
private:
    int m_channel;
public:
    TraceErrorStorage(int channel) IPL_NOEXCEPT;
    int getChannel() IPL_NOEXCEPT;
};

//! If an un-handled error is detected the custom function given in the ctor will be called.
class IPLCOMMON_EXPORT CustomErrorStorage : public ErrorStorage
{
public:
    CustomErrorStorage(ErrorStorage::FPtrAction callback) IPL_NOEXCEPT;
};

} // end ns ipl

#endif
