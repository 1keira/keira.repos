/*
    Copyright 2020, 2023 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_IMESSAGE_FILTER_HXX
#define TRACING_IMESSAGE_FILTER_HXX

#include <string>
#include <tracing/message/Message.hxx>
#include <tracing/entity/IEntityAccessor.hxx>

namespace tracing
{
//! \brief Filter type constant definitions.
struct TRACINGIMPL_EXPORT FilterType
{
    static const int16_t FILTER_FRONTEND = 0;         //! Flags for Frontend filtering.
    static const int16_t FILTER_BACKEND = 1;          //! Flags for Backend individual filtering.
    static const int16_t FILTER_BACKEND_DEFAULT = 2;  //! Flags for default backend filtering.
};

/*!
 *  \brief
 *      Interface class to implement a trace message filter to be applied for
 *      frontend and/or backend message filtering.
 *
 *      The message filter is a functor operating on trace messages of the given
 *      channel, thread and process entities.
 *
 *      You can implement your own trace message filter if none of the supplied
 *      filters matches your needs by following these simple steps:
 *
 *      -# Create a class and derive from IMessageFilter.
 *      -# Implement at least the pure virtual functions declared in this class.
 *      -# Implement the static functions declared in this class.
 *      -# For the functor entity arguments you also need to create a class and
 *         derive from IEntityAccessor, which allows you to access the desired
 *         attributes of different entity nodes (e.g. for backend or frontend)
 *      -# In a source file, include your filter header file.
 *      -# Compile this into a shared library for static configuration,
 *         or into your application and apply your filter via setMessageFilter()
 *         API of an individual backend or for frontend or default backend
 *         filtering towards the trace core API.
 *      -# For static configuration, specify the name of your filter in the
 *         tracing's configuration file and where it shall be applied.
 *         Filtering can be applied in two steps:
 *         - at frontend before the message enters the message buffer: "frontend filter"
 *         - at trace core, before messages are forwarded to backends:
 *           By default the trace core applies the "default backend filter".
 *           If a backend is configured with an own individual "backend filter"
 *           this filter is individually applied by the trace core for this backend,
 *           instead of the "default backend filter".
 *         The related configuration keys are "filter"."name" within the
 *         "client" and "backends" section, whereas the "default backend filter"
 *          is specified within a special backend entry called "default".
 *
 *      A sample is provided for this purpose, briefly demonstrating the usage.
 */
class IMessageFilter
{
public:
    //! No special capabilities provided by filter.
    static const uint16_t FLAGS_NONE = 0;
    //! Indicates that the filter may change its filtering rules during runtime.
    static const uint16_t FLAGS_DYNAMIC_FILTERING = 1;
public:
    /*!
     *  \brief
     *      Constructor.
     *  \param
     *      filter_name The unique filter name, which must be identical to the filter name
     *      as given in the tracing configuration file.
     *  \param
     *      description A brief filter description indicating about the filter.
     */
    IMessageFilter(const std::string & filter_name, const std::string & description)
        : m_name(filter_name)
        , m_description(description)
    {
    }

    /*!
     *  \brief
     *      Virtual destructor.
     */
    virtual ~IMessageFilter() {/* nop */}

    /************ Start of MessageFilter factory functions interface *********/

    /*!
     *  \brief
     *      Returns a C string containing the name of the filter.
     *
     *      If you derive from this interface and implement your own filter you
     *      are expected to return a C string containing a unique name for your
     *      filter. This string will be compared with entries found in the config
     *      file, to decide which filter to instantiate. The relevant config file
     *      keys are named "filter"."name".
     *
     *  \return
     *      C-style string with message filter's name.
     */
    static const char * getFilterName() { return nullptr; }

    /*!
     *  \brief
     *      Returns the message filter interface version number.
     *
     *      This is not yet checked, so you can return 0 in your own filter for
     *      the moment, but this may change in the future. The current version
     *      number will be defined in this header when this feature is used.
     *
     *      Future versions of the tracing module may refuse to work with
     *      message filters that return version numbers too low.
     *
     *  \return
     *      Version number of message filter interface.
     */
    static int32_t getVersion() { return 0;}

    /*!
     *  \brief
     *      Creates a new message filter.
     *
     *      When implementing your own message filter you are expected to implement
     *      this function in a way, such that when calling it will create a new
     *      message filter of the type you declared (and which derives itself from
     *      this interface class) and return a pointer to an object of your message
     *      filter class or NULL if construction failed. Your message filter will
     *      not be used by the trace core in the latter case.
     *
     *  \return
     *      A pointer to the newly created message filter.
     */
    static IMessageFilter * create() { return nullptr; }

    /*!
     *  \brief
     *      Destroys a message filter again.
     *
     *      This is the counter-part to create(), it will be called when shutting
     *      down the trace core. You can implement this just like shown here, but
     *      possibly you want to do some other cleanup work in your filter first.
     *      The pointer provided as parameter is the one received from create().
     *
     *  \param
     *      message_filter A pointer to a message filter object.
     */
    static void destroy(IMessageFilter * message_filter) { delete message_filter; }

    /************ End of MessageFilter factory functions interface ***********/

    /************ Start of MessageFilter interface ***************************/

    /*!
     *  \brief
     *      The message filter implementation method for filtering at frontend
     *      and/or filtering at backend.
     *  \param
     *      msg The message to be filtered.
     *  \param
     *      thread The thread accessor of the entity which transmitted the message.
     *  \param
     *      channel The channel accessor of the entity where message was transmitted.
     *  \return
     *      true on filter match (pass), false to filter out the message.
     */
    virtual bool operator()(const MessagePtr & msg,
                            const IEntityAccessor & thread,
                            const IEntityAccessor & channel) IPL_NOEXCEPT = 0;

    /*!
     *  \brief
     *      Convenience method to allow early evaluation of message level filtering
     *      for a given message level.
     *
     *      If you derive from this interface and implement your own message
     *      filter you are expected to return a boolean value to indicate if
     *      a message with given level would be filtered out.
     *  \param
     *      msg_level The message level to be filtered.
     *  \param
     *      thread The thread accessor of the entity which transmitted the message.
     *  \param
     *      channel The channel accessor of the entity where message was transmitted.
     *  \return
     *      true on filter match (pass), otherwise false (filter out).
     */
    virtual bool isLevelEnabled(const int16_t msg_level,
                                const IEntityAccessor & thread,
                                const IEntityAccessor & channel) const IPL_NOEXCEPT
    {
        return false;
    }

    /************ End of MessageFilter interface *****************************/

    /*!
     *  \brief
     *      Return the filter's name.
     *
     *      This should return the name of your filter, but as a std::string.
     *      You may want to just call getFilterName() in your implementation of
     *      this method.
     *
     *  \return
     *      C++ string with the filter's name.
     */
    virtual const std::string & getName() {return m_name;}

    /*!
     *  \brief
     *      Return the filter's description.
     *
     *      This should return the description of your filter.
     *
     *  \return
     *      C++ string with the filter's description.
     */
    virtual const std::string & getFilterDescription() { return m_description;}

    /*!
     *  \brief
     *      Get the filter's capability flags.
     *
     *  \return
     *      OR'ed integer containing values from FLAGS_* constants.
     */
    virtual uint16_t getFlags() { return FLAGS_NONE; }
protected:
    //! The filter's name.
    std::string m_name;
    //! The filter's description.
    std::string m_description;
};

}

#endif /* TRACING_IMESSAGE_FILTER_HXX */

