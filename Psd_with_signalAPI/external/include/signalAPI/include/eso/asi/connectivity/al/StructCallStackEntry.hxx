/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_CALLSTACKENTRY_HXX
#define ASI_CONNECTIVITY_AL_CALLSTACKENTRY_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>
#include <asi/connectivity/al/StructTimestamp.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::CallStackEntry.
    */
    struct PROXY_EXPORT CallStackEntry
    {
        CIPtr< CIString > name; // optional=True
        CIPtr< CIString > number; // optional=True
        CIPtr< asi::connectivity::al::Timestamp > timestamp; // optional=True
        CIPtr< CIString > time; // optional=True
        CIPtr< CIString > date; // optional=True
        CIPtr< CIString > uid; // optional=True
        private:
            CallStackEntry()
            :
            name(),
            number(),
            timestamp(),
            time(),
            date(),
            uid()
            { }
            friend class CallStackEntryFactory;
            friend class CIFactory<CallStackEntry>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::CallStackEntry> >;
            friend class ipl::vector<CallStackEntry>;
            friend class ipl::allocator<CallStackEntry>;
#endif
    };

    typedef CIPtrArray<CallStackEntry> CICallStackEntryArray;

    /** \brief factory for al::CallStackEntry. */
    class PROXY_EXPORT CallStackEntryFactory  : CIFactory<CallStackEntry> {
    public:
        static inline CIPtr<CallStackEntry> createCallStackEntry() {
            return CIFactory<CallStackEntry>::createObject();
        }
        static inline void createCallStackEntry(CIPtr<CallStackEntry> & s) {
            CIFactory<CallStackEntry>::createObject(s);
        }
        static inline CIPtr<CICallStackEntryArray> createCallStackEntryArray(size_t size) {
            return CIFactory<CallStackEntry>::createArray(size);
        }
        static inline void createCallStackEntryArray(CIPtr<CICallStackEntryArray>& a, size_t size) {
            CIFactory<CallStackEntry>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_CALLSTACKENTRY_HXX
