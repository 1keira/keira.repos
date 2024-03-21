/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMMON_UNROLLER_HXX
#define COMMON_UNROLLER_HXX

#include <ipl_config.h>
#include <iplbase/exceptions.hxx>
#include <common/ipl_namespace.hxx>
#include <common/NonCopyable.hxx>

namespace IPL_NAMESPACE
{

/**
 * \brief
 *     Unrolling helper class

 *     This class helps you with unrolling certain operations e.g. upon
 *     error conditions in a larger block of code.
 *
 *     This is similar to the \c ScopeGuard approach. The difference is
 *     that the ScopeGuard calls a member function of an object to undo
 *     a certain operation. The Unroller, however, is provided an
 *     external function to perform some kind of unrol operation on a
 *     certain RESSOURCE.
 * \code
 *     // this example shows how to release a heap-allocated string in case of error
 *
 *     char *mystr = strdup("somestring");
 *
 *     struct StringUnroller : public Unroller<char*>
 *     {
 *          // this function contains the code to unroll the string
 *          allocation
 *         static void unroll_string(char *s)
 *         { ::free(s); }
 *
 *         StringUnroller(char* s) :
 *             Unroller<char*>(s, &unroll_string) { }
 *     };
 *
 *     StringUnroller su(mystr);
 *
 *     // do a lot of work
 *     if( error )
 *     {
 *         // error condition detected
 *
 *         // destructor of su will cleanup mystr automatically
 *         return;
 *     }
 *
 *     // this will cause su not to cleanup mystr any more (e.g. in
 *     case of success we want // to keep the string
 *     su.disarm();
 * \endcode
 **/
template <typename RESSOURCE>
class Unroller :
    ipl::NonCopyable
{
public:
    typedef void(*unroll_func)(RESSOURCE);
public:
    /**
     * \brief
     *     Create a new unroller for \c r of type RESSOURCE, using
     *     \c f as the function to call for unrolling.
     **/
    Unroller(RESSOURCE r, unroll_func f) IPL_NOEXCEPT :
        m_armed(true),
        m_res(r),
        m_func(f)
    { }

    /**
     * \brief
     *     If still armed will call \c f to unroll ressource \c r.
     **/
    ~Unroller() IPL_NOEXCEPT
    {
        if( m_armed )
            IPLBASE_ABORT_ON_EXCEPTION(
                (*m_func)(m_res);
            )
    }

    //! \brief
    //!    Call this function to cause the unroller object not to
    //!    unroll anything during destruction any more.
    void disarm() IPL_NOEXCEPT
    { m_armed = false; }
protected:
    bool m_armed;
    RESSOURCE m_res;
    unroll_func m_func;
};

} // end namespace

#endif /* COMMON_UNROLLER_HXX */
