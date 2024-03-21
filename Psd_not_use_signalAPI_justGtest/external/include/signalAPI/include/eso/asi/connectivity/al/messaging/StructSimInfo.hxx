/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_SIMINFO_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_SIMINFO_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/messaging/Definitions.hxx>
#include <asi/connectivity/al/messaging/Definitions.hxx>
#include <asi/connectivity/al/messaging/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{

    /**
    \brief struct messaging::SimInfo.
    */
    struct PROXY_EXPORT SimInfo
    {
        asi::connectivity::al::messaging::SimReady simReady; // optional=False
        asi::connectivity::al::messaging::SimType simType; // optional=False
        asi::connectivity::al::messaging::SimMode simMode; // optional=False
        CIPtr< CIString > iccid; // optional=True
        private:
            SimInfo()
            :
            simReady(),
            simType(),
            simMode(),
            iccid()
            { }
            friend class SimInfoFactory;
            friend class CIFactory<SimInfo>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::messaging::SimInfo> >;
            friend class ipl::vector<SimInfo>;
            friend class ipl::allocator<SimInfo>;
#endif
    };

    typedef CIPtrArray<SimInfo> CISimInfoArray;

    /** \brief factory for messaging::SimInfo. */
    class PROXY_EXPORT SimInfoFactory  : CIFactory<SimInfo> {
    public:
        static inline CIPtr<SimInfo> createSimInfo() {
            return CIFactory<SimInfo>::createObject();
        }
        static inline void createSimInfo(CIPtr<SimInfo> & s) {
            CIFactory<SimInfo>::createObject(s);
        }
        static inline CIPtr<CISimInfoArray> createSimInfoArray(size_t size) {
            return CIFactory<SimInfo>::createArray(size);
        }
        static inline void createSimInfoArray(CIPtr<CISimInfoArray>& a, size_t size) {
            CIFactory<SimInfo>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al
}//namespace messaging


#endif// ASI_CONNECTIVITY_AL_MESSAGING_SIMINFO_HXX
