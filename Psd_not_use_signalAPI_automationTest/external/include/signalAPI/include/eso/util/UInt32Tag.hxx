/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_UINT32TAG_HXX
#define UTIL_UINT32TAG_HXX

#include <cstdint>
#include <string>
#include <iostream>
#include <common/ByteOrder.hxx>


namespace util {

///@brief class defining a readable integer with 4 ascii characters
///

class UInt32Tag  {
public:

    ///@brief default xtor for an invalid tag
    constexpr UInt32Tag () : m_tag {0} {};

    ///@brief xtor from int
    constexpr UInt32Tag (uint32_t val) : m_tag {val} {};

    ///@brief xtor from 4 single characters
    constexpr UInt32Tag (char a1, char a2, char a3, char a4);

    ///@brief xtor expeciting an array of char of lenght 4;
    constexpr UInt32Tag (const char str[4]);

    ///@brief conversion to uint_32_t
    constexpr operator uint32_t() const { return m_tag; };

    ///@brief checks all characters are within [a-z] or [A-Z]
    constexpr bool isValid() const;

    ///@brief return the textual representation
    std::string toString() const;

private:

    uint32_t m_tag;

    static constexpr uint32_t convert (char a1, char a2, char a3, char a4)
    {
        return  (((uint32_t)(a1) << 24) | ((uint32_t)(a2) << 16) | ((uint32_t)(a3) << 8) | ((uint32_t)(a4)));
    }

    static constexpr bool isValidTagByte(char c)
    {
        return !((c < 'A' || c > 'z') || ( c >'Z' && c < 'a'));
        // or allow all ascii char?
        // return (c > char(31) && (c < char(127));d
    }

};


inline constexpr UInt32Tag::UInt32Tag(const char a[4])
 :m_tag {convert(a[0], a[1], a[2], a[3])}
{}


inline constexpr UInt32Tag::UInt32Tag (char a1, char a2, char a3, char a4)
 : m_tag { convert(a1,a2,a3,a4) }
{}


inline bool constexpr UInt32Tag::isValid() const
{
    return isValidTagByte((char)(m_tag  & 0x000000ff)) &&
           isValidTagByte((char)((m_tag & 0x0000ff00)>>8)) &&
           isValidTagByte((char)((m_tag & 0x00ff0000)>>16)) &&
           isValidTagByte((char)((m_tag & 0xff000000)>>24));
}


inline std::string UInt32Tag::toString() const
{
    if (isValid()) {
        uint32_t val = IPL_TO_BE_UINT32( m_tag);
        return std::string((char*)&val, sizeof(val));
    } else  {
        return std::to_string(m_tag);
    }
}

///@brief operator << for UInt32Tag
inline std::ostream &operator<<(std::ostream &os, const UInt32Tag& t) {
    os << t.toString();
    return os;
}


} // namespace util

#endif // UTIL_UINT32TAG
