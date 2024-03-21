/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_NETWORKADDRESS_HXX
#define OSAL_NETWORKADDRESS_HXX
/****************************************************************************/

#include <ipl_config.h>
#include <osal/osal_dso.h>

#include "NetworkAddressBase.hxx"

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief One network address of any kind
    */
    struct OSAL_EXPORT NetworkAddress: public NetworkAddressBase {

        NetworkAddress() IPL_NOEXCEPT: NetworkAddressBase() {}
        NetworkAddress(const NetworkAddressBase &other) IPL_NOEXCEPT:
            NetworkAddressBase(other) {}
        NetworkAddress(Type type, const ipl::string &string) IPL_NOEXCEPT:
            NetworkAddressBase(type, string) {}
        //! \brief Set from system dependent data
        NetworkAddress(int family, const void *data) IPL_NOEXCEPT {
            set(family, data);
        }

        //! \brief Set from system dependent data, return \c true on error
        // see .cxx file for argument format
        bool set(int family, const void *data) IPL_NOEXCEPT;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
