/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IFRONTENDLISTENER_HXX
#define TRACING_IFRONTENDLISTENER_HXX

#include <tracing/tracing_dso.h>
#include <common/stdint.h>
#include <common/types/vector.hxx>
#include <common/types/map.hxx>
#include <common/types/string.hxx>
#include <stdlib.h>

namespace tracing
{

class Frontend;
class EntityURI;

/*!
 *    \brief
 *        Interface class for a frontend listener.

 *        An implementation of this class is used by the trace frontend (i.e. the
 *        low-level client API) to notify the high-level frontend about changes in
 *        the trace model or callback execution requests.
 *        If you use the high-level client API, i.e. the Client.hxx header which
 *        gets automatically included by tracing.hxx you don't need to know anything
 *        about this interface. It is implemented by the Client and may need to be
 *        implemented if you write your own high-level client or if you use the
 *        low-level tracing API only.
 */
class TRACINGIMPL_EXPORT IFrontendListener
{
public:
    //! \brief Default constructor.
    IFrontendListener() :
        m_fid(-1),
        m_frontend(nullptr)
    {
    }

    /*!
     *    \brief
     *        Virtual destructor.
     */
    virtual ~IFrontendListener() {/* nop */}

    /*!
     *    \brief
     *        Initialise the frontend listener.
     *
     *    \param
     *        fid The frontend plugin id.
     *    \param
     *        frontend A pointer to the frontend instance, acquired by e.g. calling
     *        Frontend::getTraceFrontend()
     */
    virtual void init(int16_t fid, Frontend * frontend) = 0;

    /*!
     *    \brief
     *        Shut down the frontend listener.
     */
    virtual void shutdown() = 0;

    /*!
     *    \brief
     *        Callback execution requested.
     *    \param
     *        cbid The callback's ID as returned from the frontend when registering
     *        the callback function.
     *    \param
     *        data User-supplied data as received from the backend.
     *    \param
     *        len Size in bytes of the memory, data is pointing to.
     */
    virtual void executeCallback(int32_t cbid, void * data, size_t len) = 0;

    /*!
     *    \brief
     *        Propagate change of filter level.
     *    \param
     *        uri The URI of the entity whose level was changed.
     *    \param
     *        level The new level of the entity.
     *    \return
     *        true if the level change was handled, false if this entity is
     *        not handled by this listener.
     */
    virtual void requestFilterLevel(const EntityURI & uri, int16_t level) = 0;

    /*!
     *    \brief
     *        Quit requested from one of the backends.
     */
    virtual void requestQuit() = 0;

    /*!
     *    \brief
     *        Supplies arguments to the frontend listener.
     *    \param
     *        args The arguments for the frontend listener. The contents is
     *        completely implementation-dependant and could e.g. be a set of
     *        files, etc. A frontend listener implementation should check
     *        m_args and use them accordingly. This usually contains a set of
     *        key-value pairs supplied in a map.
     */
    void setArgs(const ipl::map<ipl::string, ipl::string> & args)
    {
        m_args = args;
    }

    /*!
     *    \brief
     *        Provides the frontend plugin id.
     *    \return
     *        The plugin's ID.
     */
    int16_t getId() const
    {
        return m_fid;
    }

protected:
    ipl::map<ipl::string, ipl::string> m_args;
    int16_t m_fid;
    Frontend * m_frontend;
};

inline void IFrontendListener::init(int16_t fid, Frontend * frontend)
{
    m_fid = fid;
    m_frontend = frontend;
}

} // end of namespace tracing

#endif /* TRACING_IFRONTENDLISTENER_HXX */

