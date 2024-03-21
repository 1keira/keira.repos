/*
    Copyright 2022 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_INTERFACEINFORMATIONPROVIDER_HXX
#define UTIL_INTERFACEINFORMATIONPROVIDER_HXX

#include <util/config/Provider.hxx>

namespace util
{
namespace config
{

/**
 * The InterfaceInformationProvider is part of the InterfaceInformationCenter. The Provider itself is fully generic and
 * protocol-agnostic. Like the other ConfigProvider it is realized as a singelton.
 * This Provider provides a way to get the version information from the interface_version.json file.
 *
 * @link2req satisfies req~FW_UTIL_INTERFACE_INFORMATION_PROVIDER~1
 */
class UTIL_EXPORT InterfaceInformationProvider
{
public:
    static InterfaceInformationProvider& instance();

    bool isInit() const
    {
        return config_provider.isValid() && config_provider.isDictionary();
    }

    /**
     * Returns the configured interface versions.
     *
     * @param interfaceType the interface type e.g. rsi or asi
     * @param interfaceName the interface name
     * @param interfaceVersions the available interface version's as descriped in the interface_version file.
     * @return true if something went wrong e.g. not initialized
     *                                   or interfaceType or interfaceName not found.
     *                                   or if invalid data in the interface_version.json file was detected.
     * @return false on success
     */
    bool getInterfaceVersion(const std::string& interfaceType, const std::string &interfaceName,
        std::vector<std::string>& interfaceVersion) const;

private:
    InterfaceInformationProvider();
    ~InterfaceInformationProvider();
    InterfaceInformationProvider(const InterfaceInformationProvider&) = delete;
    InterfaceInformationProvider(InterfaceInformationProvider &&) = delete;
    InterfaceInformationProvider& operator=(const InterfaceInformationProvider&) = delete;
    InterfaceInformationProvider& operator=(InterfaceInformationProvider &&) = delete;

    config::Provider config_provider;
};

} // namespace config
} // namespace util

#endif //UTIL_INTERFACEINFORMATIONPROVIDER_HXX