/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_STREAMFMTFILERW_HXX
#define OSAL_STREAMFMTFILERW_HXX

#include <common/types/string.hxx>
#include <common/streams/istream.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/StreamBinFileRW.hxx>
#include <osal/FmtFileWrapper.hxx>

namespace osal
{

typedef FmtFileWrapper<StreamBinFileRW, ipl::iostream, StreamBinFileRW::ReadWriteFlags> StreamFmtFileRW;

} // end osal

#endif
