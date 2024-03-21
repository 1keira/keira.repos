/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SERIALPORTFMT_HXX
#define OSAL_SERIALPORTFMT_HXX

#include <osal/SerialPort.hxx>

#include <common/BinBuffer.hxx>
#include <osal/osal_dso.h>
#include <osal/osal.hxx>

namespace osal
{

/**
 *    \brief
 *        Wrap a SerialPort to make it formatted
 **/
class /* OSAL_EXPORT win32 can't deal with export of all inline class */ SerialPortFmt :
    public ipl::iostream
{
public: // functions

    /**
     *    \brief
     *        Create a formatted serial port operating in blocking mode and with the given
     *        buffer size for formatted operations

     *        A non-blocking, formatted serial-port is not provided as the streams library
     *        iostream interface isn't really prepared for non-blocking operation.
     **/
    SerialPortFmt(const size_t bufsize = 8192) :
        ipl::iostream(NULL),
        m_port(true),
        m_buf(&m_port, &m_port, bufsize, bufsize)
    { this->init( &m_buf ); }

    ~SerialPortFmt()
    {
        close();
    }

    virtual bool open()
    {
        return m_port.open();
    }

    virtual bool close()
    {
        *this << ipl::flush;

        return m_port.close();
    }

    virtual bool isValid() const
    {
        return m_port.isValid();
    }

    virtual bool hasError() const
    {
        return m_port.hasError();
    }

    const SerialPort& getPort() const
    { return m_port; }

    SerialPort::PortSettings& getPortSettings()
    {
        return m_port.getPortSettings();
    }

    void setPortSettings(const SerialPort::PortSettings &p_settings)
    {
        return m_port.setPortSettings(p_settings);
    }

protected:
    //! the contained binary file type
    osal::SerialPort m_port;
    //! the buffer connecting the binary stream to the formatted stream
    ipl::BinBuffer m_buf;
}; // end class

} // end osal

#endif
