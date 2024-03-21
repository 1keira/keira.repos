/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/****************************************************************************/
#ifndef OSAL_MESSAGE_HXX
#define OSAL_MESSAGE_HXX
/****************************************************************************/

#include <osal/osal_dso.h>
#include <common/Tag.hxx>
#include <common/Macros.hxx>
#include <common/error/Error.hxx>

#include <threadsafe/Mutex.hxx>
#include <iplbase/exceptions.hxx>
#include <set>

#include <functional>
#include <memory>

#include <stddef.h>

/****************************************************************************/

namespace osal {

/****************************************************************************/

    /*!
        \brief The base of asyncronous programming

        A Message is some bunch of information that gets passed around
        and handled in some suitable way.
        They come in two general flavours,
        event-like and asyncronous-procedure-call-like.

        An event-like message contains information about
        “This and this has happened”.
        It is supposed to pass this information to zero or more
        handlers suitable for this very type of message.
        This is done by calling the get_handled_by() method,
        possibly several times, passing a Message::Handler each time.
        The concrete Message implementation is responsible for
        determining the suitability of the passed Handler and
        calling the right method(s) with the right parameters,
        as far as applicable.

        An asyncronous-procedure-call-like message contains information to
        “Invoke that procedure with these parameters”,
        i.e. it needs no handler but can handle itself instead.
        This is done by the invoke() method.
        The concrete Message implementation is responsible for
        doing the right thing when invoked.
        It may even mutate the current set of handlers here, as
        invoke() is guaranteed to be called after finished with get_handled_by().

        As there are many ways to allocate a Message,
        depending on the concrete case,
        a uniform method of release/delete is provided, dismiss().
        If your messages do nothing special, you \b must create them
        via \c new, as the default implementation of dismiss() calls \c delete.
        If you have special needs and must create your messages differently
        you also must override dismiss().

        \see Dispatcher
    */
    class OSAL_EXPORT Message {

    public:

        class Source;
        class Sink;
        class UnlimitedSink;
        
        class Pusher;
        class Hold;
        
        class Contingent;
        class Handler;

        class Callback;

        Message() IPL_NOEXCEPT=default;
        virtual ~Message() IPL_NOEXCEPT=default;

        /*!
            \brief Have the Message handled by \a handler

            This can be called several times for several handlers.
            It must determine what to do with this handler or
            whether to ignore it completely.
            Implement for event-style messages.

            A typical implementation will look roughly like this:
            \code
            class FooHandler: public osal::Message::Handler {
            public:
                static ipl::Tag TYPE;
                void *cast(const ipl::Tag &type) IPL_NOEXCEPT override { return type==TYPE? this : nullptr; }
                void foo(int bar);
            };

            void FooEventMessage::get_handled_by(Handler *handler)
            {
                void *p=handler->cast(FooHandler::TYPE);
                if(p)
                    ((FooHandler *)p)->foo(42);
            }
            \endcode
        */
        virtual void get_handled_by(Handler *handler);

        /*!
            \brief Do any self-contained action not requiring a handler

            This must be called after get_handled_by() and before dismiss(),
            so it can even mutate the set of handlers.
            Implement for async-command-style messages.
        */
        virtual void invoke();

        /*!
            \brief “I have got this Message from a MessageSource and am done with it”

            In a simple scenario, a message would always be allocated on the Heap
            and would be deleted via \c delete.
            But depending on the concrete usecase,
            the message could also live within a pool or a preallocated ring buffer
            or whatever.
            Therefore a uniform interface is needed that deletes/releases
            ownership in the right way.

            When you get a Message pointer from a MessageSource you are the
            owner of the message.
            When you are finished processing the Message, call dismiss() to
            relinquish this ownership and do not touch the Message afterwards.

            When the message is to be allocated with \c new, dismiss()
            should simply call <tt>delete this</tt>.
            The default implementation does exactly that, so you \b must either
            create all Message objects via \c new or override dismiss().
        */
        virtual void dismiss() IPL_NOEXCEPT;

        /*!
            \brief “I want to prematurely remove you from the queue”

            Do whatever needs to be done to cleanly cancel the Message,
            return whether it can be deleted now.
            If abort() returns \c true,
            only dismiss may be called on the Message.

            This is meant for emergency-emptying a limited queue or similar.
        */
        virtual bool abort();
    };

/****************************************************************************/

    /*!
        \brief Thing you can extract \ref Message "Messages" from
        (think one end of a message queue)
    */
    class OSAL_EXPORT Message::Source {

    public:
        virtual ~Source() IPL_NOEXCEPT=default;
        //! \brief Get the next message or nullptr
        //!
        //! When you're done with the message, call its
        //! \ref Message::dismiss() "dismiss()" method.
        virtual Message *pop_nonblock() IPL_NOEXCEPT=0;
    };

/****************************************************************************/

    /*!
        \brief Thing you can stuff \ref Message "Messages" into
        (think one end of a message queue) if backpressure allows
    */
    class OSAL_EXPORT Message::Sink {

    public:
        virtual ~Sink() IPL_NOEXCEPT=default;
        //! \brief Put \a message into the queue (or whatever)
        //!
        //! Returns \c true if pushing has failed.
        //! In that case you keep ownership of \p message and should
        //! either keep it for later or dispose() of it, and it is
        //! guaranteed that pusher->retry_push() gets called once as soon as
        //! pushing is possible again.
        //!
        //! On success, \c false is returned and ownership of \c message
        //! is transferred to the Sink and ultimately to whoever handles
        //! the message later.
        virtual bool push(Message *message, Pusher *pusher) IPL_NOEXCEPT=0;
        //! \brief Forget about \p pusher possibly pending
        //!
        //! After returning, \p pusher's retry_push() method is guaranteed
        //! not to be called again, i.e. \p pusher can safely be deleted.
        //! Except if it is used in another failing push() thereafter,
        //! of course.
        virtual void forget(Pusher *pusher) IPL_NOEXCEPT=0;
    };
    
/****************************************************************************/

    /*!
        \brief Thing you can stuff \ref Message "Messages" into
        (think one end of a message queue), no backpressure
    */
    class OSAL_EXPORT Message::UnlimitedSink: public Message::Sink {
        
    public:
        //! \brief Put \a message into the queue (or whatever)
        //!
        //! By pushing the message you transfer ownership to the Sink
        //! and ultimately to whoever handles the message later.
        virtual void push(Message *message) IPL_NOEXCEPT=0;
        bool push(Message *message, Pusher *pusher) IPL_NOEXCEPT override;
    };
    
/****************************************************************************/

    /*!
        \brief Callback interface for Message::Sink
    */
    class OSAL_EXPORT Message::Pusher {
        
    public:
        virtual ~Pusher() IPL_NOEXCEPT=default;
        virtual void retry_push() IPL_NOEXCEPT=0;
    };
    
/*****************************************************************************/

    /*!
        \brief Convenient wrapper for dealing with failed push
        
        Wraps around a Message::Sink but doesn't refuse pushing.
        Instead it holds the Message internally and retries on retry_push().
        
        You must not try to push another Message while one is still being
        held.
    */
    class OSAL_EXPORT Message::Hold: public Pusher
    {
        
    public:
        explicit Hold(Sink &queue): queue(queue) {}
        
        //! \brief \c true if a message is pending
        explicit operator bool () const IPL_NOEXCEPT { return hold; }
        
        //! Contrary to Message::Sink::push() this always takes ownership of
        //! \p data. This relieves the user from the burden of conditionally
        //! holding on to a message that failed to push.
        //!
        //! On rejection the message gets stored for a later retry.
        //!
        //! If you call this while another message is already pending
        //! (as indicated by operator bool ()), \c true is returned,
        //! error is raised and \p msg is dismissed.
        bool push(Message *msg) IPL_NOEXCEPT;
        
        //! If data from some earlier rejected push is stored, delete it.
        void free() IPL_NOEXCEPT;
        
        static ipl::ErrorType error;
            
    protected:
        //! If data from some failed push is stored, the push is retried.
        //!
        //! This is automatically called by the queue.
        void retry_push() IPL_NOEXCEPT override;
        
        Sink &queue;
        Message *hold{nullptr};
    };
    
/*****************************************************************************/

    /*!
        \brief Wrapper around a Sink that limits pushs to a dynamic contingent
        
        In order to implement backpressure from some Message driven
        service to someone enqueueing these Messages, the Sink needs to
        be able to deny push unless the service allows for receiving more.
        This is done by a contingent mechanism, i.e. the messagequeue or rather
        the Message::Sink that gets pushed to maintains a count of how many
        messages may be pushed. When the count drops to zero, more pushes
        fail.
        
        When the service can receive more Messages, it increases the count
        again and pending sends get retried. This allows a service that
        experiences backpressure itself from some other peer further downstream
        to not get flooded with more jobs and rather pass the pressure on
        upstream.
        
        Contingent implements contingent handling as a wrapper around any other
        Message::Sink. For each contingent you want to count independently
        you can create an independent Contingent object, all wrapping the same
        queue. Note that this only makes sense for Messages based on invoke(),
        as an event style Message (get_handled_by()) generally have no known
        number of receivers (that would increment the contingent).
        
        \code
        SomeMessageQueue queue;  // implements osal::Message::Sink
        osal::Message::Contingent contingent(queue);  // one Message allowed initially  by default
                
        SomeMessageOrigin origin(contingent);  // pushes
        SomeMessageDestination destination(contingent);
        
        void SomeMessageDestination::do_it()
        {
            do_something();
            if(finished)
                contingent.more();  // allow for another Message to be pushed
        }
        \endcode
    */
    class OSAL_EXPORT Message::Contingent: public Message::Sink {
        
    public:
        //! Wrap \p underlying, initially only allowing for
        //! \p initial_contingent messages to be pushed through this
        //! Contingent object, until someone calls for more().
        Contingent(Message::Sink &underlying,
                   unsigned initial_contingent=1) IPL_NOEXCEPT:
            underlying(underlying), contingent(initial_contingent) {}
                
        //! \brief Allow for \p additional_contingent more messages to be pushed
        void more(unsigned additional_contingent=1) IPL_NOEXCEPT;
        
        //! \brief Is some contingent left?
        //!
        //! Races against push() and more(), so only makes sense to use from
        //! threads calling those exclusively.
        explicit operator bool () IPL_NOEXCEPT {
            threadsafe::Mutex::Guard lock(mutex);
            return contingent;
        }
        
        //! \brief \warning Holds a mutex during callback to retry_push()!
        bool push(Message *message, Message::Pusher *pusher) IPL_NOEXCEPT override;
        void forget(Pusher *pusher) IPL_NOEXCEPT override;
        
    protected:
        Message::Sink &underlying;
        threadsafe::Mutex mutex{true};  // recursive for registration pattern
        unsigned contingent;
        typedef std::set<Message::Pusher *> Waiting;
        Waiting waiting;
    };

/****************************************************************************/

    /*!
        \brief Listener for \ref Message "Messages"
        \anchor osal_Message_Handler

        \ref Message "Messages" are processed by calling their
        \ref Message::get_handled_by "get_handled_by()" zero or more times,
        feeding it one Handler a time as parameter.
        The Message then determines whether the Handler instance provides
        a suitable interface,
        and if yes, makes suitable calls to the Handler's method(s).

        Which methods these are is completely up to you when designing
        a concrete Message-Handler interface.
        For example when you have a FooEvent and a BarEvent (derived from
        Message) and hence your FooBarHandler has methods foo() and bar(),
        FooEvent::get_handled_by() should call foo() and
        BarEvent::get_handled_by() bar(),
        possibly passing along some parameters of the events.

        To make this possible, you need to make your Handler identifiable
        as implementing your FooBar interface.
        You do that by implementing the cast() method and providing a
        static \ref ipl::Tag "Tag" acting as interface designator:
        \code
        class FooBarHandler: public osal::Message::Handler {
        public:
            virtual void *cast(const ipl::Tag &type) IPL_NOEXCEPT;
            static ipl::Tag TYPE;

            void foo(int revolutions);
            void bar(const char *id, const Frobnicator &frob);  // whatever
        };

        ipl::Tag FooBarHandler::TYPE;

        void *FooBarHandler::cast(const ipl::Tag &type) IPL_NOEXCEPT
        {
            if(type==TYPE)
                return this;
            return nullptr;
        }
        \endcode
    */
    class OSAL_EXPORT Message::Handler {

    public:
        virtual ~Handler()=default;

        /*!
            \brief Poor man's dynamic cast

            If this object supports the interface designated by \a type,
            return a pointer to it (or some proxy object).
            The pointer will get casted and used as pointing
            to the type designated by \a type.
            If this object doesn't support the \a type interface,
            return nullptr.

            \see the example in the \ref osal_Message_Handler "class docu".
        */
        virtual void *cast(const ipl::Tag &type) IPL_NOEXCEPT=0;
    };

/****************************************************************************/

    /*!
        \brief Convenient asyncronous-procedure-call-like Message
        invoking a normal callback
    */
    class OSAL_EXPORT Message::Callback: public Message {

    public:

        typedef void (*Procedure)(void *context);

        Callback(std::function<void()> &&callback) IPL_NOEXCEPT: callback(callback) {}
        Callback(Procedure procedure, void *context=nullptr) IPL_NOEXCEPT:
            Callback([procedure, context]{ procedure(context); }) {}

        void invoke() override;

    protected:
        std::function<void()> callback;
    };

/****************************************************************************/

}  // end of namespace osal

/****************************************************************************/
#endif
