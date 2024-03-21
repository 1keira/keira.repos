/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_TCPSOCKETFMT_HXX
#define OSAL_TCPSOCKETFMT_HXX

#include <common/BinBuffer.hxx>
#include <common/streams/iostream.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/TCPSocket.hxx>

namespace osal
{

/**
 * \brief
 *    Provides s streams library iostream interface on top of an osal::TCPSocket
 **/
class /* OSAL_EXPORT win32 can't deal with export of all inline class */ TCPSocketFmt :
    public ipl::iostream
{
public: // functions

    /**
     * \brief
     *    Construct a formatted TCPSocket using the given IP
     *    addresses

     *    The socket will always be in blocking mode as the
     *    iostream framework isn't prepared for non-blocking
     *    operation.
     **/
    TCPSocketFmt(const osal::TCPSocket::IPAddress src, const osal::TCPSocket::IPAddress dst,
        const bool reuse_address, const size_t bufsize = 8192, const osal::IPSocket::IPProtocolVersion p_ip_version = osal::IPSocket::IPV4) :
        ipl::iostream(NULL),
        m_tcp(true, 0, 0, src, dst, reuse_address, p_ip_version),
        m_buf(&m_tcp, &m_tcp, bufsize, bufsize)
    { this->init( &m_buf ); if( !this->tie() ) { this->tie( this ); } }

    //! \brief
    //! Construct a formatted TCPSocket from the given TCPSocket
    //! destriptor
    TCPSocketFmt(const TCPSocket::Description &desc, const size_t bufsize = 8192) :
        ipl::iostream(NULL),
        m_tcp(true, 0, 0, desc),
        m_buf(&m_tcp, &m_tcp, bufsize, bufsize)
    { this->init( &m_buf ); if( !this->tie()) { this->tie( this ); } }

    ~TCPSocketFmt()
    {
        if( m_tcp.getState() == m_tcp.OPEN ||  m_tcp.getState() == m_tcp.CONNECTING )
        {
            TCPSocketFmt::close();
        }
    }

    virtual bool close(const bool shutdown = false)
    {
        *this << ipl::flush;

        return m_tcp.close(shutdown);
    }

    /**
     * \brief
     *    Opens the socket
     * \see
     *    TCPSocket::connect()
     * \return
     *    Whether connection is setup asynchronously
     **/
    virtual bool connect()
    {
        bool async_con = m_tcp.connect();

        if( m_tcp.hasError() )
            return true;

        if( async_con )
        {
            // not handled yet
            return true;
        }

        return false;
    }

    //! returns whether the file is valid and open
    virtual bool isValid() const
    {
        return m_tcp.isValid();
    }

    //! returns whether the last operation failed
    virtual bool hasError() const
    {
        return m_tcp.hasError();
    }

    bool setTCPNoDelay(const bool enable)
    {
        m_tcp.setTCPNoDelay(enable);
        return m_tcp.hasError();
    }

    bool setKeepalive(const
        osal::TCPSocket::KeepaliveSettings
        &settings)
    {
        m_tcp.setKeepalive(settings);
        return m_tcp.hasError();
    }

    const TCPSocket& getSocket() const
    { return m_tcp; }
    
    TCPSocket& getSocket()
    { return m_tcp; }

protected:
    //! the contained binary file type
    osal::TCPSocket m_tcp;
    //! the buffer connecting the binary stream to the formatted stream
    ipl::BinBuffer m_buf;
}; // end class

} // end osal

#endif
