/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_STREAMFMTFILEW_HXX
#define OSAL_STREAMFMTFILEW_HXX

#include <common/types/string.hxx>
#include <common/streams/ostream.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/StreamBinFileW.hxx>
#include <osal/FmtFileWrapper.hxx>

namespace osal
{

typedef FmtFileWrapper<StreamBinFileW, ipl::ostream, StreamBinFileW::WriteFlags> StreamFmtFileW;

} // end osal

#endif
