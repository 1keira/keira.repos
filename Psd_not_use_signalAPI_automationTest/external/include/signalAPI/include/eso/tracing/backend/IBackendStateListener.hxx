/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IBACKENDSTATELISTENER_HXX
#define TRACING_IBACKENDSTATELISTENER_HXX

#include <common/types/string.hxx>

namespace tracing
{

/*!
 *  \brief
 *      Interface class which allows listening to backend state changes.
 */
class IBackendStateListener
{
public:
    //! \brief Virtual destructor.
    virtual ~IBackendStateListener() {};

    /*!
     *  \brief
     *      Informs that a backend got connected to the trace core.
     *
     *  \param
     *      backend_id The unique backend id.
     *  \param
     *      backend_key The backend name.
     *  \param
     *      backend_flags The backend flags as defined in IBackend.
     */
    virtual void backendConnected(int16_t backend_id, const ipl::string & backend_key,
                                  int32_t backend_flags) = 0;

    /*!
     *  \brief
     *      Informs that a backend got disconnected from the trace core.
     *
     *  \param
     *      backend_id The unique backend id.
     */
    virtual void backendDisconnected(int16_t backend_id) = 0;
};

} // end of namespace tracing

#endif /* TRACING_IBACKENDSTATELISTENER_HXX */

