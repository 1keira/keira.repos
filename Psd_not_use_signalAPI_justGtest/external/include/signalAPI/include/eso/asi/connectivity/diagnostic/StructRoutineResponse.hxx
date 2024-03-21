/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINERESPONSE_HXX
#define ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINERESPONSE_HXX

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
    \brief struct diagnostic::RoutineResponse.
    */
    struct PROXY_EXPORT RoutineResponse
    {
        /**
            data Array Size: unlimited
        */
        CIPtr< CIUInt8Array > data; // optional=True
        uint32_t routineId; // optional=False
        asi::connectivity::diagnostic::RoutineState state; // optional=False
        private:
            RoutineResponse()
            :
            data(),
            routineId(),
            state()
            { }
            friend class RoutineResponseFactory;
            friend class CIFactory<RoutineResponse>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::diagnostic::RoutineResponse> >;
            friend class ipl::vector<RoutineResponse>;
            friend class ipl::allocator<RoutineResponse>;
#endif
    };

    typedef CIPtrArray<RoutineResponse> CIRoutineResponseArray;

    /** \brief factory for diagnostic::RoutineResponse. */
    class PROXY_EXPORT RoutineResponseFactory  : CIFactory<RoutineResponse> {
    public:
        static inline CIPtr<RoutineResponse> createRoutineResponse() {
            return CIFactory<RoutineResponse>::createObject();
        }
        static inline void createRoutineResponse(CIPtr<RoutineResponse> & s) {
            CIFactory<RoutineResponse>::createObject(s);
        }
        static inline CIPtr<CIRoutineResponseArray> createRoutineResponseArray(size_t size) {
            return CIFactory<RoutineResponse>::createArray(size);
        }
        static inline void createRoutineResponseArray(CIPtr<CIRoutineResponseArray>& a, size_t size) {
            CIFactory<RoutineResponse>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace diagnostic


#endif// ASI_CONNECTIVITY_DIAGNOSTIC_ROUTINERESPONSE_HXX
