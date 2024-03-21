/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_PLUGINLOADER_HXX
#define UTIL_PLUGINLOADER_HXX

#include <ipl_config.h>

// common includes
#include <common/types/vector.hxx>
#include <common/types/utility.hxx>
#include <common/error/Error.hxx>

// osal includes
#include <osal/SharedObj.hxx>
#include <osal/SysError.hxx>

// util includes
#include <util/util_dso.h>


namespace util
{

/**
 * \brief
 *     Shared object plugin loading helper

 *     The PluginLoader loads shared object files from a given
 *     directory according to a specified name pattern and checks those
 *     libraries for presence of a certain shared library symbol.
 *
 *     All matching libraries will then be loaded and returned to the
 *     client.
 * \note
 *     This class does currently not support shared objects at unicode
 *     paths
 **/
class UTIL_EXPORT PluginLoader
{
public: // constants

    //! \brief
    //! platform-independent library prefix: can be used for PI
    //! plugin name building
    static const char* const LIBPREFIX;
    //! \brief
    //! platform-independent library suffix: can be used for PI
    //! plugin name building
    static const char* const LIBSUFFIX;

    enum PluginLoaderErrors
    {
        // directory could not be accessed
        ACCESS_ERROR = 0
    };

    //! specific error type
    static ipl::ErrorType Error;

public: // functions

    /**
     * \brief
     *     Loads all plugin libraries matching the given parameters

     *     Searches in the absolute or relative path \a libdir for
     *     all libraries matching \a pattern that contain symbol
     \a symbol. All matching libraries will be loaded into the
     *     processes address space and can be accessed via
     *     getPlugins().
     *
     *     If \a libdir does not exist or could not be opened,
     *     DirAccessError is thrown and the object will not be
     *     constructed. If no filenames match \a pattern or no
     *     libraries contain \a symbol then no libraries will be
     *     loaded. The object will still be constructed.
     * \param[in] libdir
     *     Absolute or relative path to the directory that is
     *     supposed to contain plugin libraries.
     * \param[in] pattern
     *     A pattern that may contain one wildcard (asterisk '*',
     *     see util::Directory::search()). Plugin files to be
     *     loaded need to to match this pattern. e.g.  LIBPREFIX +
     *     "*" + LIBSUFFIX.
     * \param[in] symbol
     *     A shared library symbol that needs to be present in each
     *     file matching \c pattern to be considered by the
     *     PluginLoader.
     * \errorindicator
     *     via isValid()
     * \errors
     *     PluginLoader::Error with IDs:
     *
     *     - ACCESS_ERROR if \c libdir could not be accessed.
     **/
    PluginLoader(const ipl::string &libdir,
        const ipl::string &pattern,
        const ipl::string &symbol) IPL_NOEXCEPT;

    //! Returns the number of plugins that could be loaded
    size_t count() const IPL_NOEXCEPT
    { return m_plugins.size(); }

    //! \brief
    //! Returns a vector containing pairs of (basename of library,
    //! loaded shared obj)
    const ipl::vector< ipl::pair<ipl::string,
        osal::SharedObj> >& plugins() IPL_NOEXCEPT
    { return m_plugins; }

    bool isValid() const IPL_NOEXCEPT
    { return true; }
private: // members
    //! All valid plugins are stored here
    ipl::vector< ipl::pair<ipl::string,
        osal::SharedObj> > m_plugins;
};

} // end namespace

#endif
