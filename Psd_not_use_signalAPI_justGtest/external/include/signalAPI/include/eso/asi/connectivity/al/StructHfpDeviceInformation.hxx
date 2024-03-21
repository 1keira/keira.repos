/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_HFPDEVICEINFORMATION_HXX
#define ASI_CONNECTIVITY_AL_HFPDEVICEINFORMATION_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>
#include <asi/connectivity/al/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::HfpDeviceInformation.
    */
    struct PROXY_EXPORT HfpDeviceInformation
    {
        uint32_t featureMask; // optional=False
        asi::connectivity::al::HfpVersion hfpVersion; // optional=False
        asi::connectivity::al::VoiceRecognitionFlavor voiceRecognitionFlavor; // optional=False
        CIPtr< CIString > manufacturerName; // optional=True
        CIPtr< CIString > manufacturerModel; // optional=True
        CIPtr< CIString > modelRevision; // optional=True
        CIPtr< CIString > imei; // optional=True
        private:
            HfpDeviceInformation()
            :
            featureMask(),
            hfpVersion(),
            voiceRecognitionFlavor(),
            manufacturerName(),
            manufacturerModel(),
            modelRevision(),
            imei()
            { }
            friend class HfpDeviceInformationFactory;
            friend class CIFactory<HfpDeviceInformation>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::HfpDeviceInformation> >;
            friend class ipl::vector<HfpDeviceInformation>;
            friend class ipl::allocator<HfpDeviceInformation>;
#endif
    };

    typedef CIPtrArray<HfpDeviceInformation> CIHfpDeviceInformationArray;

    /** \brief factory for al::HfpDeviceInformation. */
    class PROXY_EXPORT HfpDeviceInformationFactory  : CIFactory<HfpDeviceInformation> {
    public:
        static inline CIPtr<HfpDeviceInformation> createHfpDeviceInformation() {
            return CIFactory<HfpDeviceInformation>::createObject();
        }
        static inline void createHfpDeviceInformation(CIPtr<HfpDeviceInformation> & s) {
            CIFactory<HfpDeviceInformation>::createObject(s);
        }
        static inline CIPtr<CIHfpDeviceInformationArray> createHfpDeviceInformationArray(size_t size) {
            return CIFactory<HfpDeviceInformation>::createArray(size);
        }
        static inline void createHfpDeviceInformationArray(CIPtr<CIHfpDeviceInformationArray>& a, size_t size) {
            CIFactory<HfpDeviceInformation>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_HFPDEVICEINFORMATION_HXX
