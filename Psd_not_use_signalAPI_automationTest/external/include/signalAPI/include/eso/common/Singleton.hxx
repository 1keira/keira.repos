/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_SINGLETON_HXX
#define IPL_SINGLETON_HXX

#include <ipl_config.h>
#include <threadsafe/Mutex.hxx>

/**
\brief
    This file contains a macro that can be used for classes that
    need to implement a singleton design pattern.

    The macro defines a generic getInstance function that is used to
    retrieve the Singleton instance. Constructor is declared
    protected as an instance of this class should only be created
    from within the singleton class itself. Copy constructor and
    assignment operator are declared private as they should never be
    used for singleton classes.

    For the user of this macro to be able to define its custom
    default constructor code the default constructor isn't
    implemented by means of this macro. If no custom default
    constructor code is wanted then an empty default constructor
    implementation has to be created manually.

    Internally a Meyers Singleton is used, inheriting all its limitations
    and gotchas.
\code
    class MySingleton
    {
        IPL_DECLARE_SINGLETON(MySingleton);
    public:
        void mySpecificFunction();
        [...]
    };

    IPL_IMPLEMENT_SINGLETON(MySingleton);

    MySingleton::MySingleton()
    {
        // either leave it empty or
        // put some specific code in here
    }

    int main()
    {
        MySingleton& singleton = MySingleton::getInstance();
        singleton.mySpecificFunction();
    }
\endcode

\warning
    No additional constructors, copy constructors or assignment
    operators should be declared public as this would oppose the
    design pattern principle.

\warning
    By using macros like these the debuggers can't tell correctly at
    which line of code it currently is as the source file has a
    different lock than the compiler / debugger knows of !

\warning
    Static objects like these must be used with great care. If an
    instance of the singleton is used in the destructor of some
    other static object then this object should issue a call to
    getInstance() in its constructor already. See the C++-FAQ for a
    discussion of problems that can appear when using static
    objects: http://parashift.com/c++-faq-lite/ctors.html#faq-10.14
**/
#define IPL_DECLARE_SINGLETON(CLASS) \
    public:\
        static CLASS& getInstance() IPL_NOEXCEPT;\
    protected:\
        CLASS();\
    private:\
        CLASS(const CLASS&);\
        CLASS& operator=(const CLASS&);\
        static threadsafe::Mutex s_singleton_mutex;\

#define IPL_IMPLEMENT_SINGLETON(CLASS) \
    threadsafe::Mutex CLASS::s_singleton_mutex;\
    CLASS& CLASS::getInstance() IPL_NOEXCEPT\
    {\
        s_singleton_mutex.lock();\
        static CLASS class_instance;\
        s_singleton_mutex.unlock();\
        return class_instance;\
    }\

#endif
