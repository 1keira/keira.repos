#ifndef TRACING_POWERSTATE_IPOWERSTATEHANDLER_HXX
#define TRACING_POWERSTATE_IPOWERSTATEHANDLER_HXX

namespace tracing
{

/*!
 *    \brief
 *        Interface class for a power state handler which gets notified upon
 *        system power state changes.
 */
class IPowerStateHandler
{
public:
    //! \brief Virtual destructor.
    virtual ~IPowerStateHandler() {/* nop */}
    //! \brief Indication of a changed power state.
    virtual void powerStateChanged(const std::string & power_state) = 0;
};

} // end of namespace tracing

#endif /* TRACING_POWERSTATE_IPOWERSTATEHANDLER_HXX */

