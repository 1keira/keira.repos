/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_SERIALPORT_HXX
#define OSAL_SERIALPORT_HXX

#include <ipl_config.h>

#include <common/types/string.hxx>
#include <common/Macros.hxx>

#include <osal/osal_dso.h>
#include <osal/StreamBinFileRW.hxx>

namespace osal
{

/**
 * \brief
 *     Abstraction for serial / COM / RS232 port access

 *     This class allows for platform-independent access to serial
 *     ports. The class inherits from the StreamBinFileRW and thus also
 *     implements the abstract IBinInputStream and IBinOutputStream
 *     interfaces.
 *
 *     The access to the serial port will be configured in a way such
 *     that binary data transmissions become possible. Otherwise
 *     operating systems tend to perform a lot of interpretation of
 *     data going over the line like handling control signals and such.
 *
 *     The class inherits protected from StreamBinFileRW to make the
 *     file-related API unavailable that makes no sense with a
 *     SerialPort.
**/
class OSAL_EXPORT SerialPort :
    public osal::StreamBinFileRW
{
public: // types
    /**
     * \brief
     *    A type for selecting a baudrate from a predefined set of
     *    baudrates

     *    Different baudrates than that shouldn't be needed as
     *    these are predefined for RS232. Not all baudrates must
     *    be supported by the actual implementation, though. This
     *    is especially the case for the very high rates above
     *    115200 and the very low rates below 1200.
     **/
    enum Baudrate
    {
        BAUDRATE_50 = 50,            //!< \brief Not supported on Windows
        BAUDRATE_75 = 75,            //!< \brief Not supported on Windows
        BAUDRATE_110 = 110,
        BAUDRATE_134 = 134,
        BAUDRATE_150 = 150,
        BAUDRATE_200 = 200,
        BAUDRATE_300 = 300,
        BAUDRATE_600 = 600,
        BAUDRATE_1200 = 1200,
        BAUDRATE_1800 = 1800,
        BAUDRATE_2400 = 2400,
        BAUDRATE_4800 = 4800,
        BAUDRATE_9600 = 9600,
        BAUDRATE_14400 = 14400,      //!< \brief Non-POSIX
        BAUDRATE_19200 = 19200,
        BAUDRATE_38400 = 38400,
        BAUDRATE_57600 = 57600,
        BAUDRATE_115200 = 115200,
        BAUDRATE_128000 = 128000,    //!< \brief Non-POSIX
        BAUDRATE_230400 = 230400,    //!< \brief Not supported on Windows
        BAUDRATE_256000 = 256000,    //!< \brief Non-POSIX
        BAUDRATE_460800 = 460800,    //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_500000 = 500000,    //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_576000 = 576000,    //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_921600 = 921600,    //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_1000000 = 1000000,  //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_1152000 = 1152000,  //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_1500000 = 1500000,  //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_2000000 = 2000000,  //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_2500000 = 2500000,  //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_3000000 = 3000000,  //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_3500000 = 3500000,  //!< \brief Non-POSIX, not supported on Windows
        BAUDRATE_4000000 = 4000000   //!< \brief Non-POSIX, not supported on Windows
    };

    /**
     * \brief
     *     Allows to specify a parity checking mode to use

     *     Parity checking is a simple form of error detection for
     *     data transmissions.  A redundant bit is sent with every
     *     byte (thus usually the nineth bit). This allows to
     *     detect (not correct!) one bit errors.
     *
     *     Usually when a parity error is detected then the
     *     affected byte will be replaced by a NULL character.
     **/
    enum ParityMode
    {
        //! parity bit is not sent at all
        OFF,
        //! \brief
        //! the nineth bit is zero if there is an even number of
        //! ones in the data bits
        EVEN,
        //! \brief
        //! the nineth bit is zero if there is an odd number of
        //! ones in the data bits
        ODD,
        //! \brief
        //!    the nineth bit is always set to one. This is no
        //!    parity check. Not everywhere supported.
        MARK,
        //! \brief
        //!    the nineth bit is always set to zero. This is no
        //!    parity check. Not everywhere supported.
        SPACE
    };

    /**
     * \brief
     *     This struct is used for specifying the serial port
     *     connection settings.

     *     The amount of settings is kept small for the start.
     *     People usually simply want to read and write binary data
     *     at a certain baudrate.
     * \note
     *     The data bits of the serial port are always set to 8.
     **/
    struct PortSettings
    {
        /*!
            \brief The device to use for serial communication

            On Windows this is something like "COM1",
            on Linux and QNX "/dev/ttyS0" or similar.
        */
        ipl::string device_name;

        /*!
            This \em should be a value from Baudrate enum but can also be
            an arbitrary number of bits per second.
            In the latter case chances are that it won't work with every OS.
        */
        size_t baudrate;

        //! \brief Number of stop bits, 1 (default) or 2
        uint8_t stop_bits;
        ParityMode parity_mode;

        //! \brief Whether software flow control characters are honoured during sending
        bool xon_xoff_transmission;
        //! \brief Wheter software flow control characters are generated during receiving
        bool xon_xoff_reception;
        //! \brief Whether RTS/CTS hardware flow control is enabled
        bool rts_cts_handshake;

        PortSettings() IPL_NOEXCEPT :
            baudrate(BAUDRATE_57600),
            stop_bits(1),
            parity_mode(OFF),
            xon_xoff_transmission(false),
            xon_xoff_reception(false),
            rts_cts_handshake(false)
        { }

        IPL_DEPRECATED("access device_name directly",
                       ipl::string getDeviceName() const IPL_NOEXCEPT) {
            return device_name;
        }

        IPL_DEPRECATED("access device_name directly",
                       void setDeviceName(const ipl::string &p_device_name) IPL_NOEXCEPT) {
            device_name = p_device_name;
        }

        IPL_DEPRECATED("access baudrate directly",
                       size_t getBaudrate() const IPL_NOEXCEPT) {
            return baudrate;
        }

        IPL_DEPRECATED("access baudrate directly",
                       void setBaudrate(const size_t p_baudrate) IPL_NOEXCEPT) {
            baudrate = p_baudrate;
        }

        IPL_DEPRECATED("access stop_bits directly",
                       uint8_t getStopBits() const IPL_NOEXCEPT) {
            return stop_bits;
        }

        IPL_DEPRECATED("access stop_bits directly",
                       void setStopBits(const uint8_t p_stop_bits) IPL_NOEXCEPT) {
            stop_bits = p_stop_bits;
        }

        IPL_DEPRECATED("access paritiy_mode directly",
                       ParityMode getParityMode() const IPL_NOEXCEPT) {
            return parity_mode;
        }

        IPL_DEPRECATED("access parity_mode directly",
                       void setParityMode(const ParityMode p_mode) IPL_NOEXCEPT) {
            parity_mode = p_mode;
        }

        IPL_DEPRECATED("access xon_xoff_transmission directly",
                       bool xonXoffTransmission() const IPL_NOEXCEPT) {
            return xon_xoff_transmission;
        }

        IPL_DEPRECATED("access xon_xoff_transmission directly",
                       void setXonXoffTransmission(const bool p_on_off) IPL_NOEXCEPT) {
            xon_xoff_transmission = p_on_off;
        }

        IPL_DEPRECATED("access xon_xoff_reception directly",
                       bool xonXoffReception() const IPL_NOEXCEPT) {
            return xon_xoff_reception;
        }

        IPL_DEPRECATED("access xon_xoff_reception directly",
                       void setXonXoffReception(const bool p_on_off) IPL_NOEXCEPT) {
            xon_xoff_reception = p_on_off;
        }

    };

public: // functions
    /**
     * \brief
     *     default constructor that creates a SerialPort with a
     *     sane default configuration and the given basic I/O
     *     parameters. Device name is left empty.

     *     Default configuration is: 57600 baud, no xon/xoff
     *     control at all, 1 stop bit, no parity check.
     *
     *     \c p_blocking, \c p_read_buffer and \c p_write_buffer
     *     have the same meaning as in \c StreamBinFileRW
     *     constructors.
     * \errors
     *     none
     **/
    SerialPort(const bool p_blocking = true,
            const size_t p_read_buffer=0,
            const size_t p_write_buffer=0) IPL_NOEXCEPT :
        StreamBinFileRW(p_read_buffer, p_write_buffer)
    {
        this->setBlocking(p_blocking);
    }

    //! \brief
    //!    Destructor calls close() like StreamBinFileW does. This
    //!    is needed to get our performFlush() implementation
    //!    called upon close.
    ~SerialPort() IPL_NOEXCEPT
    {
        if( SerialPort::close() ) // BRANCH_COVERAGE_UNTESTABLE
        {
            IPL_WARN("error closing SerialPort");
            ipl_error.ack();
        }
    }

    /**
     * \brief
     *     open the serial port that has previously been configured
     *     via setPortSettings()

     *     configuration is done at construction time (default
     *     constructor of PortSettings) by calling
     *     setPortSettings() or by doing each setting individually
     *     by calling the apropriate methods at the object returned
     *     by getPortSettings().
     *
     *     In case the serial port could not be correctly opened an
     *     appropriate error is raised. Invalid configuration is
     *     first indicated here and not when the configuration data
     *     is set.
     *
     *     On successful return the serial port is ready for
     *     operation and read and write calls can be performed at
     *     the object.
     *
     *     If the SerialPort is currently already opened then it
     *     will be closed before trying to open it with the
     *     currently set PortSettings.
     * \post
     *     if \c false is returned then the serial port is now
     *     ready with the currently set PortSettings applied
     * \return
     *     true on error, false otherwise
     * \errorindicator
     *     via isValid(), via return code
     * \errors
     *     The errors described at BinFileBase::open(const char*,
     *     const ReadWriteFlags&) are possible here, too.
     *
     *     Additionally these errors can occur:
     *
     *     ipl::CommonError with ID
     *
     *    - NOT_SUPPORTED if the current PortSetting isn't
     *    supported
     *     - INVALID_PARAMETER if the current PortSetting is
     *     invalid
     *
     *     FileAccessError with ID
     *     - BAD_PATH if the device couldn't be found
     *     - UNKNOWN_ACCESS_ERROR on other errors during
     *     opening/configuring the device
     **/
    bool open() IPL_NOEXCEPT;

    /**
     * \brief
     *     return the currently active port settings

     *     The currently active port settings will be returned as a
     *     complete set in form of a PortSettings struct. This
     *     struct can be used to change only a few settings
     *     directly on the object.
     *
     *     Note that changes to the settings object only take
     *     effect upon an open() call.
     * \return
     *     The currently active PortSettings struct of the
     *     SerialPort
     **/
    PortSettings& getPortSettings() IPL_NOEXCEPT
    {
        return m_port_settings;
    }

    /**
     * \brief
     *     Change the settings of the SerialPort.

     *     This changes the settings for the SerialPort. Note that
     *     the change of the settings first takes effect at the
     *     next time when open() is called.
     *
     *     Individual settings can also be changed separately by
     *     using the separate set... member functions provided.
     * \param[in]
     *     p_settings the new PortSettings struct to be used for
     *     configuration
     **/
    void setPortSettings(const PortSettings &p_settings) IPL_NOEXCEPT
    {
        m_port_settings = p_settings;
    }

    // waitForIncomingData()
    // can be used for blocking until new data arrives at the serial
    // port

    // static ipl::vector<ipl::string> getAvailablePorts();
    // can be used for getting a list of available SerialPorts in
    // the system.
protected: // functions
    // the following makes base class API protected that doesn't
    // make sense any more on SerialPort-level
    using StreamBinFileRW::open;
    using StreamBinFileRW::seek;

    /**
     * \brief
     *     Implementation of pure virtual method from
     *     IplOutputStream.

     *     Performs an actual flush operation on the serial port,
     *     if supported. Is triggered by IplOutputStream::flush.
     *
     *     This call will usually block until all pending output
     *     data is actually written. This behaviour is independant
     *     of the blocking or non-blocking setting of the
     *     SerialPort instance.
     * \see
     *     IplOutputStream::performFlush
     * \errorindicator
     *     via hasError(), via return code
     * \errors
     *     ipl::CommonError with IDs:
     *
     *     - INVALID_USAGE if the port is not currently known to be
     *     open.
     *
     *     osal::SysError with IDs:
     *
     *     - INTEGRITY_ERROR on severe system errors
     *     - INTERRUPTED if a system call was canceled
     *     - IO_FAILURE if reading failed due to device error or
     *     something
     *     - PERMISSION_DENIED if the operation isn't allowed for
     *     the caller
     *     - OUT_OF_MEMORY on lack of ressources to perform read
     *
     *     SerialPort::Error with IDs:
     *
     *     - INVALID_DEVICE if the device is not valid or cannot
     *     perform the required operation
     **/
    bool performFlush() IPL_NOEXCEPT;
private:
    //! the currently active port settings for the SerialPort.
    PortSettings m_port_settings;
}; // class SerialPort

} // end namespace

#endif
