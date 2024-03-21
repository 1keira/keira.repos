/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_REGEX_HXX
#define OSAL_REGEX_HXX

#include <ipl_config.h>

#include <common/NonCopyable.hxx>
#include <common/error/Error.hxx>
#include <common/types/vector.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>

#if !defined OSAL_USE_POSIXREGEX && !defined OSAL_USE_SPENCER
    #error Regular expression implementation undefined!
#endif

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/RegexDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/RegexDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

namespace osal
{

/**
 * \brief
 *     Regular expression matching facility

 *     This class allows to compile regular expressions and match them
 *     against arbitrary strings. The supported regular expression
 *     syntax is conforming to POSIX extended regular expressions. That
 *     is e.g.  the syntax that the egrep utility uses.
 *
 *     Backreferences are explicitly *not* supported for performance
 *     reasons.
 **/
class OSAL_EXPORT Regex :
    public ipl::NonCopyable
{
public: // types

    /**
     * \brief
     *     Flags that influence regular expression matching
     **/
    enum CompileFlags : uint32_t
    {
        //! default behaviours are applied
        NONE = 0,
        //! ignore character case during match() operations
        IGNORE_CASE = 1,
        //! \brief
        //! make it possible to retrieve sub-string matches
        //! via match(const char*,ipl::vector<SubstringMatch>&)
        SUBSTRING_MATCHES = 1 << 1
    };

    //! regular expression specific error type
    static ipl::ErrorType Error;

    //! error codes used for Regex::Error
    enum RegexErrors
    {
        //! the regular expression contains a syntax error
        SYNTAX_ERROR = 0,
        //! the regular expresson routines ran out of memory
        MEMORY_EXAUSTED,
        //! \brief
        //! some error while trying to match an already compiled
        //! regular expressions against a string occured
        MATCH_ERROR
    };

    /**
     * \brief
     *     Represents a single sub-string match

     *     A sub-string match comes into play when sub-expressions
     *     are used in regular expressions. sub-expressions are
     *     introduced via parantheses like this: "\(.*\)". Each
     *     pair of parantheses introduces a new possible sub-string
     *     match.
     *
     *     If you compile your regular expression with support for
     *     SUBSTRING_MATCHES then you can get the sub-string
     *     matches from match(const char*, ipl::vector<
     *     SubstringMatch >&).
     **/
    struct SubstringMatch :
        public RegMatchHandle
    {
        inline size_t startOffset() const;

        inline size_t endOffset() const;

        inline size_t matchLength() const
        {
            return endOffset() - startOffset();
        }
    };

public: // functions
    /**
     * \brief
     *     Creates an invalid regular expression object

     *     isValid() will return \c false. To compile a regular
     *     expression call compile() for the new object.
     * \errors
     *     none
     **/
    Regex() :
        m_handle()
    { }

    /**
     * \brief
     *     Frees any storage associated with the object
     **/
    ~Regex()
    {
        this->clean();
    }

    /**
     * \brief
     *     Removes a previously compiled regular expression, if
     *     present
     **/
    inline void clean();

    /**
     * \brief
     *     Compile the regular expression \c expr

     *     On success subsequent match() calls will operate based
     *     on the regular expression \c expr.
     *
     *     Any previously compiled regular expression will be
     *     discarded by means of calling clean() before anything
     *     else is done.
     * \errorindicator
     *     via return code, via isValid()
     * \errors
     *     Regex::Error with ID
     *
     *     - MEMORY_EXAUSTED attached with
     *     ipl::CommonError with ID OUT_OF_MEMORY in case \c expr
     *     cannot be compiled due to lack of memory ressources in
     *     some place.
     *
     *     - SYNTAX_ERROR in a number of different cases that
     *     involve illegal syntax or bad logic contained in \c
     *     expr.
     * \return
     *     \c true on error, \c false on success
     **/
    bool compile(const char *expr,
        const uint32_t &flags = NONE);

    /**
     * \brief
     *     Match the provided string \a s against the currently
     *     compiled regular expression
     * \return
     *     < 0 if an error occured during the attempt to match \a s
     *     against the currently compiled regular expression. 0 if
     *     the match procedure was successfully performed and \a s
     *     matches the currently compiled regular expression. > 0
     *     if the match procedure was successfully performed but \a
     *     s doesn't match the currently compiled regular
     *     expression.
     **/
    inline int_fast8_t match(const char *s) const;

    /**
     * \brief
     *     Does the same as match(const char *s) const but also
     *     delivers the determined sub-string matches

     *     Use of this variant of match is only possible if the
     *     currently compiled regular expression has been compiled
     *     with the SUBSTRING_MATCHES flag set. If this is not the
     *     case then the function will always fail doing nothing.
     *
     *    On success \a matches will contain the determined
     *    sub-string matches. These are defined via the index
     *    positions within \a s where the according matches have
     *    been found.
     * \return
     *      \see match(const char*) const
     **/
    inline int_fast8_t match(const char *s,
        ipl::vector< SubstringMatch > &matches) const;

    //! \brief
    //! Returns \c true if currently a valid regular expression is
    //! loaded
    bool isValid() const
    { return m_handle.isValid(); }

private: // data
    RegexHandle m_handle;
}; // end class

} // end osal

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/Regex.inl"
#elif defined IPL_OS_WINPC
#    include "common/Regex.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
