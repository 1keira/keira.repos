/*
    Copyright 2021 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_POWERSTATE_IPOWERSTATEPLUGIN_HXX
#define TRACING_POWERSTATE_IPOWERSTATEPLUGIN_HXX

#include <set>
#include <string>
#include <cstdint>

namespace tracing
{

class IPowerStateHandler;

/*!
 *    \brief
 *        Interface class for a power state plugin which provides available power
 *        states and also tracks the current system power state.
 *
 *        It is loaded by the power state handler.
 */
class IPowerStatePlugin
{
public:
    //! \brief Returns the plugin name.
    static const char * getName() { return nullptr; }

    //! \brief Returns the version of the plugin.
    static int32_t getVersion() { return 0; }

    /*!
     *  \brief
     *      Creates a new power state plugin.
     *
     *  \return
     *      A pointer to the newly created plugin.
     */
    static IPowerStatePlugin * create() { return nullptr; }

    /*!
     *  \brief
     *      Destroys a power state plugin.
     *
     *  \param
     *      plugin A pointer to a plugin.
     */
    static void destroy(IPowerStatePlugin * plugin) { delete plugin; }

    //! \brief Virtual destructor.
    virtual ~IPowerStatePlugin() {/* nop */}

    /*!
     *  \brief
     *      Initializes the power state plugin.
     *
     *  \param
     *      handler The valid instance of a power state handler.
     */
    virtual bool init(IPowerStateHandler * handler) = 0;

    //! \brief Shut down the plugin.
    virtual void exit() = 0;

    /*!
     *  \brief
     *      Provides the system specific power states, usually to the
     *      power state handler.
     *
     *  \param
     *      valid_states The list of valid power state names.
     */
    virtual void getValidPowerStates(std::set<std::string> & valid_states) = 0;
};

} // end of namespace tracing

#endif /* TRACING_POWERSTATE_IPOWERSTATEPLUGIN_HXX */

