/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_IMESSAGEDECODER_HXX
#define TRACING_IMESSAGEDECODER_HXX

#include <common/types/string.hxx>

namespace tracing
{

/*!
 *    \brief
 *        Interface class for message decoders.

 *        Message decoders provide functionality to transform an instance
 *        of class Message into a (possibly) human-readable string so
 *        that it can be used by a message formatter and a backend.
 *        If you want to use a message decoder it needs to be specified in
 *        the tracing configuration file as a subtree below the "decoders"
 *        node. See the reference tracing configuration file for an example.
 *
 *    \sa IMessageFormatter
 *    \sa IBackend
 */
class IMessageDecoder
{
public:
    //! \brief Virtual destructor.
    virtual ~IMessageDecoder() {/* nop */}

    //! \brief Returns the name of the decoder, should be the class name.
    static const char * getMessageDecoderName() { return nullptr; }

    //! \brief Returns the version of the message decoder.
    static int32_t getMessageDecoderVersion() { return 0; }

    //! \brief Creates a message decoder by calling its constructor and returning
    //! the resulting instance pointer.
    static IMessageDecoder * create() { return nullptr; }

    //! \brief Destroys a message decoder.
    static void destroy(IMessageDecoder * decoder) { delete decoder; }

    /*!
     *    \brief
     *        Decodes a message.
     *    \param
     *        data Raw data pointing to the message data part of a Message.
     *        \sa Message::getMessageData()
     *    \param
     *        len Number of valid bytes, data points to.
     *        \sa Message::getMessageSize()
     *    \param
     *        decoded_message After successfully decoding the message the decoder
     *        will put a string in this parameter which can be used by backends
     *        for printing.
     *    \return
     *        true if message could be decoded, false otherwise.
     */
    virtual bool decodeMessage(const void * data, size_t len, ipl::string & decoded_message) = 0;

protected:

};

} // end of namespace tracing

#endif /* TRACING_IMESSAGEDECODER_HXX */

