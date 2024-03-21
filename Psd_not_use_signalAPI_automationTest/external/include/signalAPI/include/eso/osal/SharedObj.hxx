/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SHAREDOBJ_HXX
#define OSAL_SHAREDOBJ_HXX

#include <ipl_config.h>

#include <common/error/Error.hxx>
#include <common/types/string.hxx>

#if defined (IPL_OS_POSIX) || defined (IPL_OS_INTEGRITY)
#    include "posix/SharedObjDefs.hxx"
#elif defined (IPL_OS_WINPC)
#    include "win32/SharedObjDefs.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#include <osal/osal_dso.h>

#include <osal/RefCounted.hxx>
#include <osal/UnicodeString.hxx>

namespace osal {

    /**
    * \brief
    *    Shared Object Loader Abstraction
    *

    *    A class to load a code or data object from a shared library. As
    *    the name states it actually represents the library and in case
    *    of destruction unloads the lib as well.
    *
    *     To be able to copy an instance of \c SharedObj this class is
    *     reference counted i.e. only if the last reference goes away then
    *     the library is unloaded.
    **/
    class OSAL_EXPORT SharedObj :
        public osal::RefCounted
    {
    public: // types

        //! specific SharedObj error IDs
        enum SOErrors
        {
            LOAD_FAILED = 0,
            UNLOAD_FAILED,
            RESOLVE_FAILED
        };

        //! SharedObj specific error type
        static ipl::ErrorType Error;

        //! platform dependent library naming prefix
        static const char* const SharedLibraryPrefix;
        //! platform dependent library naming postfix
        static const char* const SharedLibrarySuffix;
    public: // static functions

        /**
        * \brief
        *     Creates a platform independent library name from \c name

        *     \c name is expected to be the mere label of the library
        *     in question not containing any platform specific
        *     prefixes or postfixes.
        *
        *     Returned will the the platform dependent library name
        *     that can be found on the file system, for example.
        **/
        static ipl::string makeLibraryName(const ipl::string &name)
        {
            return ipl::string(SharedLibraryPrefix) + name +
                ipl::string(SharedLibrarySuffix);
        }
    public: // functions
        /**
        * \brief
        *     Constructs the object and optionally immediatly tries to
        *     open and load the given library into application address
        *     space.
        * \param[in]
        *     p_library_path The filesystem path to the shared library
        *     to load. May be a relative or absolute filename
        *     specification. Default value is NULL which means not to
        *     load a library at construction time.
        * \errorindicator
        *     via isValid()
        * \errors
        *     see load()
        **/
        SharedObj(const char* const p_library_path = NULL) :
            m_lib()
        {
            if( p_library_path )
                load(p_library_path);
        }

        /**
        * \brief
        *     Unicode constructor variant

        *     Does the same as SharedObj(const char* const) but takes
        *     an osal::UnicodeString for being able to open shared
        *     libraries in unicode path locations.
        * \see
        *     SharedObj(const char* const)
        **/
        SharedObj(
            const osal::UnicodeString &p_library_path) :
            m_lib()
        {
            load(p_library_path);
        }


        /**
        * \brief
        *     ipl::string constructor variant

        *     Does the same as SharedObj(const osal::UnicodeString &p_library_path)
        *  but takes an ipl::string for being able to open shared
        *     libraries in unicode path locations. The ipl::string has
        *  to contain a string encoded in utf-8
        * \see
        *     SharedObj(const osal::UnicodeString &p_library_path)
        **/
        SharedObj(
            const ipl::string &p_library_path) :
            m_lib()
        {
            load(p_library_path);
        }

        //! Calls reference counting facility of the base class
        ~SharedObj()
        {
            this->decrement();
        }

        /**
        * \brief
        *    Load a single shared library into application memory

        *    The function loads and stores the library reference into
        *    this object.
        *
        *    Any libraries and symbols that have previously been
        *    loaded via this object will be lost in both, successful
        *    and erroneous results of calling this function.
        * \param[in] p_library_path
        *    The file system path to the shared library to load. May
        *    be a relative or absolute filename specification. On
        *    some systems additional influential environment
        *    variables can be searched, system files be checked or
        *    standard library locations be searched if only a library
        *    name is specified instead of a path.
        *
        *    Use such features with caution though as it might
        *    introduce platform dependency.
        *
        *    Note that on for Win32 MSDN states you should only
        *    use backslashes for this path specification (whereas
        *    otherwise also slashes are acceptable as path
        *    seperators).
        *
        *    Also WIN32 tries to add a .dll extension to the path, if
        *    there is none present already. If you explicitly want to
        *    have no extension then specificy just a dot "." as the
        *    last character without an extension.
        * \errorindicator
        *    via isValid()
        * \errors
        *    ipl::CommonError with IDs:
        *
        *    - INVALID_USAGE if p_library_path is NULL
        *
        *    SharedObj::Error with IDs:
        *
        *    - LOAD_FAILED if unload() of previously loaded library
        *    failed
        *    - LOAD_FAILED on system specific error reasons. File not
        *    found error is usually detected by the system. But
        *    linkage errors like "symbol not found" or "dependencies
        *    missing" are not specifically denoted most of the time.
        *    So don't be surprised when you get an error with reason
        *    "success" at this point. Time to investigate then, Mr.
        *    Holmes.
        * \warning
        *    On some sytems (notably ELF systems) if the specified
        *    shared library has additional dependencies then these
        *    dependencies are implicitly searched, too and pulled in
        *    together with the library.
        *
        *    On other systems however (notably WIN32) the operation
        *    fails in such cases. The situation is further
        *    complicated by the fact that when explicit loading of all
        *    dependencies in your own may again cause strange
        *    behaviour on some systems (ELF systems).
        *
        *    The best choice in this case is to use different code
        *    paths for the different behaviour of these systems (e.g.
        *    different code for POSIX and WIN32 branches) that loads
        *    only the library of interest or every dependency in
        *    advance instead.
        **/
        void load(const char* const p_library_path);

        /**
        * \brief
        *     Load a shared library located in a unicode path
        * \see
        *     load(const char* const)

        *     Does the same as load(const char* const) but operates on
        *     a shared library located in a unicode path.
        **/
        void load(const osal::UnicodeString &ucs);

        /**
        * \brief
        *     Load a shared library located in a unicode path. The path
        *  has to be encoded in utf-8
        * \see
        *     load(const osal::UnicodeString &ucs)

        *     Does the same as load(const osal::UnicodeString &ucs) but operates on
        *     a utf-8 encoded ipl::string path instead of osal::UnicodeString path
        **/
        void load(const ipl::string& path){
            load(osal::UnicodeString(path));
        }

        /**
        * \brief
        *     Free a currently loaded library. Further use of any
        *     previously resolved symbols will end up in trouble.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        * \errors
        *     ipl::CommonError with IDs:
        *
        *     - INVALID_USAGE if there is currently no library loaded
        *
        *     SharedObj::Error with IDs:
        *
        *     - UNLOAD_FAILED on system specific errors during unload
        *     attempt
        **/
        bool unload();

        /**
        * \brief
        *    Same as load, but also resolve a given symbol
        *    immediatly.

        *    In addition to the behaviour of load() the resolving
        *    part of this functions stores its result into the given
        *    reference on success.
        *
        *    If an error occurs then the library may already be valid
        *    but only the symbol resolution failed. The caller should
        *    check for that condition via isValid().
        *
        *    Any libraries and symbols that have previously been
        *    loaded via this object will be lost in both, successful
        *    and erroneous cases of calling this function.
        * \param[in] location
        *    The file system path to the shared library to load. May
        *    be a relative or absolute filename specification.
        * \param[in] symbol
        *    Name of the symbol in the library found at \c location
        *    to look up and resolve.
        * \param[out] loadedsym
        *    loadedsym where to store the resolve result
        * \return
        *    true on error, false on success
        * \errorindicator
        *    via return code
        * \errors
        *    see load() and void* resolve(const char* const)
        * \note
        *    The template declaration of this function allows you to
        *    put in your specific function signature or data type
        *    without the need for additional casting.
        *
        *    Also both the ASCII and the unicode path variant of
        *    load() are covered with the template.
        **/
        template <
            typename STRING_TYPE,
            typename SYMBOL_TYPE>
        bool loadAndResolve(STRING_TYPE location,
            const char* const symbol,
            SYMBOL_TYPE &loadedsym)
        {
            load(location);

            if( !isValid() )
                return true;

            return resolve(symbol, loadedsym);
        }

        /**
        * \brief
        *     A convenience function using templates that does the
        *     same as void* resolve(const char* const)

        *     The template declaration of this function allows type
        *     safe resolving of a shared library symbol without the
        *     caller needing to actively cast the resolve result to
        *     the symbol type.
        * \param[out] addr
        *     address of symbol \c symbol_name or NULL on error
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        * \errors
        *     see bool resolve(const char* const, void*&)
        **/
        template <typename SYMBOL_TYPE>
        bool resolve(const char* const symbol_name,
            SYMBOL_TYPE &addr) const
        {
            void* symbol_address;

            if( resolve(symbol_name, symbol_address) ) // BRANCH_COVERAGE_UNTESTABLE
                return true;

            addr = reinterpret_cast<SYMBOL_TYPE>(symbol_address);

            return false;
        }

        /**
        * \brief
        *     Resolve the given symbol name and return the address in
        *     the shared library that matches it.
        * \pre
        *     isValid() returns true.
        * \param[in]
        *     symbol_name The name of the symbol that should be looked
        *     up in the currently loaded library. Note that symbol
        *     name lookup is subject to platform-dependent behaviour.
        *     You should, in general, only lookup C symbols. If you
        *     want to lookup a C++ symbol then you have to declare it
        *     as 'extern "C"' to prevent name mangling by the
        *     compiler.
        *     <br>
        *     Accessing a C++ class is usually done via a class
        *     instance pointer returned via an 'extern "C"' declared
        *     function and an abstract interface that is implemented
        *     by that class instance.
        * \param[out] addr
        *     Here the address of the loaded symbol is returned. It
        *     can be NULL which means the symbol has not been assigned
        *     a value yet. This needs not to be an error. Check the
        *     return value to distuingish.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        * \errors
        *     ipl::CommonError with IDs:
        *
        *     INVALID_USAGE if isValid() returns false
        *
        *     SharedObj::Error with IDs:
        *
        *     RESOLVE_FAILED if the symbol could not be resolved for
        *     some system specific reason.
        * \note
        *     There is no unicode variant of resolve due to WIN32
        *     systems not supporting unicode symbols in shared
        *     libraries. Also using unicode shared library symbols
        *     seems a strange idea considering the C programming
        *     language doesn't allow any non-ASCII characters in their
        *     identifiers. Linkers have a hard enough job already with
        *     name mangling and introducing unicode there seems
        *     unreasonable.
        **/
        bool resolve(const char* const symbol_name, void *&addr) const;

        //! returns wheter currently a valid library is loaded
        bool isValid() const;

    protected:
        /**
        * \brief
        *     Destroys the object. Causes all previously resolved
        *     symbols and the loaded shared library to become invalid.
        * \note
        *     If a library was loaded multiple times by multiple
        *     objects then it may still be present after destruction.
        *     But don't ever count on that.
        **/
        virtual void destroy();

    private:
        //! Reference to system library object
        LibraryHandle m_lib;
    };

}  // end of namespace osal

//#if defined (IPL_OS_ANDROID) || defined (IPL_OS_LINUX) || defined (IPL_OS_QNX)
#if defined (IPL_OS_POSIX) || defined (IPL_OS_INTEGRITY)
#    include "posix/SharedObj.inl"
#elif defined (IPL_OS_WINPC)
#    include "win32/SharedObj.inl"
#else
#    error "error undefined IPL_OS_ variant"
#endif

#endif
