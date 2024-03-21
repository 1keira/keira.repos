/*
    Copyright 2022 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_INTERFACEINFORMATIONCENTER_HXX
#define COMM_INTERFACEINFORMATIONCENTER_HXX

#include <common/types/string.hxx>
#include <common/types/vector.hxx>
#include <comm/comm_dso.h>

namespace comm {
namespace iic {

/**
 * @brief Get the Interface Version of the Asi Service
 * @link2req satisfies req~FW_COMM_INTERFACE_INFORMATION_PROVIDER~1
 *
 * @param interfaceName Name of the interface to get the version for
 * @param version A vector of versions that belong to the interface
 * @return true Failed to get the interface version
 * @return false Successfully got the interface version
 */
bool COMM_EXPORT getAsiVersion(const std::string& interfaceName, std::vector<std::string> &version);

} //namespace iic
} //namespace comm

#endif //COMM_INTERFACEINFORMATIONCENTER_HXX
