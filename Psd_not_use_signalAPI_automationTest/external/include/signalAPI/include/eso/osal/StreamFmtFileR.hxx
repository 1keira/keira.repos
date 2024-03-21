/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_STREAMFMTFILER_HXX
#define OSAL_STREAMFMTFILER_HXX

#include <common/types/string.hxx>
#include <common/streams/istream.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/StreamBinFileR.hxx>
#include <osal/FmtFileWrapper.hxx>


namespace osal
{

typedef FmtFileWrapper<StreamBinFileR, ipl::istream, StreamBinFileR::ReadFlags> StreamFmtFileR;

} // end osal

#endif
