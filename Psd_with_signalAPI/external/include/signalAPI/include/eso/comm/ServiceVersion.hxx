/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef COMM_SERVICE_VERSION_HXX
#define COMM_SERVICE_VERSION_HXX

#include <string>
#include <cstdint>
#include <ipl_config.h>
#include <comm/comm_dso.h>

namespace comm {

    /**
     * \brief Indicates if a version is available, see Proxy::getServiceVersion()
     */
    enum class ServiceVersionStatus {
            StatusOK                // version contains the service version
            ,StatusNotSupported     // the peer doesn't support the protocol feature
            ,StatusNotSet           // the service did not set a version
            ,StatusNotAlive         // the proxy is not alive yet
    };

    //! return a string representation of a value from ServiceVersionStatus
    COMM_EXPORT const char* serviceVersionStatusToString(ServiceVersionStatus status);

    /**
     * \brief Holds the semantic version of module and interface of a comm service.
     */
    struct COMM_EXPORT ServiceVersion {
        ServiceVersion() IPL_NOEXCEPT = default;
        ServiceVersion( uint16_t m_ma       // ! module major version value
                        ,uint16_t m_mi      // ! module minor version value
                        ,uint16_t m_pa      // ! module patch version value
                        ,uint16_t i_ma      // ! interface major version value
                        ,uint16_t i_mi      // ! interface minor version value
                        ,uint16_t i_pa      // ! interface patch version value
                        ) IPL_NOEXCEPT
        : v_module{m_ma, m_mi, m_pa}
        , v_interface{i_ma, i_mi, i_pa}
        {
        }

        std::string str() const IPL_NOEXCEPT;

        struct COMM_EXPORT SemVer {
            SemVer() IPL_NOEXCEPT = default;
            SemVer(uint16_t ma, uint16_t mi, uint16_t pa) IPL_NOEXCEPT
            : v_major(ma)
            , v_minor(mi)
            , v_patch(pa)
            {
            }

            uint16_t v_major{0};
            uint16_t v_minor{0};
            uint16_t v_patch{0};

            std::string str() const IPL_NOEXCEPT;

        };

        SemVer v_module;
        SemVer v_interface;
    };

    inline bool operator==(const ServiceVersion::SemVer& v1, const ServiceVersion::SemVer& v2) IPL_NOEXCEPT {
        return (v1.v_major == v2.v_major)
            && (v1.v_minor == v2.v_minor)
            && (v1.v_patch == v2.v_patch);
    }

    inline bool operator!=(const ServiceVersion::SemVer& v1, const ServiceVersion::SemVer& v2) IPL_NOEXCEPT {
        return !operator==(v1,v2);
    }

    inline bool operator==(const ServiceVersion& v1, const ServiceVersion& v2) IPL_NOEXCEPT {
        return (v1.v_module == v2.v_module)
            && (v1.v_interface == v2.v_interface);
    }

    inline bool operator!=(const ServiceVersion& v1, const ServiceVersion& v2) IPL_NOEXCEPT {
        return !operator==(v1,v2);
    }

}

#endif // COMM_SERVICE_VERSION_HXX
// vim: ts=4 sw=4:

