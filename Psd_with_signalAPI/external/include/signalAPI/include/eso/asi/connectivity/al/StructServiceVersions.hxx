/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_SERVICEVERSIONS_HXX
#define ASI_CONNECTIVITY_AL_SERVICEVERSIONS_HXX

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
    \brief struct al::ServiceVersions.
    */
    struct PROXY_EXPORT ServiceVersions
    {
        uint16_t hf_ag; // optional=False
        uint16_t hf; // optional=False
        uint16_t sap; // optional=False
        uint16_t pbap; // optional=False
        uint16_t map_mse; // optional=False
        uint16_t opp; // optional=False
        uint16_t a2dp_sink; // optional=False
        uint16_t a2dp_source; // optional=False
        uint16_t avrcp; // optional=False
        private:
            ServiceVersions()
            :
            hf_ag(),
            hf(),
            sap(),
            pbap(),
            map_mse(),
            opp(),
            a2dp_sink(),
            a2dp_source(),
            avrcp()
            { }
            friend class ServiceVersionsFactory;
            friend class CIFactory<ServiceVersions>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::ServiceVersions> >;
            friend class ipl::vector<ServiceVersions>;
            friend class ipl::allocator<ServiceVersions>;
#endif
    };

    typedef CIPtrArray<ServiceVersions> CIServiceVersionsArray;

    /** \brief factory for al::ServiceVersions. */
    class PROXY_EXPORT ServiceVersionsFactory  : CIFactory<ServiceVersions> {
    public:
        static inline CIPtr<ServiceVersions> createServiceVersions() {
            return CIFactory<ServiceVersions>::createObject();
        }
        static inline void createServiceVersions(CIPtr<ServiceVersions> & s) {
            CIFactory<ServiceVersions>::createObject(s);
        }
        static inline CIPtr<CIServiceVersionsArray> createServiceVersionsArray(size_t size) {
            return CIFactory<ServiceVersions>::createArray(size);
        }
        static inline void createServiceVersionsArray(CIPtr<CIServiceVersionsArray>& a, size_t size) {
            CIFactory<ServiceVersions>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_SERVICEVERSIONS_HXX
