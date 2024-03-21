/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_NADDEVICEINFORMATION_HXX
#define ASI_CONNECTIVITY_AL_NADDEVICEINFORMATION_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::NadDeviceInformation.
    */
    struct PROXY_EXPORT NadDeviceInformation
    {
        CIPtr< CIString > manufacturer; // optional=True
        CIPtr< CIString > model; // optional=True
        CIPtr< CIString > fwVersion; // optional=True
        CIPtr< CIString > hwVersion; // optional=True
        CIPtr< CIString > imei; // optional=True
        private:
            NadDeviceInformation()
            :
            manufacturer(),
            model(),
            fwVersion(),
            hwVersion(),
            imei()
            { }
            friend class NadDeviceInformationFactory;
            friend class CIFactory<NadDeviceInformation>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::NadDeviceInformation> >;
            friend class ipl::vector<NadDeviceInformation>;
            friend class ipl::allocator<NadDeviceInformation>;
#endif
    };

    typedef CIPtrArray<NadDeviceInformation> CINadDeviceInformationArray;

    /** \brief factory for al::NadDeviceInformation. */
    class PROXY_EXPORT NadDeviceInformationFactory  : CIFactory<NadDeviceInformation> {
    public:
        static inline CIPtr<NadDeviceInformation> createNadDeviceInformation() {
            return CIFactory<NadDeviceInformation>::createObject();
        }
        static inline void createNadDeviceInformation(CIPtr<NadDeviceInformation> & s) {
            CIFactory<NadDeviceInformation>::createObject(s);
        }
        static inline CIPtr<CINadDeviceInformationArray> createNadDeviceInformationArray(size_t size) {
            return CIFactory<NadDeviceInformation>::createArray(size);
        }
        static inline void createNadDeviceInformationArray(CIPtr<CINadDeviceInformationArray>& a, size_t size) {
            CIFactory<NadDeviceInformation>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_NADDEVICEINFORMATION_HXX
