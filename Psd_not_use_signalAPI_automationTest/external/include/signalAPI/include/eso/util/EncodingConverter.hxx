/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_ENCODINGCONVERTER_HXX
#define UTIL_ENCODINGCONVERTER_HXX

#include <ipl_config.h>
#include <iplcompiler.h>
#include <util/util_dso.h>
#include <common/types/map.hxx>
#include <util/UnicodeString.hxx>
#include <common/streams/istream.hxx>

namespace util{

/**
        \brief        encoding converter class

        This class converts between different character encodings. It only works for stateless encodings, because for
        stateful ones, a state machine is needed. Luckily, most encodings are stateless.
**/

class UTIL_EXPORT EncodingConverter{

public:
    /**
        \brief constructor
    **/
    EncodingConverter(const UnicodeChar byte2codepoint[256]) IPL_NOEXCEPT;

    /**
        \brief gets a unicode string from the character encoding
    **/
    UnicodeString convert(char const* const data, uint16_t& numErrors, uint32_t size=0, bool terminateAtZero=false, uint32_t* num_bytes_read = NULL) IPL_NOEXCEPT;

    /**
        \brief gets a unicode string from the character encoding
    **/
    util::DataBuffer<> convertInverse(const UnicodeString& data, uint16_t& numErrors) IPL_NOEXCEPT;

    /*
        \brief returns true when conversion data is loaded successuflly
    */
    bool isUsable() const IPL_NOEXCEPT {return true;}

    static EncodingConverter Iso8859_1;
    static EncodingConverter Iso8859_2;
    static EncodingConverter Iso8859_4;
    static EncodingConverter Iso8859_5;
    static EncodingConverter Iso8859_7;
    static EncodingConverter Iso8859_9;
    static EncodingConverter Iso8859_15;

private:
    const UnicodeChar *m_byte2codepoint;
    typedef ipl::map<UnicodeChar, uint8_t> Codepoint2Byte;
    Codepoint2Byte m_codepoint2byte;

    static const UnicodeChar ISO8859_1[];
    static const UnicodeChar ISO8859_2[];
    static const UnicodeChar ISO8859_4[];
    static const UnicodeChar ISO8859_5[];
    static const UnicodeChar ISO8859_7[];
    static const UnicodeChar ISO8859_9[];
    static const UnicodeChar ISO8859_15[];
};

}

#endif // UTIL_ENCODINGCONVERTER_HXX
