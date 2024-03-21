/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_PSK_HXX_
#define COMMON_PSK_HXX_

#include <stddef.h>
#include <common/ipl_namespace.hxx>
#include <common/stdint.h>
#include <map>

namespace IPL_NAMESPACE {
    namespace psk {

        /**
         * \brief
         *      Retrieve the pre-shared key for the given ID
         * \param[in] id
         *      ID of the pre-shared key
         * \param[out] data
         *      Pointer to the retrieved key data
         * \param[out] data_size
         *      Size of the retrieved key
         * \return
         *      true on error, false on success
         */
        bool retrievePsk(uint16_t id, void** data, size_t& data_size);

        /**
         * \brief
         *      Securely destroy the given pre-shared key
         * \param[in] data
         *      Pointer to the key data
         * \param[in] data_size
         *      Size of the key
         * \return
         *      true on error, false on success
         */
         bool destroyPsk(void* data, size_t data_size);

         /**
         * \brief
         *      map the sent client id to a psk id
         * \param[in] identitiy
         *      identity sent by a client in order to communicate via psk
         * \return
         *      if the client id is in the map, return the appropriate psk id, otherwise return 0
         */
        uint16_t mapIdentityToID(const char * identitiy);
    }
}

#endif /* CXX_INCLUDE_COMMON_PSK_HXX_ */
