/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_IPINFO_HXX
#define ASI_CONNECTIVITY_AL_IPINFO_HXX

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
    \brief struct al::IpInfo.
    */
    struct PROXY_EXPORT IpInfo
    {
        CIPtr< CIString > ip; // optional=True
        CIPtr< CIString > mask; // optional=True
        CIPtr< CIString > gateway; // optional=True
        CIPtr< CIString > pdns; // optional=True
        CIPtr< CIString > sdns; // optional=True
        private:
            IpInfo()
            :
            ip(),
            mask(),
            gateway(),
            pdns(),
            sdns()
            { }
            friend class IpInfoFactory;
            friend class CIFactory<IpInfo>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::IpInfo> >;
            friend class ipl::vector<IpInfo>;
            friend class ipl::allocator<IpInfo>;
#endif
    };

    typedef CIPtrArray<IpInfo> CIIpInfoArray;

    /** \brief factory for al::IpInfo. */
    class PROXY_EXPORT IpInfoFactory  : CIFactory<IpInfo> {
    public:
        static inline CIPtr<IpInfo> createIpInfo() {
            return CIFactory<IpInfo>::createObject();
        }
        static inline void createIpInfo(CIPtr<IpInfo> & s) {
            CIFactory<IpInfo>::createObject(s);
        }
        static inline CIPtr<CIIpInfoArray> createIpInfoArray(size_t size) {
            return CIFactory<IpInfo>::createArray(size);
        }
        static inline void createIpInfoArray(CIPtr<CIIpInfoArray>& a, size_t size) {
            CIFactory<IpInfo>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_IPINFO_HXX
