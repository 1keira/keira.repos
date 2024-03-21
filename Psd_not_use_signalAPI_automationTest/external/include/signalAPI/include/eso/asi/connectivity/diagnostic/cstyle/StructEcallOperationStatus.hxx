/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ECALLOPERATIONSTATUS_CSTYLE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ECALLOPERATIONSTATUS_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>
#include <asi/connectivity/diagnostic/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{
struct EcallOperationStatus;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::diagnostic::cstyle::EcallOperationStatus& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::EcallOperationStatus &val);
}
}

namespace asi
{
namespace connectivity
{
namespace diagnostic
{
namespace  cstyle
{

    /**
    \brief struct diagnostic::EcallOperationStatus.
    */
    struct PROXY_EXPORT EcallOperationStatus
    {
        public:
            EcallOperationStatus()
            : m_dsAvailStateLegal()
            , m_dsAvailStatePrivate()
            , m_dsConfigStateLegal()
            , m_dsConfigStatePrivate()
            , m_functionStateLegal()
            , m_functionStatePrivate()
            , m_licenseStateLegal()
            , m_licenseStatePrivate()
            , m_serviceDisablReasonLegal()
            , m_serviceDisablReasonPrivate()
            , m_serviceStateLegal()
            , m_serviceStatePrivate()
            { }

            EcallOperationStatus (const EcallOperationStatus& other)
            : m_dsAvailStateLegal()
            , m_dsAvailStatePrivate()
            , m_dsConfigStateLegal()
            , m_dsConfigStatePrivate()
            , m_functionStateLegal()
            , m_functionStatePrivate()
            , m_licenseStateLegal()
            , m_licenseStatePrivate()
            , m_serviceDisablReasonLegal()
            , m_serviceDisablReasonPrivate()
            , m_serviceStateLegal()
            , m_serviceStatePrivate()
            {
              *this = other;
            }

            ~EcallOperationStatus () {
            }
            bool operator==(const EcallOperationStatus& rhs) const {
                bool equal = true;
                if (m_dsAvailStateLegal != rhs.m_dsAvailStateLegal)
                    equal = false;
                if (m_dsAvailStatePrivate != rhs.m_dsAvailStatePrivate)
                    equal = false;
                if (m_dsConfigStateLegal != rhs.m_dsConfigStateLegal)
                    equal = false;
                if (m_dsConfigStatePrivate != rhs.m_dsConfigStatePrivate)
                    equal = false;
                if (m_functionStateLegal != rhs.m_functionStateLegal)
                    equal = false;
                if (m_functionStatePrivate != rhs.m_functionStatePrivate)
                    equal = false;
                if (m_licenseStateLegal != rhs.m_licenseStateLegal)
                    equal = false;
                if (m_licenseStatePrivate != rhs.m_licenseStatePrivate)
                    equal = false;
                if (m_serviceDisablReasonLegal != rhs.m_serviceDisablReasonLegal)
                    equal = false;
                if (m_serviceDisablReasonPrivate != rhs.m_serviceDisablReasonPrivate)
                    equal = false;
                if (m_serviceStateLegal != rhs.m_serviceStateLegal)
                    equal = false;
                if (m_serviceStatePrivate != rhs.m_serviceStatePrivate)
                    equal = false;
                return equal;
            }
            bool operator!=(const EcallOperationStatus& rhs) const {
                return !operator==(rhs);
            }

            EcallOperationStatus& operator = (const EcallOperationStatus& src) {
                if (this == &src) return *this;
                m_dsAvailStateLegal = src.m_dsAvailStateLegal;
                m_dsAvailStatePrivate = src.m_dsAvailStatePrivate;
                m_dsConfigStateLegal = src.m_dsConfigStateLegal;
                m_dsConfigStatePrivate = src.m_dsConfigStatePrivate;
                m_functionStateLegal = src.m_functionStateLegal;
                m_functionStatePrivate = src.m_functionStatePrivate;
                m_licenseStateLegal = src.m_licenseStateLegal;
                m_licenseStatePrivate = src.m_licenseStatePrivate;
                m_serviceDisablReasonLegal = src.m_serviceDisablReasonLegal;
                m_serviceDisablReasonPrivate = src.m_serviceDisablReasonPrivate;
                m_serviceStateLegal = src.m_serviceStateLegal;
                m_serviceStatePrivate = src.m_serviceStatePrivate;
                return *this;
            }

                void setdsAvailStateLegal(const asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState _value) {
                    m_dsAvailStateLegal = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState getdsAvailStateLegal() const {
                    return m_dsAvailStateLegal;
                }
                void setdsAvailStatePrivate(const asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState _value) {
                    m_dsAvailStatePrivate = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState getdsAvailStatePrivate() const {
                    return m_dsAvailStatePrivate;
                }
                void setdsConfigStateLegal(const asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState _value) {
                    m_dsConfigStateLegal = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState getdsConfigStateLegal() const {
                    return m_dsConfigStateLegal;
                }
                void setdsConfigStatePrivate(const asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState _value) {
                    m_dsConfigStatePrivate = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState getdsConfigStatePrivate() const {
                    return m_dsConfigStatePrivate;
                }
                void setfunctionStateLegal(const asi::connectivity::diagnostic::cstyle::EcallFunctionState _value) {
                    m_functionStateLegal = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallFunctionState getfunctionStateLegal() const {
                    return m_functionStateLegal;
                }
                void setfunctionStatePrivate(const asi::connectivity::diagnostic::cstyle::EcallFunctionState _value) {
                    m_functionStatePrivate = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallFunctionState getfunctionStatePrivate() const {
                    return m_functionStatePrivate;
                }
                void setlicenseStateLegal(const asi::connectivity::diagnostic::cstyle::EcallLicenseState _value) {
                    m_licenseStateLegal = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallLicenseState getlicenseStateLegal() const {
                    return m_licenseStateLegal;
                }
                void setlicenseStatePrivate(const asi::connectivity::diagnostic::cstyle::EcallLicenseState _value) {
                    m_licenseStatePrivate = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallLicenseState getlicenseStatePrivate() const {
                    return m_licenseStatePrivate;
                }
                void setserviceDisablReasonLegal(const asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason _value) {
                    m_serviceDisablReasonLegal = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason getserviceDisablReasonLegal() const {
                    return m_serviceDisablReasonLegal;
                }
                void setserviceDisablReasonPrivate(const asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason _value) {
                    m_serviceDisablReasonPrivate = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason getserviceDisablReasonPrivate() const {
                    return m_serviceDisablReasonPrivate;
                }
                void setserviceStateLegal(const asi::connectivity::diagnostic::cstyle::EcallServiceState _value) {
                    m_serviceStateLegal = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallServiceState getserviceStateLegal() const {
                    return m_serviceStateLegal;
                }
                void setserviceStatePrivate(const asi::connectivity::diagnostic::cstyle::EcallServiceState _value) {
                    m_serviceStatePrivate = _value;
                }
                asi::connectivity::diagnostic::cstyle::EcallServiceState getserviceStatePrivate() const {
                    return m_serviceStatePrivate;
                }


        asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState m_dsAvailStateLegal;
        asi::connectivity::diagnostic::cstyle::EcallDatasetAvailabilityState m_dsAvailStatePrivate;
        asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState m_dsConfigStateLegal;
        asi::connectivity::diagnostic::cstyle::EcallDatasetConfigState m_dsConfigStatePrivate;
        asi::connectivity::diagnostic::cstyle::EcallFunctionState m_functionStateLegal;
        asi::connectivity::diagnostic::cstyle::EcallFunctionState m_functionStatePrivate;
        asi::connectivity::diagnostic::cstyle::EcallLicenseState m_licenseStateLegal;
        asi::connectivity::diagnostic::cstyle::EcallLicenseState m_licenseStatePrivate;
        asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason m_serviceDisablReasonLegal;
        asi::connectivity::diagnostic::cstyle::EcallServiceDisabledReason m_serviceDisablReasonPrivate;
        asi::connectivity::diagnostic::cstyle::EcallServiceState m_serviceStateLegal;
        asi::connectivity::diagnostic::cstyle::EcallServiceState m_serviceStatePrivate;
    private:
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::diagnostic::cstyle::EcallOperationStatus& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::diagnostic::cstyle::EcallOperationStatus &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace diagnostic

#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ECALLOPERATIONSTATUS_CSTYLE_HXX
