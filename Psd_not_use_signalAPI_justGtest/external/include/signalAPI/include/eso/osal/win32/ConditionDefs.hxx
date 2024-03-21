#ifndef OSAL_WIN32_CONDITIONDEFS_HXX
#define OSAL_WIN32_CONDITIONDEFS_HXX

#include <osal/Mutex.hxx>
#include "ConditionBase.hxx"

namespace osal
{

//! datatype for Condition on WIN32
struct OSAL_EXPORT ConditionHandle :
    public ConditionBase<osal::Mutex>
{
    ConditionBase::State state;

    ConditionHandle() :
        ConditionBase<osal::Mutex>(&state)
    {}
};

} // end ns osal

#endif
