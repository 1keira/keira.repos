/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef CALLBACKS_CALLBACKS_HXX
#define CALLBACKS_CALLBACKS_HXX
/****************************************************************************/
/*!
    \internal
    \page callbacks_page Different callback mechanisms

    There are three basic ways to implement callbacks in C++:
    C-style, C++ interfaces and bound methods.
    We sum them up here as a decision aid for potential LcCallback users.

    \section c_callbacks_page C-style callbacks

    The classic C-style callback is a function that takes a \c void \c *
    pointing to some callback internal context data
    (plus possibly some actual callback arguments):
    \code

        struct MyCallbackContext {
            int foo;
            char bar;
        };

        void my_callback(void *data)
        {
            MyCallbackContext *context=(MyCallbackContext *)data;
            ...
        }

        MyCallbackContext context;

        register_callback(my_callback, &context);

    \endcode
    This is the only way to do callbacks in C,
    so you will need it whenever you interface with C code.

    This method is simple and straightforward, but the manual casting
    makes it bot cumbersome and type-unsafe.

    \section callback_interface_page Callback interface

    The canonical way to do callbacks in C++ is to define a callback
    interface with a virtual method and then derive your
    object-to-be-called-back from this interface,
    overriding the (virtual) callback method(s):
    \code

        class Engine {

        public:

            class Callback {
            public:
                virtual void the_engine_callback()=0;
            };

            void registerCallback(Callback *);
        };

        class Client: public Engine::Callback {

        public:
            Client(Engine &engine) { engine.registerCallback(this); }
            virtual void the_engine_callback();
        };

    \endcode
    This method is very easy to use and fits very well into
    object oriented designs, so it is probably the most frequently used
    callback pattern in all OOP languages.

    But it has one shortcoming. If the \c Client object knows
    \e several \c Engine objects it can register the same callback with
    each of them, but it is impossible to register \e individual callbacks
    (i.e. so that \c engine1 calls \c callbackq(), \c engine2 calls
    \c callback2() etc.).

    \section lc_callbacks_page Bound methods

    In cases where you want to actually specify the method (as opposed to
    implementing a given interface) you need a callback specification
    to be a pair of a method and an object on which the method
    is to be called, aka. a bound method.

    This is implemented for you in util::LcCallback
    (for details refer to its class documentation):
    \code

        class Client {

        public:
            Client(Engine &engine1, Engine &engine2) {
                engine1.registerCallback(util::LcCallback<int>(this, some_callback));
                engine2.registerCallback(util::LcCallback<int>(this, another_callback));
            }

        protected:
            static void some_callback(Client &self, const int &value);
            static void another_callback(Client &self, const int &value);
        };
    \endcode

    Btw., it is named like this for no particular reason besides
    the lack of a better name and the fact that from the three
    canonical callback patterns presented here it is the
    <em>l</em>east <em>c</em>anonical one.
*/
/****************************************************************************/

#include <ipl_config.h>

#include <iplbase/exceptions.hxx>

/****************************************************************************/

// This code casts between different function types and the compiler is upset
#ifdef __GNUC__
#if (__GNUC__*10000+__GNUC_MINOR__*100+__GNUC_PATCHLEVEL__)>=40600
#pragma GCC diagnostic push  // not supported before GCC 4.6
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
#endif

/****************************************************************************/

namespace util {

/****************************************************************************/

    /*!
        \brief Callback with one argument

        This is a smart wrapper around a pair of an object and a method,
        around a function or around nothing (when unassigned)
        that can be called with a single argument of type \a Arg.
        (If your callback takes no argument at all, use \c LcCallback<>.)

        For a brief discussion of different callback strategies, refer to
        \ref callbacks_page.

        When you're the one on whom the callback gets registered,
        use it like this:
        \code

            class Foo {

            public:
                void register_callback(const LcCallback<Bar> &callback) {
                    the_callback=cb;
                }

                void do_something_useful() {
                    // ...
                    the_callback(some_value);
                    // ...
                }

            protected:
                util::LcCallback<Bar> the_callback;
                Bar                   some_value;
            };

        \endcode
        This does the Right Thing even when \c register_callback()
        was never called.

        Due to some peculiarities of the C++ standard and its various
        implementations (have a look at
        http://www.codeproject.com/KB/cpp/FastDelegate.aspx)
        method pointers cannot be used reliably, so we have to revert to
        simple function pointers internally.
        Unfortunately this implies that your callback methods must be static.
        This leaves you the normal access control but requires that some
        replacement for \c this must be used explicitly.

        Our \c this replacement is a \c self reference as first parameter
        (Python programmers will feel at home):
        \code
            static void callback(Class &self, const Arg &value)
        \endcode
        This method plus a pointer or reference to the object get rolled
        into a Callback object that takes care of all the nasty casting
        internally.

        So when you need a callback method, use LcCallback like this:
        \code

            class Foo {

                Foo(Engine &engine) {
                    engine.register_callback(util::LcCallback<Bar>(this, callback_method));
                }

            protected:
                static void callback_method(Foo &self, const Bar &value) {
                    self.do_something_with(value);
                    self.flag=true;
                }

                bool flag;
                void do_something with(const Bar &bar);
            };

        \endcode

        Note that you needn't preserve the LcCallback object after
        registering, as it is fully copyable.
        (Assuming that \c register_callback() actually makes a copy,
        which it really should.)

        In case you want to define a callback \e function while the caller
        wants an LcCallback object, use it like this:
        \code

            void callback_function(const Bar &value)
            {
                ...
            }

            engine.register_callback(util::LcCallback<Bar>(callback_function);

        \endcode
        I.e. just as you already guessed.
    */
    template <typename Arg=void>
    class LcCallback {

    protected:

        //! \brief Some random function pointer with no specific type,
        //! analogous to \c void \c * but for functions
        typedef void (*FnVoid)(void *);
        //! \brief The canonical form of a C-style callback
        typedef void (*CCallback)(void *, Arg);

    public:
        //! \brief Creates a callback that does nothing
        LcCallback() IPL_NOEXCEPT:
            m_obj(/*NULL*/0), m_fn(/*NULL*/0),
            m_dispatcher(/*NULL*/0) {}

        template <typename Class>
        LcCallback(Class &object, void (*static_method)(Class &, const Arg &)) IPL_NOEXCEPT:
            m_obj((void *)&object),
            m_fn((FnVoid)static_method),
            m_dispatcher(MethodDispatcher<Class>::fn) {}

        template <typename Class>
        LcCallback(Class *object, void (*static_method)(Class &, const Arg &)) IPL_NOEXCEPT:
            m_obj((void *)object),
            m_fn((FnVoid)static_method),
            m_dispatcher(MethodDispatcher<Class>::fn) {}

        LcCallback(void (*function)(const Arg &)) IPL_NOEXCEPT:
            m_obj(/*NULL*/0),
            m_fn((FnVoid)function),
            m_dispatcher(FunctionDispatcher::fn) {}

        LcCallback(const LcCallback<Arg> &other) IPL_NOEXCEPT:
            m_obj(other.m_obj), m_fn(other.m_fn),
            m_dispatcher(other.m_dispatcher) {}

        LcCallback<Arg> &operator = (const LcCallback<Arg> &other) IPL_NOEXCEPT {
            m_obj=other.m_obj;
            m_fn=other.m_fn;
            m_dispatcher=other.m_dispatcher;
            return *this;
        }

        /*!
            \brief Safely invoke the callback

            If this is a valid callback, invoke it.
            If this is an empty (unassigned) callback, do nothing.
        */
        void operator() (const Arg &arg) const IPL_NOEXCEPT {
            if(m_dispatcher)
                m_dispatcher(m_obj, m_fn, arg);
        }

        /*!
            \brief Convert into C-style callback

            In stock C a callback usually is a pair of a pointer to a function
            that takes a void pointer (plus normal arguments) and a
            void pointer.
            You can easily use an LcCallback object in such a context by
            passing it as both the function and the pointer,
            and the cast operators will take care of the details:
            \code

                void register_callback(void (*function)(void *, int), void *context);

                util::LcCallback<int> callback;
                register_callback(callback, callback);

            \endcode

            \see operator void * ()
        */
        operator CCallback() IPL_NOEXCEPT { return FunctionDispatcher::c_callback; }
        //! See \ref operator CCallback()
        operator void * () IPL_NOEXCEPT   { return this;                           }

    protected:
        //! \internal
        typedef void (*DispatchFn)(void *, FnVoid, const Arg &);
        //! \internal
        //! \brief Templatifying wrapper around fn()
        template <typename Class>
        class MethodDispatcher {
        public:
            typedef void (*Fn)(Class &, const Arg &);
            //! \internal
            //! \brief Cast the pointers and call the actual callback
            static void fn(void *obj, FnVoid fn, const Arg &arg) IPL_NOEXCEPT {
                IPLBASE_ABORT_ON_EXCEPTION(
                    ((Fn)fn)(*(Class *)obj, arg);
                )
            }
        };
        //! \internal
        //! \brief Wrapper around fn(), built analogously to MethodDispatcher
        class FunctionDispatcher {
        public:
            typedef void (*Fn)(const Arg &);
            //! \internal
            //! \brief Cast the pointers and call the actual callback
            static void fn(void *obj, FnVoid fn, const Arg &arg) IPL_NOEXCEPT {
                (void)obj;
                IPLBASE_ABORT_ON_EXCEPTION(
                    ((Fn)fn)(arg);
                )
            }
            //! \internal
            //! \brief Adapter to C-style callbacks
            static void c_callback(void *context, Arg arg) IPL_NOEXCEPT {
                LcCallback<Arg> &self=*(LcCallback<Arg> *)context;
                IPLBASE_ABORT_ON_EXCEPTION(
                    self(arg);
                )
            }
        };

        //! \brief The object or NULL
        void *m_obj;
        //! \brief The static method to be called on the object
        FnVoid m_fn;
        //! \brief A helper function that casts m_obj and m_fn as needed
        //! or NULL if unassigned
        DispatchFn m_dispatcher;
    };

/****************************************************************************/

    /*!
        \brief Overloaded version for zero-argument callbacks

        \see LcCallback<Arg>
    */
    template <>
    class LcCallback<void> {

    protected:

        //! \brief Some random function pointer with no specific type,
        //! analogous to \c void \c * but for functions
        typedef void (*FnVoid)(void *);
        typedef void (*CCallback)(void *);

    public:
        //! \brief Creates a callback that does nothing
        LcCallback() IPL_NOEXCEPT:
            m_obj(/*NULL*/0), m_fn(/*NULL*/0),
            m_dispatcher(/*NULL*/0) {}

        template <typename Class>
        LcCallback(Class &object, void (*static_method)(Class &)) IPL_NOEXCEPT:
            m_obj((void *)&object),
            m_fn((FnVoid)static_method),
            m_dispatcher(MethodDispatcher<Class>::fn) {}

        template <typename Class>
        LcCallback(Class *object, void (*static_method)(Class &)) IPL_NOEXCEPT:
            m_obj((void *)object),
            m_fn((FnVoid)static_method),
            m_dispatcher(MethodDispatcher<Class>::fn) {}

        LcCallback(void (*function)()) IPL_NOEXCEPT:
            m_obj(/*NULL*/0),
            m_fn((FnVoid)function),
            m_dispatcher(FunctionDispatcher::fn) {}

        LcCallback(const LcCallback<> &other) IPL_NOEXCEPT:
            m_obj(other.m_obj), m_fn(other.m_fn),
            m_dispatcher(other.m_dispatcher) {}

        LcCallback<> &operator = (const LcCallback<> &other) IPL_NOEXCEPT {
            m_obj=other.m_obj;
            m_fn=other.m_fn;
            m_dispatcher=other.m_dispatcher;
            return *this;
        }

        /*!
            \brief Safely invoke the callback

            If this is a valid callback, invoke it.
            If this is an empty callback, do nothing.
        */
        void operator() () const IPL_NOEXCEPT {
            if(m_dispatcher)
                IPLBASE_ABORT_ON_EXCEPTION(
                    m_dispatcher(m_obj, m_fn);
                )
        }

        /*!
            \brief Convert into C-style callback

            In stock C a callback usually is a pair of a pointer to a function
            that takes a void pointer and a void pointer.
            You can easily use a LcCallback object in such a context by
            passing it as both the function and the pointer,
            and the cast operators will take care of the details:
            \code

                void register_callback(void (*function)(void *), void *context);

                util::LcCallback<> callback;
                register_callback(callback, callback);

            \endcode

            \see operator void * ()
        */
        operator CCallback() IPL_NOEXCEPT { return FunctionDispatcher::c_callback; }
        //! See \ref operator CCallback()
        operator void * () IPL_NOEXCEPT   { return this;                           }

    protected:
        //! \internal
        typedef void (*DispatchFn)(void *, FnVoid);
        //! \internal
        //! \brief Templatifying wrapper around fn()
        template <typename Class>
        class MethodDispatcher {
        public:
            typedef void (*Fn)(Class &);
            //! \internal
            //! \brief Cast the pointers and call the actual callback
            static void fn(void *obj, FnVoid fn) IPL_NOEXCEPT {
                IPLBASE_ABORT_ON_EXCEPTION(
                    ((Fn)fn)(*(Class *)obj);
                )
            }
        };
        //! \internal
        //! \brief Wrapper around fn(), built analogously to MethodDispatcher
        class FunctionDispatcher {
        public:
            typedef void (*Fn)();
            //! \internal
            //! \brief Cast the pointers and call the actual callback
            static void fn(void *obj, FnVoid fn) IPL_NOEXCEPT {
                (void)obj;
                IPLBASE_ABORT_ON_EXCEPTION(
                    ((Fn)fn)();
                )
            }
            //! \internal
            //! \brief Adapter to C-style callbacks
            static void c_callback(void *context) IPL_NOEXCEPT {
                LcCallback<> &self=*(LcCallback<> *)context;
                IPLBASE_ABORT_ON_EXCEPTION(
                    self();
                )
            }
        };

        //! \brief The object
        void *m_obj;
        //! \brief The static method to be called on the object
        FnVoid m_fn;
        //! \brief A helper function that casts m_obj and m_fn as needed
        //! or NULL if unassigned
        DispatchFn m_dispatcher;
    };

/****************************************************************************/

}  // end of namespace util

/****************************************************************************/

#ifdef __GNUC__
#if (__GNUC__*10000+__GNUC_MINOR__*100+__GNUC_PATCHLEVEL__)>=40600
#pragma GCC diagnostic pop
#endif
#endif

/****************************************************************************/
#endif
