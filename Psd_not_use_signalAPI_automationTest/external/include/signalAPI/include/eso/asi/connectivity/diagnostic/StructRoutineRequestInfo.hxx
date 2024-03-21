/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUESTINFO_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUESTINFO_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/diagnostic/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace diagnostic
{

    /**
    \brief struct diagnostic::RoutineRequestInfo.
    */
    struct PROXY_EXPORT RoutineRequestInfo
    {
        uint32_t id; // optional=False
        asi::connectivity::diagnostic::RoutineRequestType requestType; // optional=False
        private:
            RoutineRequestInfo()
            :
            id(),
            requestType()
            { }
            friend class RoutineRequestInfoFactory;
            friend class CIFactory<RoutineRequestInfo>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::RoutineRequestInfo> >;
            friend class ipl::vector<RoutineRequestInfo>;
            friend class ipl::allocator<RoutineRequestInfo>;
#endif
    };

    typedef CIPtrArray<RoutineRequestInfo> CIRoutineRequestInfoArray;

    /** \brief factory for diagnostic::RoutineRequestInfo. */
    class PROXY_EXPORT RoutineRequestInfoFactory  : CIFactory<RoutineRequestInfo> {
    public:
        static inline CIPtr<RoutineRequestInfo> createRoutineRequestInfo() {
            return CIFactory<RoutineRequestInfo>::createObject();
        }
        static inline void createRoutineRequestInfo(CIPtr<RoutineRequestInfo> & s) {
            CIFactory<RoutineRequestInfo>::createObject(s);
        }
        static inline CIPtr<CIRoutineRequestInfoArray> createRoutineRequestInfoArray(size_t size) {
            return CIFactory<RoutineRequestInfo>::createArray(size);
        }
        static inline void createRoutineRequestInfoArray(CIPtr<CIRoutineRequestInfoArray>& a, size_t size) {
            CIFactory<RoutineRequestInfo>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUESTINFO_HXX
