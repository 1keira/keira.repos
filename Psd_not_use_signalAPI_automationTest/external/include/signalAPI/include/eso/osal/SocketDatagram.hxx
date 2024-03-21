/*
    Copyright e.solutions GmbH
    All rights reserved
*/
#ifndef OSAL_SOCKETDATAGRAM_HXX
#define OSAL_SOCKETDATAGRAM_HXX

#include <ipl_config.h>
#include <osal/SocketBase.hxx>
#include <common/buffers.hxx>
#include <common/Tag.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>

#include <memory>

namespace osal
{

/**
    \brief
        Abstraction for packet oriented sockets.

        This base class interface only serves for some common code and
        interface between different implementations of packet oriented
        sockets. Therefore it can not be instantiated on its own.
**/
class OSAL_EXPORT SocketDatagram :
    public SocketBase
{
public:
    virtual ~SocketDatagram() IPL_NOEXCEPT { /* NOP */}

    bool isValid() const IPL_NOEXCEPT override
    { return m_is_valid && m_socket_handle.isValid()
        && this->getState() != DEAD; }


    /**
        \brief
            Holds the messages to send/receive with datagram socket
        
            Sockets that have specific types for peer addresses should
            create a derived class from this, with own type and override tag()
     */
    struct Message
    {
        ipl::Buf data;

        virtual ~Message() { /* NOP */ }
        static ipl::Tag type;
        virtual const ipl::Tag& tag() const IPL_NOEXCEPT { return type; }

        template <typename T>
        const T* as() const IPL_NOEXCEPT {
            if( T::type == tag() ) {
                return static_cast<const T*>(this);
            }
            return nullptr;
        }

        template <typename T>
        T* as() IPL_NOEXCEPT {
            if( T::type == tag() ) {
                return static_cast<T*>(this);
            }
            return nullptr;
        }
    };

    /**
        \brief
            Read a message from the socket
        \return nullptr on Error or if no data is available, 
            valid Message object on success
        \errorindicator
            return value is nullptr and hasError() is true
          
     */
    virtual std::unique_ptr<Message> receive() IPL_NOEXCEPT = 0;

    static ipl::ErrorType error;
    //! \brief The operation failed, try again later
    static ipl::ErrorType retriable_error;
    //! \brief The parameters are wrong or we are in a wrong state for the action
    static ipl::ErrorType usage_error;
    //! \brief The object is unusable. Only creating a new object might solve it
    static ipl::ErrorType broken_error;

protected:
    /**
        \brief
            This sets up the basic socket information.

            The initial state for the socket object will be
            INACTIVE.
        \errorindicator
          via isValid()
    **/
    explicit SocketDatagram(const bool blocking) IPL_NOEXCEPT : SocketBase(true), m_is_valid(true), m_blocking(blocking) {}

    bool m_is_valid;
    const bool m_blocking;

}; //end class Socket

} // end namespace osal

#endif
