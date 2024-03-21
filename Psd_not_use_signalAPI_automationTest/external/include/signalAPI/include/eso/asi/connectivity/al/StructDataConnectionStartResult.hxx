/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_DATACONNECTIONSTARTRESULT_HXX
#define ASI_CONNECTIVITY_AL_DATACONNECTIONSTARTRESULT_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/Definitions.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::DataConnectionStartResult.
    */
    struct PROXY_EXPORT DataConnectionStartResult
    {
        int32_t asiDataConnectionId; // optional=False
        asi::connectivity::al::ResultType result; // optional=False
        private:
            DataConnectionStartResult()
            :
            asiDataConnectionId(),
            result()
            { }
            friend class DataConnectionStartResultFactory;
            friend class CIFactory<DataConnectionStartResult>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::DataConnectionStartResult> >;
            friend class ipl::vector<DataConnectionStartResult>;
            friend class ipl::allocator<DataConnectionStartResult>;
#endif
    };

    typedef CIPtrArray<DataConnectionStartResult> CIDataConnectionStartResultArray;

    /** \brief factory for al::DataConnectionStartResult. */
    class PROXY_EXPORT DataConnectionStartResultFactory  : CIFactory<DataConnectionStartResult> {
    public:
        static inline CIPtr<DataConnectionStartResult> createDataConnectionStartResult() {
            return CIFactory<DataConnectionStartResult>::createObject();
        }
        static inline void createDataConnectionStartResult(CIPtr<DataConnectionStartResult> & s) {
            CIFactory<DataConnectionStartResult>::createObject(s);
        }
        static inline CIPtr<CIDataConnectionStartResultArray> createDataConnectionStartResultArray(size_t size) {
            return CIFactory<DataConnectionStartResult>::createArray(size);
        }
        static inline void createDataConnectionStartResultArray(CIPtr<CIDataConnectionStartResultArray>& a, size_t size) {
            CIFactory<DataConnectionStartResult>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_DATACONNECTIONSTARTRESULT_HXX
