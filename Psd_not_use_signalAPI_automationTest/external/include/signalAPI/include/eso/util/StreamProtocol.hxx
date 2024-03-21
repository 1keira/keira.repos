/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_STREAMPROTOCOL_HXX
#define UTIL_STREAMPROTOCOL_HXX
/****************************************************************************/

#include <util/util_dso.h>
#include <util/transport/PeerInfo.hxx>
#include <util/Descriptor.hxx>
#include <osal/Socket.hxx>
#include <common/buffers.hxx>
#include <common/error/ErrorType.hxx>

#include <map>
#include <stddef.h>
#include <memory>
#include <functional>

/****************************************************************************/

namespace util {

/*****************************************************************************/

    /*!
        \brief Framing and other protocol logic interface
        
        If you need to separate a byte stream into messages,
        optionally implementing additional protocol features,
        implement against this interface and plug in a different implementation
        if needed.
            
        The protocol inherits ipl::Buf::Allocator so it can preallocate
        space for a header. Forward malloc() calls to an ipl::Buf::PreAllocator
        with the right header size.
            
        If your concrete protocol has some initial handshake messages to send,
        return them from initial_message() one by one. They will be sent out
        before the next payload.
        On the receiving side they will get passed to internal_payload()
        instead of to the client.
        
        prepare() will be called with a client payload to be sent and should
        add a header to it. The normal way would be to first check whether
        your protocol already \ref ipl::Buf::PreAllocator::owns() "owns" the
        buffer, which implies that header space is already preallocated.
        In that case you can fill in its
        \ref ipl::Buf::PreAllocator::header() "header" and return
        \ref ipl::Buf::PreAllocator::all() "all", i.e. the buffer including the
        header.
        If the data buffer comes from another allocator,
        \ref ipl::Buf::Allocator::copy() "copy" it to a new one with
        preallocated header. It is up to the caller to free any buffer that
        might have been copied.
        
        realloc_header() gets a (possibly NULL) buffer not too big for a header,
        determines the actual header size (as far as yet known),
        \ref ipl::Buf::Allocator::copy() "copies" the buffer to a new one
        with that size and returns that. The too small original must be freed.
        This can be iterated if the actual header size is dynamic in some way,
        in that case the method might need to parse the buffer.
        If the provided buffer already has the correct size, it must be returned
        without copying/freeing anything.
        It is up to the caller to determine that the size hasn't changed
        and stop calling.
        
        A finally fully received header is passed to parse_header(), which
        should parse the header (duh!). It returns a Result structure which
        besides others contains a flag whether the message should be delivered
        to the client or to internal_payload(). In the latter case some
        internal data extracted from the header can be attached as
        Result::context and will be passed to internal_payload() together
        with the payload portion of the message, so the protocol can have
        full access to any relevant information from the original header.
    */
    class UTIL_EXPORT StreamProtocol: public ipl::Buf::Allocator {
    
    public:
        
        //! Callback interface - implement and pass to protocol instance
        class Client;
        
        using Stream=osal::Socket;  // ipl::IBinInOutStream?
        //! Type of factory function for StreamProtocol instances
        using Create=std::function<std::unique_ptr<StreamProtocol> (Client *client, ipl::Buf::Allocator &underlying)>;
        //! Type of meta factory function for StreamProtocol factories,
        //! closing over keyword arguments from \p descriptor.
        //! The digested arguments are removed from \p descriptor, so you can
        //! check afterwards what's left, i.e what wasn't understood.
        using Factory=Create (*) (/* non-const, we may patch it */ Descriptor &descriptor);
        using Context=std::shared_ptr<void>;
        
        //! \brief %Result of parsing a header
        struct Result {
            size_t bytes;     //!< \brief Frame size
            bool internal;    //!< \brief Whether this frame is internal to the protocol
            bool error;       //!< \brief Whether the header is invalid
            Context context;  //!< \brief Potential opaque info associated with an internal frame
            
            explicit operator bool () const { return error; }
            
            Result(bool error, bool internal, size_t bytes=-1,
                   std::shared_ptr<void> context={}):
                bytes(bytes), internal(internal), error(error), context(context) {}
        };
        
        StreamProtocol(Client *client, size_t max_bytes=(size_t)-1):
            max_bytes(max_bytes), client(client) {
            IPL_ASSERT(client);
        }  // initialized later
        ~StreamProtocol() override=default;
        
        //! \brief A message (including any header) that should be sent
        //! to the peer before any payload data, or NULL
        //!
        //! This can return different messages on subsequent calls, so several
        //! initial messages can be sent. Ultimately it will need to settle
        //! for NULL or no payload can ever be sent after the initial message(s).
        virtual ipl::Buf initial_message() IPL_NOEXCEPT;
        //! \brief Process the body of a message that was marked internal
        virtual bool internal_payload(const Context &header, const ipl::Buf &data) IPL_NOEXCEPT;
        
        //! \brief Add a header to one message's worth of \p data
        //!
        //! \warning The returned Buf can be \p data,
        //! a different view into \p data or a copy of \p data,
        //! which is relevant for who deletes what.
        //! If the returned buffer's \ref ipl::Buf::allocator "allocator" member
        //! differs from \p data's, free \p data, if not both share a buffer.
        virtual ipl::Buf prepare(const ipl::Buf &data)=0;
        
        //! \brief Allocate a buffer for receiving a header into
        //! 
        //! ...or rather enough of a header to determine how much more
        //! potentially needs to be received.
        //! This means you start with a default-constructed \p buffer,
        //! realloc to needed size, receive into it
        //! and realloc again until the returned buffer is the same size as
        //! what you put in.
        //!
        //! If this actually reallocates, the original buffer is automatically
        //! copied over and freed.
        virtual ipl::Buf realloc_header(const ipl::Buf &buffer)=0;
        //! \brief Parse \p data as a protocol header
        //!
        //! Determine the payload size of the message, whether it is part of
        //! the data stream passed to the client or rather something internal
        //! to be digested by internal_payload(), or if it is invalid anyway.
        virtual Result parse_header(const ipl::Buf &data)=0;
        
        static ipl::ErrorType error;
        enum ErrorId { invalid_size, invalid_buffer, invalid_header, };
        
        //! \brief Digest (and remove) all known keyword arguments from
        //! \p descriptor and return a Create function obeying them
        static Create factory(const std::string &name,
                              /* non-const, we may patch it */ Descriptor &descriptor) {
            auto i=factories.find(name);
            if(i!=factories.end())
                return i->second(descriptor);
            return nullptr;
        }
        
        //! \brief Convenience wrapper
        template <typename Protocol> static void sign_on() {
            sign_on(Protocol::name, Protocol::factory);
        }
        //! \brief Convenience wrapper
        template <typename Protocol> static void sign_off() {
            sign_off(Protocol::name);
        }
        
        //! \brief \e Inclusive maximum for message payload size
        //! supported by this protocol
        const size_t max_bytes;
        
    protected:
        static void sign_on(const std::string &name, const Factory &factory) {
            factories[name]=factory;
        }
        static void sign_off(const std::string &name) {
            factories.erase(name);
        }
        
        Client *client;
        
        using Factories=std::map<std::string, Factory>;
        static Factories factories;
    };

/****************************************************************************/

    class StreamProtocol::Client {
        
    public:
        virtual ~Client()=default;
        //! Can be called zero or more times, new \p peerinfo should override
        //! any previous
        virtual void peerinfo(
            const std::shared_ptr<transport::PeerInfo> &peerinfo
        ) IPL_NOEXCEPT=0;
    };

/****************************************************************************/

}  // end of namespace util

/****************************************************************************/
#endif
