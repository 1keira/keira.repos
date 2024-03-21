/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_SOLOADER_HXX
#define UTIL_SOLOADER_HXX

#include <ipl_config.h>

#include <common/types/map.hxx>
#include <common/types/string.hxx>
#include <common/NonCopyable.hxx>
#include <osal/SharedObj.hxx>
#include <util/util_dso.h>

namespace util
{

typedef int32_t SharedObjId;

/**
 * \brief
 *     Handling of Collections of osal::SharedObject's

 *     A class to load a number of objects from a number of shared
 *     libraries. The shared object references are encapsulated inside.
 *     The actual libs can be accessed directly via the []-operator.
 * \note
 *     Currently it is not possible to use this class with unicode
 *     paths to shared objects.
**/
class UTIL_EXPORT SOLoader :
    public ipl::NonCopyable
{
public:
    //! Value to trigger loading of all libs in one go
    static const SharedObjId LOAD_ALL_ID;
    //! Represents an undefined id, i.e. an error
    static const SharedObjId ID_UNDEF;
    //! Only initialise ref counting and state
    SOLoader() IPL_NOEXCEPT;
    //! Unload all libraries.
    ~SOLoader() IPL_NOEXCEPT;

    /**
     * \brief
     *     Register new library at container

     *    The functions return value represents an arbitrary
     *    number which cannot be assumed to be iteratable.
     *
     *    If you intend to apply any other functions specifically
     *    for the newly loaded library then you need to store the
     *    id.
     *
     *    This function does not perform any actual actions for
     *    the library. It merely adds the library path to enable
     *    further operations provided by this class.
     * \errorindicator
     *    via hasError() and return code of ID_UNDEF
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - ipl::PARAMETER_OUT_OF_RANGE if no more libraries can
     *    be loaded
     * \return
     *    valid id if successful or invalid id (ID_UNDEF)
    **/
    SharedObjId addLib(const char* location) IPL_NOEXCEPT;

    /**
     * \brief
     *    Unload a single lib by ID
     * \errorindicator
     *    via hasError()
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - ipl::PARAMETER_OUT_OF_RANGE if no more libraries can
     *    be loaded
     *
     *    plus any errors described at osal::SharedObj::unload()
    **/
    void unloadLib(SharedObjId id) IPL_NOEXCEPT;

    /**
     * \brief
     *    Load one or more libs from the container

     *    The function offers two options to load libs: either
     *    state one libs-id or state 'LOAD_ALL_ID' which triggers
     *    a load of all previously added libs.
     * \note
     *    Errors that occur during loading of the shared object
     *    are handled by load() internally. If the returned number
     *    of loaded objects is less than the expected number of
     *    loaded objects then something went wrong while loading
     *    one or more of the object.
     * \return
     *    number of successfully loaded objs
     * \param
     *    id which shared-obj to load, if 'LOAD_ALL_ID', then all
     *    get loaded.
     * \errorindicator
     *    via hasError() and return code of < 0 (in case of id !=
     *    LOAD_ALL_ID) or return code != num of added libs
     * \errors
     *    ipl::CommonError with IDs:
     *
     *    - INT_OUT_OF_RANGE if the given \c id couldn't be found
     *    in the SOLoader.
    **/
    int32_t load(SharedObjId id) IPL_NOEXCEPT;

    /**
     * \brief
     *    Try unloading all contained libs in one go.

     *    The function tries to unload all previously added libs.
     *    This may raise an error in the case a libs never got
     *    'loaded' at any time or if it cannot be unloaded by the
     *    system itself.
     *
     *    In case of error some libraries may already be unloaded
     *    and some not.
     * \errorindicator
     *    via hasError()
     * \errors
     *    Any errors described at osal::SharedObj::unload()
    **/
    void unload() IPL_NOEXCEPT;

    /**
     * \brief
     *    Directly access libs stored in the container

     *    The function returns a reference to an existing 'added'
     *    lib. If the reference does not exist, the function call
     *    will assert.
     * \errors
     *    none. If the selected id isn't existing then an assertion occurs.
    **/
    osal::SharedObj& operator[] (SharedObjId id) IPL_NOEXCEPT;

    //! returns true if the last operation failed, false otherwise
    bool hasError() const IPL_NOEXCEPT
    { return m_has_error; }
protected:
    void setError() IPL_NOEXCEPT
    { m_has_error = true; }

    void resetError() IPL_NOEXCEPT
    { m_has_error = false; }
private:
    bool m_has_error;
    //! Map to handle Location to read Lib-Obj mapping
    ipl::map<ipl::string, osal::SharedObj> m_strobj_map;
    //! Map to handle Obj-Id to Location lookups
    ipl::map<SharedObjId, ipl::string> m_idstr_map;
    //! Internal counter for id-handling.
    SharedObjId m_id;
}; // end class

} //end ns

#endif // include guard
