/*
    Copyright e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_IPOBJECT_HXX
#define OSAL_IPOBJECT_HXX

#include <limits>

#include <ipl_config.h>

#include <common/streams/ostream.hxx>
#include <common/types/string.hxx>
#include <common/types/algorithm.hxx>
#include <common/CommonError.hxx>

#if defined IPL_OS_POSIX || defined IPL_OS_INTEGRITY
#    include "IPObjectDefs-posix.hxx"
#elif defined IPL_OS_WINPC
#    include "IPObjectDefs-win32.hxx"
#else
#    error "error undefined IPL_OS_ variant"
#endif
#include <osal/osal_dso.h>

namespace osal
{

/**
    \brief
        Abstract Base class for objects that use the IP-protocol, e.g. 
        TCP and UDP based sockets.
 **/
class OSAL_EXPORT IPObject
{
public:
    //! This provides a string representing the local loopback IP address
    static const char* const LOOPBACK_IP;
    //! This provides a string representing the local loopback IPv6 address
    static const char* const LOOPBACK_IP6;
    //! \brief
    //!    This provides a string representing "any" IPv4 address and can be used
    //!    for wildcard / don't care addressing in certain contexts
    static const char* const ANY_IP;

    //! \brief
    //!    This provides a string representing "any" IPv6 address and can be used
    //!    for wildcard / don't care addressing in certain contexts
    static const char* const ANY_IP6;

    //! \brief
    //!    An enum to differentiate between different versions of IP protocol schemes

    //!    The main difference for the user between the two available types is the used
    //!    addressing scheme
    enum IPProtocolVersion
    {
        //! IP version 4, supporting 32 bit addresses
        IPV4,
        //! \brief
        //! IP version 6, supporting 64 bit addresses
        IPV6,
        //! \brief
        //! unspecified protocol version
        IPVUNSPEC
    };

    class IPResolver;

    /**
       \brief
           An IP socket address, i.e an IP address plus a port member
     **/
    struct OSAL_EXPORT IPAddress
    {
        /**
            \brief
                adress string

                The address of an IPv4 or IPv6 communication node either
                as a numbers and dots IP address or as a network
                name that can be resolved via the systems DNS
                service
         **/
        std::string address;
        /**
            \brief
                The 16-bit port number to use for in
                conjuncation with \c address
         **/
        uint16_t port;

        IPAddress() : port(0) { };
        IPAddress(const std::string &a, const uint16_t p) :
            address(a),
            port(p) { }
        IPAddress(const IPAddressHandle &a);
        IPAddress(const IPAddressHandle6 &a);

        /**
            \brief
                Get binary IPv4 address

                Attempts to get a binary representation of the
                currently set IPv4 address and port and put it
                into \c h
            \return
                \c true on error, \c false on success
            \note
                This function calls resolve() for being able to
                convert the actual IP address into binary
                format.
         **/
        bool getBinary(IPAddressHandle &h);

        /**
            \brief
                Get binary IPv6 address

                Attempts to get a binary representation of the
                currently set IPv6 address and port and put it
                into \c h
            \return
                \c true on error, \c false on success
            \note
                This function calls resolve() for being able to
                convert the actual IP address into binary
                format.
         **/
        bool getBinary(IPAddressHandle6 &h);

        /**
            \brief
                Get binary IP address

                Attempts to get a binary representation of the
                currently set address string and port and put it
                into \c h

                The type of address (v4/v6) can be read from h.ss_family
                after the call returns.
            \return
                \c true on error, \c false on success
         **/
        bool getBinary(IPAddressHandleAny &h);

        //! Compare equal operator
        bool operator==(const IPAddress &other) const
        {
            return address == other.address &&
                port == other.port;
        }

        //! Opposite of compare equal operator
        bool operator!=(const IPAddress &other) const
        {
            return ! operator==(other);
        }

        /**
            \brief
                Checks IP address

                Returns whether the currently stored address is
                a valid IP address in numerical notation
            \return
                \c true if \c address is a valid IP address,
                \c false otherwise
         **/
        bool isNumbersAndDotsIP() const;

        /**
            \brief
                Checks if the IP address is a multicast address
            
            \return 
                \c true if \c address is a multicast IP address
                \c false otherwise
         */
        inline bool isMulticastIP(const IPProtocolVersion p_ip_version=IPV4) const;

        /**
            \brief
                Resolves the stored address into an IP address,
                if neccessary

                After successful return, the address member will
                contain the numbers and dots notation of the
                address/hostname stored there previously.
            \return
                true on error, false on success
            \errorindicator
                via return code
            \errors
                errors as defined at IPResolver::resolveName()
                can occur.

                ipl::CommonError with IDs:

                - INVALID_PARAMETER if no resolve result could
                be obtained.
         **/
        bool resolve(const IPProtocolVersion p_ip_version=IPV4);
        
        //! If address cannot be resolved into IPv4 or IPv6 address,
        //! IPVUNSPEC is returned.
        IPProtocolVersion address_type() {
            return IPObject::address_type(*this);
        }

        /**
            \brief
                Creates IPAddressHandle from parameters

                Creates an IPAddressHandle from the given binary
                IPv4 address represented by four bytes in host
                byte order
         **/
        static IPAddressHandle makeHandle(
            const uint32_t ip,
            const size_t port = 0);

        /**
            \brief
                Creates IPAddressHandle6 from parameters

                Creates an IPAddressHandle6 from the given binary
                IPv6 address represented by 16 bytes in network
                byte order
         **/
        static IPAddressHandle6 makeHandle(
            const struct in6_addr &ip,
            const size_t port = 0,
            const uint32_t scope_id = 0);

        /**
            \brief
                Get binary representation from IPAddressHandle

                Writes the binary representation of the given
                IPAddressHandle as four bytes in host byte order
                into \c ip
         **/
        static void getBinary(
            const IPAddressHandle &handle,
            uint32_t &ip,
            size_t &port);

        /**
            \brief
                Get binary representation from IPAddressHandle6

                Writes a binary representation of the given
                IPAddressHandle6 as in6_addr \c ip
         **/
        static void getBinary(
            const IPAddressHandle6 &handle,
            struct in6_addr &ip,
            size_t &port,
            uint32_t &scopeid);

        /**
            \brief
                An IPAddress object that has set don't care values.

                i.e. address will be ANY_IP and port will be 0.
         **/
        static const IPAddress ANY_ADDRESS;

        /**
            \brief
                An IPAddress object that has set don't care values.

                i.e. address will be ANY_IP6 and port will be 0.
         **/
        static const IPAddress ANY_ADDRESS6;
    private:
        /**
         * \brief
         *     This function tries to resolve the address string in
         *     p_ascii_address into a suitable binary IP representation and put
         *     it into p_binary_address

        *     In case the user specifies a hostname instead of an IP numbers
        *     and dots notation then this function tries to resolve that
        *     hostname and put it into a binary IP representation.
        *
        *     In case it is already in numerical notation then only the
        *     convertion into binary form is performed. The result is stored
        *     in the according IPSocketHandle.
        * \param[in]
        *     p_ascii_address The IP address in ascii format
        * \param[in]
        *     p_binary_address Here the binary result will be stored, if
        *     successful.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        **/
        bool convertAddrToBinary(sockaddr_in &p_binary_address) IPL_NOEXCEPT;

        /**
         * \brief
         *     This function tries to resolve the address string in
         *     p_ascii_address into a suitable binary IP representation and put
         *     it into p_binary_address

        *     In case the user specifies a hostname instead of an IP numbers
        *     and dots notation then this function tries to resolve that
        *     hostname and put it into a binary IP representation.
        *
        *     In case it is already in numerical notation then only the
        *     convertion into binary form is performed. The result is stored
        *     in the according IPSocketHandle.
        * \param[in]
        *     p_ascii_address The IP address in ascii format
        * \param[in]
        *     p_binary_address Here the binary result will be stored, if
        *     successful. Must be set to 0.
        * \return
        *     true on error, false on success
        * \errorindicator
        *     via return code
        **/
        bool convertAddrToBinary6(sockaddr_in6 &p_binary_address) IPL_NOEXCEPT;

        /**
         * \brief
         *     This function resolves the passed address string and converts it
         *     into the binary form.
         *
         *     To find out if the address string resolved to an IPv4 or IPv6
         *     address check the ss_family member of the out parameter \c binary_address.
         *
         * \param[in]
         *     address The IP address string
         * \param[in]
         *     binary_address Here the binary result will be stored, if
         *     successful.
         * \return
         *     true on error, false on success
         * \errorindicator
         *     via return code
         **/
        bool convertAddrToBinaryAny(sockaddr_storage &binary_address) IPL_NOEXCEPT;
    };


    /**
        \brief
            Retrieves the name for the current machine

            The hostname is by any chance the internet or maybe
            intranet DNS name of the machine and thus allows
            potentially to assign a socket to the associated IP
            address and thus the network interface.
        \note
            Although this function is not actually socket/networking
            specific the OSs logically connect it to the
            socket/networking API.
        \param[out] hostname
            Here the hostname retrieved from the system will be
            stored
        \return
            true on error, false on success
        \errorindicator
            via return code
        \errors
            ipl::CommonError with IDs:

            - OUT_OF_MEMORY if allocation of string(s) failed

            SystemError with IDs:

            - INTEGRITY_ERROR on severe internal errors
     **/
    static bool getHostname(std::string &hostname);

    virtual ~IPObject();

    //! returns the IPProtocolVersion specified at construction time
    IPProtocolVersion getIPProtocolVersion() const
    {
        return m_ip_version;
    }

    //! If address cannot be resolved into IPv4 or IPv6 address,
    //! IPVUNSPEC is returned.
    static IPProtocolVersion address_type(IPAddress address /* copy because resolve() mutates */) {
        ipl::ErrorStorage ignoreme;
        osal::IPAddressHandleAny handle;
        if(address.getBinary(handle))
            return IPVUNSPEC;
        // yeah, sure, full OS internals leaked into higher layers
        // because reasons
        switch(handle.ss_family) {
        default:
            return IPVUNSPEC;
        case AF_INET:
            return IPV4;
        case AF_INET6:
            return IPV6;
        }
    }

    /**
        \brief
            Return a reference to the local IP address used for
            communication

            If you want to examine what the local IP address used
            for communication actually is you can retrieve it via
            this function call.
        \return
            The returned object is a reference to the internally
            stored IPAddress object.  This is to avoid copying of
            the involved address string.
     **/
    const IPAddress& getLocalAddress() const
    {
        return m_local_address;
    }

protected:
    /**
        \brief
            Constructs a new IPObject using the given IP protocol
            version
        
        \param[in]
            p_src The IP address of this object
        \param[in]
            p_ip_version IP version to use.
     **/
    IPObject(const IPAddress &p_src, IPProtocolVersion p_ip_version);

    //! the local IP address to use
    IPAddress m_local_address;
    IPProtocolVersion m_ip_version;

    //! IP version specific, OS specific handle
    IPSocketHandle m_ipsocket_handle;
}; // end class


//! \brief
//!    A subclass that allows resolving of hostnames and ip addresses
//!    into each other
class OSAL_EXPORT IPObject::IPResolver
{
public:
    IPResolver();
    IPResolver(const IPResolver&) = delete;
    IPResolver& operator=(const IPResolver&) = delete;

    //! releases all string copies possibly present due to resolving
    ~IPResolver();

    static constexpr size_t resolve_error = std::numeric_limits<size_t>::max();

    /**
        \brief
            Resolve a hostname into an (or many) IP address

            All IP addresses that could be found are stored
            internally in the object. They can be accessed via
            getItem().

            Any previous resolve results will be deleted by this
            call.
        \param[in]
            p_hostname The hostname that is to be resolved into all
            IP address known for it.
        \param[in]
            p_ip_version The IP version for which addresses should
            be resolved.  Only addresses matching this version will
            be returned.
        \return
            The number of IP addresses that could be resolved for
            the given hostname, or \c resolve_error on error
        \return
            \c resolve_error on error otherwise the number of resolved items in
            the object.
        \errorindicator
            via return code
        \errors
            ipl::CommonError with IDs

            SysError with IDs

            - OUT_OF_MEMORY on lack of memory ressources to perform
            operation
            - UNKNOWN_ERROR on other errors

            SocketBase::Error with IDs

            - RESOLVE_FAILED on resolve specific errors
     **/
    size_t resolveName(
        const char* const p_hostname,
        const IPProtocolVersion p_ip_version = IPV4);

    /**
        \brief
            Resolve an IP address into its known hostnames

            Only one hostname may match the given IP. It can be
            accessed via getItem(0) in case > 0 is returned.

            Any previous resolve results will be deleted by this call.
        \param[in]
            p_ip_addr The IP address that is to be resolved into a
            hostname
        \param[in]
            p_fqdn Boolean flag that determines wheter a fully
            qualified domain name should be returned or only a short
            form of the hostname.
        \param[in]
            p_ip_version Which IP version should be
            returned/resolved. Currently only the default of IPV4 is
            supported.
        \return
            > 0 if resolving was successful, 0 if there was no
            name found matching the IP, < 0 on error
        \errorindicator
            via return code < 0
        \errors
            ipl::CommonError with IDs

            - INVALID_PARAMETER if \c p_ip_addr is no valid IP in
            numbers and dots notation

            SysError with IDs

            - OUT_OF_MEMORY on lack of memory ressources to perform
            operation
            - INTEGRITY_ERROR on severe internal errors
            - UNKNOWN_ERROR on other errors

            SocketBase::Error with IDs

            - RESOLVE_FAILED on resolve specific errors
     **/
    size_t resolveIP(
        const char* const p_ip_addr,
        const bool p_fqdn=false,
        const IPProtocolVersion p_ip_version = IPV4);

    /**
        \brief
            Return the requested resolved item string

            After a successful call to resolveName or resolveIP you
            can access any results via this function. If the chosen
            index is invalid then an assertion will occur.

            Index counting begins at zero i.e. if you have one
            result then it will be accessed via index zero.
        \return
            A constant reference to the resolved item string. If you
            want to keep the string after the validity of the
            resolve result has expired you need to make a copy of
            the string.
        \errors
            if an invalid index is selected an assertion will occur
     **/
    const std::string& getItem(const size_t p_index) const;

    /**
        \brief
            Returns the number of items currently available in the object
     **/
    size_t getCount() const;
protected:
    size_t resolveAddr(
        const char* const p_addr,
        const bool p_fqdn=false,
        const bool p_numeric_addr=false,
        const IPProtocolVersion p_ip_version = IPV4);
private:
    void freeResolveHandle(ResolveHandle& handle);
    ResolveHandle m_resolve_handle;
};

} // end namespace


/**
 * \brief
 *     stream output operator for printing an IPAddress
 **/
inline ipl::ostream& operator<<(
    ipl::ostream &o,
    const osal::IPObject::IPAddress &a)
{
    // Check if IPv6 address
    if(a.address.find(':') != std::string::npos)
    {
        o << "[" << a.address << "]:" << a.port;
    }
    else
        o << a.address << ":" << a.port;
    return o;
}

#endif // OSAL_IPOBJECT_HXX
