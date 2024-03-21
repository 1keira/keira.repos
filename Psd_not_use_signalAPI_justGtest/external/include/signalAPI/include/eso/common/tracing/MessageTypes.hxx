/*
    Copyright 2022 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_MESSAGETYPES_HXX
#define TRACING_MESSAGETYPES_HXX

#include <common/iplcommon_dso.h>
#include <common/stdint.h>


namespace tracing
{

//! \brief Currently specified message types.
struct IPLCOMMON_EXPORT MessageTypes
{
    static const int16_t STRING_OLD;            /* = 0; */      //! Obsolete coding of strings.
    static const int16_t STRING_UTF8;           /* = 1; */      //! Utf8 bytes of string.
    static const int16_t PROBE;                 /* = 2; */      //! Raw byte array contained in message data.
    static const int16_t COMM;                  /* = 3; */      //! Raw byte array contained in message data.
    static const int16_t MLP;                   /* = 4; */      //! MIB Logging Protocol
    static const int16_t ESO_BIN;               /* = 5; */      //! Eso binary representation of structure data.

    static const int16_t APP;                   /* = 0x80; */   //! Message types below are reserved by applications

    static const int16_t CKCM;                  /* = 0x80; */   //! Connectivity
    static const int16_t BT_HCI;                /* = 0x81; */   //! Connectivity
    static const int16_t TPEG;                  /* = 0x82; */   //! Navi
    static const int16_t ANNOTATION;            /* = 0x83; */   //! Annotation library blob
    static const int16_t AISIN_NAVPOS;          /* = 0x84; */   //! AW navigation
    static const int16_t ESOPOSPROVIDER;        /* = 0x85; */   //! Eso navigation
    static const int16_t FPK_PROFILE_CHANNEL;   /* = 0x86; */   //! FPK
    static const int16_t HERE_NAV;              /* = 0x87; */   //! Here navigation
    static const int16_t RSTP;                  /* = 0x88; */   //! RSTP server
    static const int16_t GNSS_RAW_DATA;         /* = 0x89; */   //! GNSS
    static const int16_t CHRONOSCOPE;           /* = 0x8a; */   //! Chronoscope
    static const int16_t HARMAN_ASIA_NAV;       /* = 0x8b; */   //! Harman Asia navigation
    static const int16_t ES_DATEN;              /* = 0x8c; */   //! FPK Event System Data
    static const int16_t IOC_ESO_TRACER;        /* = 0x8d; */   //! Conmod IOC traces
    static const int16_t NAT_BL;                /* = 0x8e; */   //! Native BL binary data
    static const int16_t TLR;                   /* = 0x8f; */   //! E3 platform TLR messages
    static const int16_t ESOMAPMATCHER;         /* = 0x90; */   //! Eso navigation

    static const int16_t USER;                  /* = 0x100; */  //! Message types below this are reserved.

    static const int16_t VW;                    /* = 0x5657; */ //! Message type for custom VW messages
};

}

#endif /* TRACING_MESSAGETYPES_HXX */
