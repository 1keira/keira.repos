/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_ENVIRONMENT_HXX
#define OSAL_ENVIRONMENT_HXX

#include <ipl_config.h>

#include <common/types/string.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "posix/EnvironmentDefs.hxx"
#elif defined IPL_OS_WINPC
#    include "win32/EnvironmentDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    /**
    * \brief
    *    Access to Current Process's Environment Variables

    *    This class allows access to the current process's environment
    *    variables in two ways:
    *
    *    By instantiating an object of this type you may iterate over all
    *    present environment variables. This is a potentially expensive
    *    operation as the underlying OS might need to allocate extra
    *    memory for this operation (notably on WinPC this is the case).
    *
    *    The other way is to access an environment variable by giving its
    *    name to the static function getVariable(). This access can be
    *    considered fast as the underlying OS is able to maintain a
    *    sorted data structure like a map to quickly access the content
    *    of the desired variable.
    *
    *    Note that currently there is no API available to change the
    *    content of an environment variable. If you need to change
    *    environment variables for a child process then use the
    *    facilities provided in osal::ProcessTNG.
    *
    *    Otherwise *don't* attempt write access to any of the strings
    *    returned by this class as this might wreck your process's
    *    environment or even cause memory corruption.
    **/
    class OSAL_EXPORT Environment
    {
    public: // types

        //! iterator-like type used in begin() and end()
        template <typename STRING>
        class const_iterator_base
        {
        public:
            const_iterator_base(EnvironmentIteratorHandle h) :
                m_handle(h)
            { }

            inline const_iterator_base& operator++();

            inline const_iterator_base operator++(int);

            /**
            * \brief
            *     Returns the environment variable currently
            *     pointed to

            *    Please be aware that the returned string is a
            *    flat copy of internal data structures. The
            *    returned string must not be modified and it is
            *    only valid until the iterator is moved to
            *    another position.
            **/
            inline STRING operator*() const;

            bool operator==(const const_iterator_base &o) const
            { return o.m_handle == m_handle; }

            bool operator!=(const const_iterator_base &o) const
            { return !operator==(o); }
        private:
            EnvironmentIteratorHandle m_handle;
        };

        //! iterator that returns ASCII strings
        typedef const_iterator_base<const char*> const_iterator;
        //! iterator that returns unicode strings
        typedef const_iterator_base<const osal::UnicodeString>
            const_iterator_ucs;

    public: // functions
        /**
        * \brief
        *    Create an Environment Object Containing the Current
        *    Environment Block

        *    The constructor already allocates any possibly needed
        *    memory. As this operation may fail you need to check
        *    isValid() for success.
        * \errorindicator
        *    via isValid()
        * \errors
        *    osal::SysError with UNKNOWN_ERROR ID in case isValid()
        *    returns false.
        **/
        Environment();

        /**
        * \brief
        *    Frees the Memory Acquired during Construction Time
        **/
        ~Environment();

        //! returns true if construction succeeded, false otherwise
        bool isValid() const;

        /**
        * \brief
        *    Returns an Iterator to the First Environment Variable
        *    Name-Value Pair

        *    Each string in the environment block is of the form
        *    "<name>=<value>" i.e.  the equal sign is a separator
        *    between the environment variable name and its value. As
        *    the environment variable content may also contain equal
        *    signs only the first occurence of the equal sign can be
        *    considered the separator.
        *
        *    The environment variable name usually isn't allowed to
        *    contain special characters.
        **/
        const_iterator begin() const;

        //! \brief
        //! returns an iterator to the position just after the last
        //! valid name-value pair
        const_iterator end() const;

        //! same as begin() but for unicode strings
        const_iterator_ucs begin_ucs() const;

        //! same as end() but for unicode strings
        const_iterator_ucs end_ucs() const;

        /**
        * \brief
        *    Query the process environment for the variable "name"

        *    Every system process gets supplied a number of so called
        *    environment variables usually consisting of "name=value"
        *    pairs. This function queries the process for the
        *    supplied environment variable name "name" and returns
        *    it's associated value. If no environment variable with
        *    that name exists than an empty string is returned.
        * \note
        *    Setting environment variables is not thread safe using
        *    standard functionality. OSAL requires you not to modify
        *    the process environment for this reason. Environment
        *    variables can be seen as a mechanism for the user to
        *    supply information to the process and thus they are
        *    considered read-only.
        * \return
        *    string containing the ASCII value of the given
        *    environment variable \c name or an empty string in case
        *    no such variable exists. The returned string is
        *    read-only and may only be valid for the calling thread.
        **/
        static const char* getVariable(const char *name);

        //! \brief
        //! does the same as getVariable(const char*) but takes an
        //! ipl::string object instead of a char*
        static const char* getVariable(const ipl::string &name)
        { return getVariable(name.c_str()); }

        /**
        * \brief
        *     Does the same as getVariable(const char*) but uses
        *     osal::UnicodeStrings instead of char*
        * \note
        *    Using unicode variable names (not content!) may reduce
        *    portability. In general POSIX and WIN32 allow variable
        *    names acc. to unicode but e.g. the bash shell doesn't
        *    allow to set such variables due to syntax restrictions.
        **/
        static osal::UnicodeString getVariable(
            const osal::UnicodeString &ucs);

        static ipl::wstring getVariable(const ipl::wstring &name)
        {
            osal::UnicodeString us(name);
            us = getVariable(us);
            return us;
        }
    private: // members
        EnvironmentHandle m_handle;
#if defined(IPL_OS_INTEGRITY)
#define ENV_VAR_COUNT 2
       static char m_env_map[ENV_VAR_COUNT * 2][100];
        static bool get_env;
#endif
    };

}  // end of namespace osal

#if defined IPL_OS_POSIX
#    include "posix/Environment.inl"
#elif defined IPL_OS_WINPC
#    include "winpc/Environment.inl"
#elif defined IPL_OS_INTEGRITY
#    include "integrity/Environment.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
