/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*
    This is a replacement for the missing inttypes.h in
    MS C compilers that are not C99 compliant.

    The standard reference was:
    www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf
*/
#ifndef IPL_INTTYPES_REPLACEMENT_H
#define IPL_INTTYPES_REPLACEMENT_H

#include <ipl_config.h>
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#elif defined(_MSC_VER)

/* 7.8 ... includes stdint.h */
#include "stdint.h"

/* Format conversion of integer types */
/* imaxdiv_t according to MSDN */
typedef struct {
    intmax_t quot;
    intmax_t rem;
} imaxdiv_t;

/* 7.8.1 Macros for format specifiers */
/* "C++ should include these only if __STDC_FORMAT_MACROS is defined before
   inttypes.h is included" */

#if !defined(__cplusplus) || defined (__STDC_FORMAT_MACROS)

/* fprintf macros for signed integers */
#define PRId8       "d"
#define PRIi8       "i"
#define PRIdLEAST8  "d"
#define PRIiLEAST8  "i"
#define PRIdFAST8   "d"
#define PRIiFAST8   "i"

#define PRId16      "hd"
#define PRIi16      "hi"
#define PRIdLEAST16 "hd"
#define PRIiLEAST16 "hi"
#define PRIdFAST16  "hd"
#define PRIiFAST16  "hi"

#define PRId32      "I32d"
#define PRIi32      "I32i"
#define PRIdLEAST32 "I32d"
#define PRIiLEAST32 "I32i"
#define PRIdFAST32  "I32d"
#define PRIiFAST32  "I32i"

#define PRId64      "I64d"
#define PRIi64      "I64i"
#define PRIdLEAST64 "I64d"
#define PRIiLEAST64 "I64i"
#define PRIdFAST64  "I64d"
#define PRIiFAST64  "I64i"

#define PRIdMAX     "I64d"
#define PRIiMAX     "I64i"

#define PRIdPTR     "Id"
#define PRIiPTR     "Ii"

/* fprintf macros for unsigned integers */
#define PRIo8       "o"
#define PRIu8       "u"
#define PRIx8       "x"
#define PRIX8       "X"
#define PRIoLEAST8  "o"
#define PRIuLEAST8  "u"
#define PRIxLEAST8  "x"
#define PRIXLEAST8  "X"
#define PRIoFAST8   "o"
#define PRIuFAST8   "u"
#define PRIxFAST8   "x"
#define PRIXFAST8   "X"

#define PRIo16      "ho"
#define PRIu16      "hu"
#define PRIx16      "hx"
#define PRIX16      "hX"
#define PRIoLEAST16 "ho"
#define PRIuLEAST16 "hu"
#define PRIxLEAST16 "hx"
#define PRIXLEAST16 "hX"
#define PRIoFAST16  "ho"
#define PRIuFAST16  "hu"
#define PRIxFAST16  "hx"
#define PRIXFAST16  "hX"

#define PRIo32      "I32o"
#define PRIu32      "I32u"
#define PRIx32      "I32x"
#define PRIX32      "I32X"
#define PRIoLEAST32 "I32o"
#define PRIuLEAST32 "I32u"
#define PRIxLEAST32 "I32x"
#define PRIXLEAST32 "I32X"
#define PRIoFAST32  "I32o"
#define PRIuFAST32  "I32u"
#define PRIxFAST32  "I32x"
#define PRIXFAST32  "I32X"

#define PRIo64      "I64o"
#define PRIu64      "I64u"
#define PRIx64      "I64x"
#define PRIX64      "I64X"
#define PRIoLEAST64 "I64o"
#define PRIuLEAST64 "I64u"
#define PRIxLEAST64 "I64x"
#define PRIXLEAST64 "I64X"
#define PRIoFAST64  "I64o"
#define PRIuFAST64  "I64u"
#define PRIxFAST64  "I64x"
#define PRIXFAST64  "I64X"


#define PRIoMAX     "I64o"
#define PRIuMAX     "I64u"
#define PRIxMAX     "I64x"
#define PRIXMAX     "I64X"
#define PRIoPTR     "Io"
#define PRIuPTR     "Iu"
#define PRIxPTR     "Ix"
#define PRIXPTR     "IX"

/* fscanf macros for signed integers */
#define SCNd8       "d"
#define SCNi8       "i"
#define SCNdLEAST8  "d"
#define SCNiLEAST8  "i"
#define SCNdFAST8   "d"
#define SCNiFAST8   "i"

#define SCNd16      "hd"
#define SCNi16      "hi"
#define SCNdLEAST16 "hd"
#define SCNiLEAST16 "hi"
#define SCNdFAST16  "hd"
#define SCNiFAST16  "hi"

#define SCNd32      "ld"
#define SCNi32      "li"
#define SCNdLEAST32 "ld"
#define SCNiLEAST32 "li"
#define SCNdFAST32  "ld"
#define SCNiFAST32  "li"

#define SCNd64      "I64d"
#define SCNi64      "I64i"
#define SCNdLEAST64 "I64d"
#define SCNiLEAST64 "I64i"
#define SCNdFAST64  "I64d"
#define SCNiFAST64  "I64i"

#define SCNdMAX     "I64d"
#define SCNiMAX     "I64i"

#ifdef _WIN64
/* 64 bit ptr */
#define SCNdPTR     "I64d"
#define SCNiPTR     "I64i"
#else
/* 32 bit */
#define SCNdPTR     "ld"
#define SCNiPTR     "li"
#endif

/* fscanf macros for unsigned integers */
#define SCNo8       "o"
#define SCNu8       "u"
#define SCNx8       "x"
#define SCNoLEAST8  "o"
#define SCNuLEAST8  "u"
#define SCNxLEAST8  "x"
#define SCNoFAST8   "o"
#define SCNuFAST8   "u"
#define SCNxFAST8   "x"

#define SCNo16      "ho"
#define SCNu16      "hu"
#define SCNx16      "hx"
#define SCNoLEAST16 "ho"
#define SCNuLEAST16 "hu"
#define SCNxLEAST16 "hx"
#define SCNoFAST16  "ho"
#define SCNuFAST16  "hu"
#define SCNxFAST16  "hx"

#define SCNo32      "lo"
#define SCNu32      "lu"
#define SCNx32      "lx"
#define SCNoLEAST32 "lo"
#define SCNuLEAST32 "lu"
#define SCNxLEAST32 "lx"
#define SCNoFAST32  "lo"
#define SCNuFAST32  "lu"
#define SCNxFAST32  "lx"

#define SCNo64      "I64o"
#define SCNu64      "I64u"
#define SCNx64      "I64x"
#define SCNoLEAST64 "I64o"
#define SCNuLEAST64 "I64u"
#define SCNxLEAST64 "I64x"
#define SCNoFAST64  "I64o"
#define SCNuFAST64  "I64u"
#define SCNxFAST64  "I64x"

#define SCNoMAX     "I64o"
#define SCNuMAX     "I64u"
#define SCNxMAX     "I64x"

#ifdef _WIN64
/* 64 bit ptr */
#define SCNoPTR     "I64o"
#define SCNuPTR     "I64u"
#define SCNxPTR     "I64x"
#else
/* 32 bit */
#define SCNoPTR     "lo"
#define SCNuPTR     "lu"
#define SCNxPTR     "lx"
#endif

#endif /* __cplusplus || __STDC_FORMAT_MACROS */

/* 7.8.2 Functions for greatest-width integer types */
/* 7.8.2.1 imaxabs */
#define imaxabs _abs64

/* 7.8.2.2 imaxdiv */
#define imaxdiv ldiv

/* 7.8.2.3 strtoimax, strtoumax */
#define strtoimax _strtoi64
#define strtoumax _strtoui64

/* 7.8.2.4 wcstoimax, wcstoumax */
#define wcstoimax _wcstoi64
#define wcstoumax _wcstoui64

#else
#error Of all toolchains not having inttypes.h we currently only support MSC. Please contact eso framework project lead for support of your particulary toolchain
#endif /* HAVE_INTTYPES_H */

#endif
