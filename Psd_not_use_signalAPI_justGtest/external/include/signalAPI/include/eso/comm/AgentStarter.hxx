/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef COMM_AGENTSTARTER_HXX
#define COMM_AGENTSTARTER_HXX

/* standard header files */

/* project-specific header files */
#include <ipl_config.h>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <common/streams/ostream.hxx>

#include <common/types/string.hxx>
#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>

// embed a variable tagging the comm header version used
// for builds with gcc
#if __GNUC__ >= 4
#ifndef comm_EXPORTS
__attribute__((used)) static const char* ESO_COMM_VERSION = COMM_LIB_VERSION;
#endif
#endif
namespace comm {

    struct AgentExtraParam;

    /**
     * \brief
     *  An interface to receive status events while the comm agent starts.

     *  An implementation of this interface receives events from the starting agent.
     *  Those events either report the agent as started or the start as aborted.
     *  In case of an abort the reason is reported too.
     * \note
     * Make sure your AgentStarterEventReceiver lives at least as long as your AgentStarter.
     * \note
     * Events may be reported synchronously or asynchronously with regards to the AgentStarter::start call.
     * \see comm::AgentStartStatus
     **/
    class COMM_EXPORT AgentStarterEventReceiver {
        public:
            //! The event.
            enum Event { StartOK        /*!< The agent did start. */
                        ,StartAborted   /*!< The agent aborted its start. */
                        };
            //! More detail on the event. Even more details can usually be found in the trace log.
            enum Detail { None                      /*!< No details are available. */
                        ,BrokerTransportSetupFailed /*!< The agent was not able to contact the broker. */
                        ,AgentTransportSetupFailed  /*!< The agent was not able to setup its incoming transport channel(s). */
                        ,BrokerProxyFailure         /*!< The proxy to the broker reported an error. */
                        ,ConfigFailure              /*!< There was an error while processing configuration data. */
                        ,InternalError              /*!< Some error in the internal logic. See trace or logging output. */
                        ,NotFirst                   /*!< Start was already called in the same process */
            };
            //! Constructor.
            AgentStarterEventReceiver() {}
            //! Destructor.
            virtual ~AgentStarterEventReceiver() {}
            //! Receives an event and details.
            virtual void receive ( const Event& ev, const Detail& de ) = 0;
    };

    /**
     * \brief
     * A helper class that receives comm agent start events.

     * This implementation of comm::AgentStarterEventReceiver can be used to poll the state of the comm agent
     * start or wait until the agent is started.<br>
     * Please note the example code.
     */
    class COMM_EXPORT AgentStartStatus : public comm::AgentStarterEventReceiver {
        public:
            //! The state of the agent start-up.
            enum State { Unknown    /*!< No event received yet, state unknown. */
                        ,Started    /*!< The agent started successfully */
                        ,Aborted    /*!< The agent aborted the start-up. */
                        };
            //! Default constructor.
            AgentStartStatus();
            //! Destructor.
            ~AgentStartStatus() override;
            //! Receives agent start-up events.
            /*!
             * \see comm::AgentStarterEventReceiver
             */
            void receive ( const Event& ev, const Detail& de ) override;

            //! Answers if the agent did start up.
            bool isStarted() const;
            //! Answers the start-up state.
            State getState() const;
            //! Answers the detail.
            AgentStarterEventReceiver::Detail getDetail() const;

            //! Waits until the agent start-up is completed or aborted or times out.
            /*!
             * Blocks until one of the following conditions holds true:
             * <ul>
             * <li>The agent completed the start-up successfully.</li>
             * <li>The agent aborted the start-up.</li>
             * <li>The timeout is reached before any of the previous conditions holds true.</li>
             * </ul>
             * \param timeout the maximum time the call blocks waiting for successful start or abort. A timeout value of 0 or less is
             * silently changed to 1. There is no 'wait forever'.
             * \return The state of the start-up when the call returns. State \ref Unknown means that neither successful
             * start nor abort happend within the time limit.
             * \note
             * In case of an aborted start-up getDetail() reports the reason.
            */
            State waitUntilStarted(const osal::TimeT timeout) IPL_NOEXCEPT;

            //! prints the state to an output stream.
            ipl::ostream& print(ipl::ostream& out) const;

        private:
            State                                   m_state;
            osal::Mutex                             m_mutex;
            osal::Condition                         m_condvar;
            comm::AgentStarterEventReceiver::Detail m_detail;
    };

    //! output stream operator.
    inline ipl::ostream& operator << (ipl::ostream& out, comm::AgentStartStatus const& st) { return st.print(out); }


    /**
     * \brief
     * Starts the comm Agent.

     * Starts the comm agent in the start() method. When the instance is destroyed the comm agent shuts down.
    */
    class COMM_EXPORT AgentStarter  {
        public:
            //! Constructor with process and node name.
            // node name is obsolete
            AgentStarter( const ipl::string& name, const ipl::string& node) IPL_NOEXCEPT;
            //! Constructor with process name.
            explicit AgentStarter( const ipl::string& name) IPL_NOEXCEPT;
            /* Constructor that allocates a dynamic agent id.
             *
             * \param id if set and valid the agent try to allocate it
             * Otherwise an arbitrary dynamic id will be requested
             */
            explicit AgentStarter( comm::AgentID id=comm::AgentID() ) IPL_NOEXCEPT;
            //! Destructor.
            ~AgentStarter() IPL_NOEXCEPT;
            //! Starts the comm agent.
            /*!
             * The agent initializes and connects to the broker. The way errors are reported and
             * if connecting to the broker is retried depend on the parameters.
             *
             * \param cb a pointer to an event receiver for start-up events.
             * Can be nullptr in which case no events are reported.
             *
             * \param retry if false, the agent tries once to connect to the broker.
             * If true the agent keeps retrying to connect to the broker.
             * Timeout between retries and the maximal number of retries are configured in
             * the comm_agent_connect_retries and comm_agent_connect_retry_delay configuration
             * settings.
             *
             * \return true on success.
             *
             * \note
             * Please note that the return value semantics differ from most other framework
             * functions, which return true on error.
             *
             *
             * \errorindicator
             *      Asynchronously via the cb parameter.
             */
            bool start( AgentStarterEventReceiver* cb=nullptr, bool retry=true ) IPL_NOEXCEPT;

            AgentID getAgentID() IPL_NOEXCEPT;

            //! Internal
            AgentStarter( const ipl::string& name, const AgentExtraParam* param ) IPL_NOEXCEPT;
        private:
            AgentStarter(const AgentStarter&);
            AgentStarter& operator=(const AgentStarter&);

            AgentStartStatus            m_status;   // default, used if none is passed

    };

    /**
     * \example
     * \code
     * #include <comm/AgentStarter.hxx>
     * int main (int argc, const char** argv ) {
     *  // some setup code
     *  //...
     *
     *  // NOTE! startStatus must live as long as the agent
     *  comm::AgentStartStatus startStatus;
     *  comm::AgentStarter agent("your process name","your node name");
     *  agent.start(&startStatus);
     *
     *  // do something that does not need comm ...
     *
     *  // wait at max 10 seconds for the agent to start
     *  // Note if the start failed, the call will not wait, but return immediately
     *  if ( startStatus.waitUntilStarted(10000) != comm::AgentStartStatus::Started ) {
     *      // handle timeout or abort ...
     *      // e.g. print some message to stderr
     *      ipl::clog << "Could not start comm agent: "<<startStatus<<ipl::endl;
     *      // ...
     *  }
     *  // other code ...
     * }
     * \endcode
     */
}

#endif // COMM_AGENTSTARTER_HXX
// vim: ts=4 sw=4:

