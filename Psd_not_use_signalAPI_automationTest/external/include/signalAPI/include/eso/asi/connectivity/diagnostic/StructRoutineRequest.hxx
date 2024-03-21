/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUEST_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUEST_HXX

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
    \brief struct diagnostic::RoutineRequest.
    */
    struct PROXY_EXPORT RoutineRequest
    {
        /**
            data Array Size: unlimited
        */
        CIPtr< CIUInt8Array > data; // optional=True
        asi::connectivity::diagnostic::RoutineRequestType requestType; // optional=False
        uint32_t routineId; // optional=False
        private:
            RoutineRequest()
            :
            data(),
            requestType(),
            routineId()
            { }
            friend class RoutineRequestFactory;
            friend class CIFactory<RoutineRequest>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::RoutineRequest> >;
            friend class ipl::vector<RoutineRequest>;
            friend class ipl::allocator<RoutineRequest>;
#endif
    };

    typedef CIPtrArray<RoutineRequest> CIRoutineRequestArray;

    /** \brief factory for diagnostic::RoutineRequest. */
    class PROXY_EXPORT RoutineRequestFactory  : CIFactory<RoutineRequest> {
    public:
        static inline CIPtr<RoutineRequest> createRoutineRequest() {
            return CIFactory<RoutineRequest>::createObject();
        }
        static inline void createRoutineRequest(CIPtr<RoutineRequest> & s) {
            CIFactory<RoutineRequest>::createObject(s);
        }
        static inline CIPtr<CIRoutineRequestArray> createRoutineRequestArray(size_t size) {
            return CIFactory<RoutineRequest>::createArray(size);
        }
        static inline void createRoutineRequestArray(CIPtr<CIRoutineRequestArray>& a, size_t size) {
            CIFactory<RoutineRequest>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINEREQUEST_HXX
