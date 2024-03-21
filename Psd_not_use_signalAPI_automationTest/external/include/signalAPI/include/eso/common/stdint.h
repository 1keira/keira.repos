/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*!
    \file
    Include this instead of <stdint.h> in order to compile even on systems
    that lack stdint.h.
*/

#include <ipl_config.h>

#if defined(HAVE_STDINT_H)
#include <stdint.h>
#elif defined(_MSC_VER)
#include "stdint-msc.h"
#else
#error Of all toolchains not having stdint.h we currently only support MSC. Please contact eso framework project lead for support of your particulary toolchain
#endif

/*****************************************************************************/
