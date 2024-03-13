/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleStruct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_HFPDEVICEINFORMATION_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_HFPDEVICEINFORMATION_CSTYLE_HXX

#include <comm/commidltypes.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>
#include <asi/connectivity/al/cstyle/Definitions.hxx>

// Forward declaration of the struct needed for the forward declaration of the deserializer
namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{
struct HfpDeviceInformation;
}
}
}
}

// Forward declaration of serializer because of friend declaration
namespace util {
namespace serializer {
bool serialize (util::serializer::IStructuredSerializer &ser, const asi::connectivity::al::cstyle::HfpDeviceInformation& val);
bool deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::HfpDeviceInformation &val);
}
}

namespace asi
{
namespace connectivity
{
namespace al
{
namespace  cstyle
{

    /**
    \brief struct al::HfpDeviceInformation.
    */
    struct PROXY_EXPORT HfpDeviceInformation
    {
        public:
            HfpDeviceInformation()
            : m_featureMask()
            , m_hfpVersion()
            , m_voiceRecognitionFlavor()
            , m_manufacturerName(nullptr)
            , m_manufacturerModel(nullptr)
            , m_modelRevision(nullptr)
            , m_imei(nullptr)
            { }

            HfpDeviceInformation (const HfpDeviceInformation& other)
            : m_featureMask()
            , m_hfpVersion()
            , m_voiceRecognitionFlavor()
            , m_manufacturerName(nullptr)
            , m_manufacturerModel(nullptr)
            , m_modelRevision(nullptr)
            , m_imei(nullptr)
            {
              *this = other;
            }

            ~HfpDeviceInformation () {
                if (m_manufacturerName) {
                    delete m_manufacturerName;
                }
                if (m_manufacturerModel) {
                    delete m_manufacturerModel;
                }
                if (m_modelRevision) {
                    delete m_modelRevision;
                }
                if (m_imei) {
                    delete m_imei;
                }
            }
            bool operator==(const HfpDeviceInformation& rhs) const {
                bool equal = true;
                if (m_featureMask != rhs.m_featureMask)
                    equal = false;
                if (m_hfpVersion != rhs.m_hfpVersion)
                    equal = false;
                if (m_voiceRecognitionFlavor != rhs.m_voiceRecognitionFlavor)
                    equal = false;
                if (m_manufacturerName == nullptr && rhs.m_manufacturerName != nullptr)
                    equal = false;
                else if (m_manufacturerName != nullptr && rhs.m_manufacturerName == nullptr)
                    equal = false;
                else if ((m_manufacturerName != nullptr) && (rhs.m_manufacturerName != nullptr) && (*m_manufacturerName != *rhs.m_manufacturerName))
                    equal = false;
                if (m_manufacturerModel == nullptr && rhs.m_manufacturerModel != nullptr)
                    equal = false;
                else if (m_manufacturerModel != nullptr && rhs.m_manufacturerModel == nullptr)
                    equal = false;
                else if ((m_manufacturerModel != nullptr) && (rhs.m_manufacturerModel != nullptr) && (*m_manufacturerModel != *rhs.m_manufacturerModel))
                    equal = false;
                if (m_modelRevision == nullptr && rhs.m_modelRevision != nullptr)
                    equal = false;
                else if (m_modelRevision != nullptr && rhs.m_modelRevision == nullptr)
                    equal = false;
                else if ((m_modelRevision != nullptr) && (rhs.m_modelRevision != nullptr) && (*m_modelRevision != *rhs.m_modelRevision))
                    equal = false;
                if (m_imei == nullptr && rhs.m_imei != nullptr)
                    equal = false;
                else if (m_imei != nullptr && rhs.m_imei == nullptr)
                    equal = false;
                else if ((m_imei != nullptr) && (rhs.m_imei != nullptr) && (*m_imei != *rhs.m_imei))
                    equal = false;
                return equal;
            }
            bool operator!=(const HfpDeviceInformation& rhs) const {
                return !operator==(rhs);
            }

            HfpDeviceInformation& operator = (const HfpDeviceInformation& src) {
                if (this == &src) return *this;
                m_featureMask = src.m_featureMask;
                m_hfpVersion = src.m_hfpVersion;
                m_voiceRecognitionFlavor = src.m_voiceRecognitionFlavor;
                if (m_manufacturerName)
                    delete m_manufacturerName;
                if (src.m_manufacturerName) {
                    m_manufacturerName = new (ipl::nothrow)ipl::string(*(src.m_manufacturerName));
                } else {
                    m_manufacturerName = nullptr;
                }
                if (m_manufacturerModel)
                    delete m_manufacturerModel;
                if (src.m_manufacturerModel) {
                    m_manufacturerModel = new (ipl::nothrow)ipl::string(*(src.m_manufacturerModel));
                } else {
                    m_manufacturerModel = nullptr;
                }
                if (m_modelRevision)
                    delete m_modelRevision;
                if (src.m_modelRevision) {
                    m_modelRevision = new (ipl::nothrow)ipl::string(*(src.m_modelRevision));
                } else {
                    m_modelRevision = nullptr;
                }
                if (m_imei)
                    delete m_imei;
                if (src.m_imei) {
                    m_imei = new (ipl::nothrow)ipl::string(*(src.m_imei));
                } else {
                    m_imei = nullptr;
                }
                return *this;
            }

                void setfeatureMask(const uint32_t _value) {
                    m_featureMask = _value;
                }
                uint32_t getfeatureMask() const {
                    return m_featureMask;
                }
                void sethfpVersion(const asi::connectivity::al::cstyle::HfpVersion _value) {
                    m_hfpVersion = _value;
                }
                asi::connectivity::al::cstyle::HfpVersion gethfpVersion() const {
                    return m_hfpVersion;
                }
                void setvoiceRecognitionFlavor(const asi::connectivity::al::cstyle::VoiceRecognitionFlavor _value) {
                    m_voiceRecognitionFlavor = _value;
                }
                asi::connectivity::al::cstyle::VoiceRecognitionFlavor getvoiceRecognitionFlavor() const {
                    return m_voiceRecognitionFlavor;
                }
                void setmanufacturerName(const ipl::string* _value) {
                    if (m_manufacturerName)
                        delete m_manufacturerName;
                    if (_value) {
                        m_manufacturerName = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_manufacturerName = nullptr;
                    }
                }
                const ipl::string* getmanufacturerName() const {
                    return m_manufacturerName;
                }
                    bool manufacturerNameValid() const {
                        return m_manufacturerName != nullptr;
                    }
                void setmanufacturerModel(const ipl::string* _value) {
                    if (m_manufacturerModel)
                        delete m_manufacturerModel;
                    if (_value) {
                        m_manufacturerModel = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_manufacturerModel = nullptr;
                    }
                }
                const ipl::string* getmanufacturerModel() const {
                    return m_manufacturerModel;
                }
                    bool manufacturerModelValid() const {
                        return m_manufacturerModel != nullptr;
                    }
                void setmodelRevision(const ipl::string* _value) {
                    if (m_modelRevision)
                        delete m_modelRevision;
                    if (_value) {
                        m_modelRevision = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_modelRevision = nullptr;
                    }
                }
                const ipl::string* getmodelRevision() const {
                    return m_modelRevision;
                }
                    bool modelRevisionValid() const {
                        return m_modelRevision != nullptr;
                    }
                void setimei(const ipl::string* _value) {
                    if (m_imei)
                        delete m_imei;
                    if (_value) {
                        m_imei = new (ipl::nothrow)ipl::string(*_value);
                    } else {
                        m_imei = nullptr;
                    }
                }
                const ipl::string* getimei() const {
                    return m_imei;
                }
                    bool imeiValid() const {
                        return m_imei != nullptr;
                    }


        uint32_t m_featureMask;
        asi::connectivity::al::cstyle::HfpVersion m_hfpVersion;
        asi::connectivity::al::cstyle::VoiceRecognitionFlavor m_voiceRecognitionFlavor;
    private:
        ipl::string* m_manufacturerName;
        ipl::string* m_manufacturerModel;
        ipl::string* m_modelRevision;
        ipl::string* m_imei;
        friend bool util::serializer::serialize (util::serializer::IStructuredSerializer &s, const asi::connectivity::al::cstyle::HfpDeviceInformation& val);
        friend bool util::serializer::deserialize (util::serializer::IStructuredPullDeserializer &s, asi::connectivity::al::cstyle::HfpDeviceInformation &val);
    };

} // cstyle
}//namespace asi
}//namespace connectivity
}//namespace al

#endif// ASI_CONNECTIVITY_AL_HFPDEVICEINFORMATION_CSTYLE_HXX
