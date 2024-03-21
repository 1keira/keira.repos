/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_NETWORKADDRESSBASE_HXX
#define OSAL_NETWORKADDRESSBASE_HXX
/****************************************************************************/

#include <ipl_config.h>
#include <osal/osal_dso.h>

#include <common/types/string.hxx>
#include <common/streams/sstream.hxx>
#include <common/PseudoBool.hxx>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \internal
    */
    struct OSAL_EXPORT NetworkAddressBase {

        enum Type { NONE, MAC, IPv4, IPv6 } type;
        //! \brief The address readable for humans
        ipl::string string;

        static const NetworkAddressBase ANY_IPv4;
        static const NetworkAddressBase ANY_IPv6;

        NetworkAddressBase() IPL_NOEXCEPT: type(NONE) {}
        NetworkAddressBase(Type type, const ipl::string &string) IPL_NOEXCEPT:
            type(type), string(string) {}

        operator ipl::PseudoBool () const IPL_NOEXCEPT {
            return type!=NONE && !string.empty()? &ipl::PSEUDO_TRUE : ipl::PSEUDO_FALSE;
        }

        //! \brief Compare type and raw string value (no parsing involved!)
        bool operator == (const NetworkAddressBase &other) const IPL_NOEXCEPT {
            return type==other.type && string==other.string;
        }
        //! \brief Compare type and raw string value (no parsing involved!)
        bool operator != (const NetworkAddressBase &other) const IPL_NOEXCEPT {
            return !operator == (other);
        }

        //! \brief Turn prefix length into netmask-like address
        bool set_prefix(Type type, unsigned prefix) IPL_NOEXCEPT;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
