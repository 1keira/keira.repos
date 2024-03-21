/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef COMMON_NAMESPACE_IPL_HXX
#define COMMON_NAMESPACE_IPL_HXX
/*****************************************************************************/

#include <ipl_config.h>

/*****************************************************************************/
/*!
    \def IPL_NAMESPACE

    \brief
    This definition is only for backward compatibility with existing code.
    The namespace \c ipl is no longer an alias for namespace \c std.
*/

#define IPL_NAMESPACE ipl

#ifdef _MSC_VER
    // prevent a bunch of warning on MSVC about its own use of exception
    #pragma warning(disable:4530)
#endif

#include<common/types/new.hxx>
/*****************************************************************************/
#endif
