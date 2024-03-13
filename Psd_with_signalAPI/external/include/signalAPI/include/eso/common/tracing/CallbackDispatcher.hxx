/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_CALLBACKDISPATCHER_HXX
#define TRACING_CALLBACKDISPATCHER_HXX

#include <ipl_config.h>
#include <iplbase/exceptions.hxx>

#include <common/types/vector.hxx>
#include <common/tracing/IClient.hxx>
#include <common/tracing/CallbackObject.hxx>

namespace tracing
{

/*!
 *    \brief
 *        A template for registering callback objects of arbitrary type.

 *        Please have a look at the user-guide for documenation
 *        regarding implementing trace callbacks.
 */
template <class T> class CallbackDispatcher : public CallbackObject
{
public:
    //! \brief Default constructor.
    CallbackDispatcher() IPL_NOEXCEPT {/* nop */}

    //! \brief Registers a new callback with specified name together with a class
    //! instance and member function pointer.
    void registerCallback(const ipl::string & name, T * obj,
                          void (T::*func)(int32_t id, void * const data,
                                          size_t len)) IPL_NOEXCEPT
    {
        IClient * client = IClient::getTraceClient();
        IPL_ASSERT(client);
        if (client) // BRANCH_COVERAGE_UNTESTABLE
        {
            int32_t id;
            IPLBASE_ABORT_ON_EXCEPTION(
                id = client->registerCallback(name, this);
            )
            Callbacks c;
            c.id = id;
            c.obj = obj;
            c.func = func;
            c.name = name;

            // insert into internal list
            m_callbacks.push_back(c);
        }
    }

    //! \brief Unregisters the callback pointed to by obj.
    void unregisterCallback(const ipl::string & name, const T * obj) IPL_NOEXCEPT
    {
        IClient * client = IClient::getTraceClient();
        IPL_ASSERT(client);
        if (client) // BRANCH_COVERAGE_UNTESTABLE
        {
            typename ipl::vector<Callbacks>::iterator i = m_callbacks.begin();
            for ( ; i != m_callbacks.end(); ++i)
            {
                if (i->obj == obj && i->name == name)
                {
                    IPLBASE_ABORT_ON_EXCEPTION(
                        client->unregisterCallback(i->id);
                    )
                    (void) m_callbacks.erase(i);
                    return;
                }
            }
        }
    }

    //! \brief Executes the callback specified by cbid.
    void execute(int32_t cbid, void * const data, size_t len) IPL_NOEXCEPT override
    {
        for (size_t i = 0; i < m_callbacks.size(); ++i)
        {
            if (m_callbacks[i].id == cbid)
                IPLBASE_ABORT_ON_EXCEPTION(
                    (m_callbacks[i].obj->*(m_callbacks[i].func))(cbid, data, len);
                    return;
                )
        }
    }

    //! \brief Specifies that registered callback objects should not be deleted automatically.
    bool deleteAtUnregister() const IPL_NOEXCEPT override
    {
        return false;
    }

private:
    //! \brief Just a struct to keep IDs and pointers together.
    struct Callbacks
    {
        int32_t id;
        T * obj;
        void (T::*func)(int32_t, void * const, size_t);
        ipl::string name;
    };

    //! \brief Hidden copy constructor.
    CallbackDispatcher(const CallbackDispatcher & other) IPL_NOEXCEPT;
    //! \brief Hidden assignment operator.
    CallbackDispatcher & operator=(const CallbackDispatcher & other) IPL_NOEXCEPT;

    //! The callbacks contained in this class.
    ipl::vector<Callbacks> m_callbacks;
};

} // end of namespace tracing

#endif /* TRACING_CALLBACKDISPATCHER_HXX */

