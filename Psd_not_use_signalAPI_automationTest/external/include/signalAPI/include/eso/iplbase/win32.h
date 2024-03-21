/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef IPLBASE_WIN32_HXX
#define IPLBASE_WIN32_HXX
/*****************************************************************************/
/*!
    \file
    \brief include windos.h in the right way

    It is extremely non-trivial to include Windows headers in a way that
    does not break the compile.
    Wherever you need to include windows.h or winsock2.h, include this file instead.
*/
/*****************************************************************************/

#ifndef NOMINMAX
#define NOMINMAX  // don't #define min and max
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601  // Windows 7 API
#endif

#include <winsock2.h>  // necessary to avoid problems when included later
#include <Ws2tcpip.h>  // apparently not automatically included in above
#include <Netioapi.h>  // apparently not automatically included in above
#include <windows.h>

/*****************************************************************************/
#endif
