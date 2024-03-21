/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_ASTRA_ASTRA_HXX
#define UTIL_ASTRA_ASTRA_HXX
/****************************************************************************/

#include <util/util_dso.h>
#include <common/error/ErrorType.hxx>

/****************************************************************************/

namespace util {
    
/****************************************************************************/

    /*!
        \brief Newstyle async communication
        
        \see \ref util_astra_page for background.
    */
    namespace astra {

/****************************************************************************/

        //! \brief Root of astra's error hierarchy
        extern UTIL_EXPORT ipl::ErrorType error;

/****************************************************************************/

        /*
            The other reason for this file to exist is to put doxygen docu
            where apidoc may find it.
        */

        /*!
            \page util_astra_page Asynchronous %Transport Principles
            
            The new %Transport system is made optimized for asynchronous
            programs. When using it, your program \e should be built around
            a message queue and handler thread like osal::Dispatcher, using a
            Transport::Client.
            This allows you to handle incoming data asynchronously, lock free,
            flexibly and overall in a solid, stable way.
            You \e can use synchronous callbacks instead by injecting your own
            implementation of \ref Transport::RawCallbacks,
            but this is not recommended as long as you don't have a
            very good reason.
            
            \section util_astra_basic_use_page Basic use
            
            \subsection util_astra_basic_use_async_page Async architecture
            
            A basic asynchronous program has a central queue of messages /
            events / deferred calls / whatever
            and a thread that processes them one by one.
            This sequential processing massively reduces the need for locking
            as well as the number of threads.
            
            So your program needs, besides the normal framework stuff,
            at least a queue for the Messages, a Dispatcher running the
            main loop and a Notifier that connects them:
            \code
            // setup async engine
            osal::Dispatcher::VanillaNotifier notifier;
            osal::Dispatcher dispatcher{notifier};
            osal::Dispatcher::VanillaQueue queue{notifier};
            dispatcher.add_low_prio(queue);
            
            // setup application logic
            SomeThingStuffGetsCalledOn some_thing_stuff_gets_called_on;
            SomeThingThatPushesIntoTheQueue some_thing_that_pushes_into_the_queue(queue);
            
            // start async engine
            dispatcher.run();

            // The correct way to end a multithreaded program
            iplbase::exit(0);
            \endcode
            \see \ref AsyncBasicUnlimitedSample.cxx,
            \ref AsyncBasicBackpressureSample.cxx
            
            \subsection util_astra_basic_use_transport_page Client
            
            As a %Transport client you need a Transport to some service, duh.
            Typically the kind of transport mechanism and the actual endpoint
            will be configurable in some way, so you will get the
            %Transport instance from the \ref util_astra_factory_page "factory".

            You can send your data via the respective %Transport's
            \ref Transport::send() "send()" method, but that can temporarily
            fail due to backpressure, i.e. the other side not being able to
            receive right now, so you need to handle that case.
            The easiest way is to use a \ref Transport::Hold "Hold".
            
            In order to get callbacks from the %Transport you need some
            business logic object inheriting Transport::Client.
            This is already asynchronous, i.e. uses some queue.
            It will call your transport_received() and transport_error()
            methods from the async system's central thread.
            
            \code
            class ClientLogic: public util::astra::Transport::Client {
                
            public:
                ClientLogic(osal::Message::Sink &queue,
                            util::astra::Transport &transport):
                    Client(queue), hold(transport) {}
                
            protected:
                void transport_received(util::astra::Transport *transport,
                                        const ipl::Buf &data) IPL_NOEXCEPT override;
                void transport_error(util::astra::Transport *transport,
                                    const std::string &error) IPL_NOEXCEPT override;
                void transport_retry(util::astra::Transport *transport) IPL_NOEXCEPT override;
                
                util::astra::Transport::Hold hold;
            };
            
            void ClientLogic::transport_received(util::astra::Transport *transport,
                                                 const ipl::Buf &data) IPL_NOEXCEPT
            {
                // maybe differentiate on transport...
                
                do_something_with(data);
                data.free();
            }
            
            void ClientLogic::transport_retry(util::astra::Transport *transport) IPL_NOEXCEPT
            {
                hold.retry_send();
                maybe_restart_something_that_wasnt_allowed_to_send();
            }
            
            ...
            
            // setup application logic
            const char *peer="tcp:localhost:1234";
            std::unique_ptr<util::astra::Transport> transport=util::astra::create_transport(peer);
            if(!transport)
                waah_error_crash_and_burn();
            ClientLogic client_logic(queue, *transport);
            util::astra::Transport::Connect transport_to_logic(*transport, client_logic);
            
            ...
            
            // send something
            if(client_logic.hold) {
                // do nothing, maybe retrigger later in ClientLogic::transport_retry()
            } else {
                ipl::Buf msg=transport->malloc(some_number_of_bytes);
                fill_with_data(msg);
                client_logic.hold.send(msg);
            }
            
            \endcode
            \see \ref AsyncTransportChatClient.cxx
            
            \subsection util_astra_basic_use_listener_page Server
            
            %A server has one or more \ref Listener "Listeners" that wait
            for incoming connections.
            Those Listeners will typically need to be configurable,
            so again use the factory to create them.
            They "receive" readily connected Transports that can be used
            much the same way as in the client case above.
            
            \code
            class ServerLogic: public util::astra::Listener::Client {
            public:
                ServerLogic(osal::Message::Sink &queue):
                    Client(queue) {}
                
            protected:
                void listener_accepted(util::astra::Listener *listener,
                                       util::astra::Transport *transport) IPL_NOEXCEPT override;
                void listener_error(util::astra::Listener *listener,
                                    const std::string &error) IPL_NOEXCEPT override;
            };
            
            ...
            
            // setup application logic
            const char *address="tcp:localhost:1234?service";
            std::unique_ptr<util::astra::Listener> listener=
                util::astra::create_listener(address);
            if(!listener)
                waah_error_crash_and_burn();
            ServerLogic server_logic(queue);
            util::astra::Listener::Connect listener_to_logic(*listener, server_logic);
            \endcode
            
            There are several possible ways to manage parallel connections.
            If you need a per-connection object anyway, it can hold onto the
            Transport and the Transport::Connect and implement the callbacks.
            \code
            class PerConnectionLogic: public util::astra::Transport::Client {
            
            public:
                PerConnectionLogic(osal::Message::Sink &queue,
                                   util::astra::Transport *transport):
                    Client(queue),
                    transport(transport),
                    transport_to_this(*transport, *this),
                    hold(transport) {}
                
            protected:
                void transport_received(util::astra::Transport *transport,
                                        const ipl::Buf &data) IPL_NOEXCEPT override;
                void transport_error(util::astra::Transport *transport,
                                    const std::string &error) IPL_NOEXCEPT override;
                void transport_retry(util::astra::Transport *transport) IPL_NOEXCEPT override;
                
                ipl::unique_ptr<util::astra::Transport> transport;
                util::astra::Transport::Connect transport_to_this;
                util::astra::Transport::Hold hold;
            };
            
            void ServerLogic::listener_accepted(util::astra::Listener *listener,
                                                util::astra::Transport *transport) IPL_NOEXCEPT
            {
                some_container_of_PerClientConnection.emplace(queue, transport);
            }
            \endcode
            
            Another way that sometimes comes in handy
            is to have the central ServerLogic object inherit
            Transport::Client and implement its callbacks, only store the
            raw Transports and call \ref Transport::set_client()
            "set_client(&server_logic)" on each of them instead of
            creating Transport::Connect objects.
            The downside is that this doesn't play well with Transport::Hold.
            
            \see \ref AsyncTransportChatServer.cxx
            
            \subsection util_astra_basic_use_contingent_page Passing on backpressure
            
            If the messages your, say, server receives trigger sending more
            messages you might run into the situation that sending fails
            due to backpressure and you want to stop receiving so you
            won't overrun any queues.
            The mechanism for this is the \ref osal::Message::Contingent "Contingent".
            It wraps your queue and disallows push() after some number of
            messages -- typically one.
            If you pass this to the constructor of your %Transport::Client
            instead of the raw queue, the %Transport stops after one
            received message (or other callback).
            When you are ready to receive more, call
            \ref osal::Message::Contingent::more() "contingent.more()".
            
            \subsection util_astra_basic_use_deletion_page Dynamically deleting a Transport::Client
            
            When you are creating and destroying your clients dynamically,
            you need to ensure that no callbacks to them are still stuck in the
            queue on delete, or else those will segfault.
            <b>Transport::Clients need to stay alive until there will be no more
            callbacks to them.</b>
            
            The basic strategy for this is to first disconnect the client
            from all Transports or Listeners that might enqueue any calls to it
            (typically by deleting any \c Connect object referencing them),
            thus guaranteeing that no new calls get into the queue.
            Then you enqueue an asynchronous call to delete the client.
            This will be after any callbacks, so it can safely delete the
            client.
            This can be as simple as a lambda calling \c delete.
            
            \see \ref AsyncBasicDynamicHandlersSample.cxx
            
            \section util_astra_creation_page Creating a Transport or Listener
            
            If you need a certain point-to-point Transport in your Application,
            create one. Just create the object, locally, with \c new, with
            \c make_unique, whatever, introduce it to your client (see below)
            and you're in business.
            The constructor is synchronous, obviously, but actually connecting
            to the communication peer under the hood may be very asynchronous.
            You can already call everything on your new Transport object,
            but sending will most probably fail at first.
            This is not a problem as you get the usual retry callbacks.
            
            Typically you will not know statically what exactly you need, but
            it will rather be configurable.
            The actual type and parameters will be described by some string,
            the Descriptor.
            Then you call create_transport() with that string and get a
            corresponding Transport instance back.
            
            Or when you implement a server, you create a Listener (e.g. a
            listening TCP socket), again either by hand or by create_listener()
            from a Descriptor string, and that calls you back with a readily
            setup Transport instance for any incoming connection.
            
            \section util_astra_backpressure_subpage The general backpressure protocol
            
            Throughout the whole system of Transports, Listeners and the
            \ref osal::Message::Sink "Messagequeue" there is a common pattern of
            pushing data forward against potential backpressure.
            This means normally some data source calls some receiver "here's
            some data", but the receiver can return "go away, I'm busy".
            Later the receiver can retrigger delivery by calling "try again" on
            the source which in turn retries the original call "here's some
            data".
            This repeats until the receiver finally returns "OK, got it".
            
            So there is always a pair of interfaces, one data client (receiver)
            with something like a <code>bool received(data, source)</code>
            method returning whether the data has been accepted or not
            and one data source with a <code>void retry()</code> method that
            retriggers a previously failed call to <code>received()</code>.
            
            This pattern repeats through all the data path,
            between Transport::send() and the synchronous Transport::RawCallbacks
            or the asynchronous Transport::Client,
            between Transport::RawCallbacks::received() and Transport::retry(),
            between osal::Message::Sink::push() and
            osal::Message::Pusher::retry().
            
            \subsection util_astra_backpressure_hold Holding under backpressure
            
            Trouble with that whole backpressure business is that you allocate
            some kind of message object and either succeed or fail to give
            ownership away.
            Now you have (potentially) to store the object for retrying later,
            which is cumbersome, or you have to throw it away and allocate a
            new one whenever retrying, which is a bit less cumbersome but
            inefficient.
            
            The common pattern here is a Hold, a convenience thing that combines
            sending/pushing, retrying and if needed storing for later into one.
            Both osal::Message::Hold and util::astra::Transport::Hold have a
            send/push method that never denies sending but always takes
            ownership and stores if necessary, a retry mechanism that is
            automatically (%Message) or manually (%Transport) triggered and a way
            to find out if you are allowed to send or whether it still waits
            to get the pending object out.
            This is an extra object rather than part of the Transport or
            Message::Sink as you need one per source, not one per sink.
            
            You do not \em need to use a Hold, but it is highly recommended
            as it saves you some hassle as well as bug opportunities.
            
            \section util_astra_clients_subpage Registering callback clients
            
            astra is built around asynchronous callbacks.
            In many cases the callback receivers ("clients") can register and
            unregister dynamically, and they will do so from different threads.
            This means we need a model for threadsafety.
            
            Obviously the list of clients (or whatever) needs to be guarded
            by a mutex. But a deregistering client also needs a guarantee that
            after deregistering is through there will be no more callbacks to
            it, and any already pending callback is through,
            so it can be safely destroyed.
            This requires the mutex to be held during callbacks, and in order
            to be able to unregister during a callback the mutex must be
            recursive.
            
            So everything in the vicinity of astra that has some kind of dynamic
            registration of client objects (including the one-to-one one between
            Transport and Transport::RawCallbacks) gives the guarantee that the
            client can be safely destroyed after deregistration has returned,
            <em>except when deregistration is triggered from within a callback</em>
            -- in that case the client can safely be destroyed after the callback
            has returned.
            On the flip side this means that registration calls (and maybe more)
            may not be issued with any client side lock held if the callback
            might also take it, as this will deadlock.
            
            The pattern of registration after creation time implies, at least
            for single-client services, that the service cannot work fully
            before the client has registered and after it has deregistered.
            This again implies that any underlying activity may not be
            started/stopped in the constructor/destructor but dynamically at
            (de)registration time.
            The implementation (e.g. of some Transport) must consider this and
            ensure that activity actually gets started when the last
            precondition is met, regardless of the order the preconditions
            (clients, transport, whatnots) actually trundle in.
            
            \subsection util_astra_clients_setter_subpage Setting a Client for a Transport or Listener
            
            Now you would think it is easy to introduce Transport and Client
            to each other, just have the Clients' base class constructor and
            destructor call Transport::set_client() as needed and everything
            is fine and dandy. Unfortunately set_client() calls back into a
            virtual method, and that one might call a virtual method of the
            Client, but at that moment the Client is not fully constructed yet
            and all hell breaks loose.
            To mitigate that, set_client() must be called after the Client
            object, derived class or not, is fully constructed.
            
            So we introduce yet another indirection, Transport::Connect.
            This is a guard class calling
            <code>transport.set_client(&client)</code> in its constructor and
            <code> transport.set_client(nullptr)</code> in its destructor.
            Create one of these after your Transport and Transport::Client
            and make sure to give it a name so it actually sticks around.
            \c \<transport>_to_\<client> would be a canonical name, i.e.
            \code
            SomeTransport t1;
            SomeClient c1;
            util::astra::Transport::Connect t1_to_c1(t1, c1);
            \endcode
        */
    
/****************************************************************************/

    }  // end of namespace astra
}  // end of namespace osal

/****************************************************************************/
#endif
