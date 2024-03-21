/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_HELPERS_HXX
#define OSAL_HELPERS_HXX

#include <common/Unroller.hxx>

#ifndef IPL_OS_INTEGRITY
#include <malloc.h>
#endif

namespace osal
{

/*
 *    some unrolling helper for con- and destructors
 */

struct StringUnroller :
    public ipl::Unroller<char**>
{
    static void unroll_string(char **s)
    {
        if( *s)
        {
            ::free(*s);
            *s = NULL;
        }
    }

    StringUnroller(char **s) :
        ipl::Unroller<char**>(s, &unroll_string) { }
};

/*
 *    checks for a valid priority value
 *
 *    returns true on error, false otherwise
 *
 *    on error raises an appropriate error
 */
inline bool checkPriorityRange(const Priority &p)
{
    // min and max priorities are in general not a static concept
    // so there is no way of checking the validity of a priority value
    // without more context - e.g. scheduling policy/priority class of the thread
    // for backwards compatibility, return ok.
    // the actual calls to manipulate priorities might still fail.
    return false;
}



} // end namespace

#endif // OSAL_HELPERS_HXX
