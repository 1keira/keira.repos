/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_LEVELS_HXX
#define TRACING_LEVELS_HXX

#include <common/iplcommon_dso.h>
#include <common/stdint.h>
#include <common/types/string.hxx>

namespace tracing
{

//! \brief Filter levels available for trace messages
struct IPLCOMMON_EXPORT Levels
{
    //! Lowest level a trace message/entity can have.
    static const int16_t LevelTRACE = 0;
    static const int16_t LevelDEBUG = 1;
    static const int16_t LevelINFO = 2;
    static const int16_t LevelWARN = 3;
    static const int16_t LevelERROR = 4;
    //! Highest level a trace message/entity can have.
    static const int16_t LevelFATAL = 5;
    //! Disables traces from entities with this level.
    static const int16_t LevelOFF = 6;
    //! Unspecified, which means inherit from parent.
    static const int16_t LevelNONE = 7;
    //! Entities having this filter level are disabled.
    static const int16_t LevelDISABLED = 8;
    //! Default level is reserved for presets, using it in tracing.json not possible.
    static const int16_t LevelDEFAULT = 9;
    /*!
     *    \brief
     *        Array with strings of the level's names as declared above.
     */
    static const char * NAMES[10];
};

}

#endif /* TRACING_LEVELS_HXX */

