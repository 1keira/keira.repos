/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_IMSGWRITER_HXX
#define UTIL_IMSGWRITER_HXX

#include <ipl_config.h>
#include <util/util_dso.h>

#include <util/transport/Writeable.hxx>
#include <functional>

namespace util
{
namespace transport
{

/**
 * \brief
 *     Callback interface for writing message data into a writable
 *     object

 *     The ITransport's send API uses possibly windowed buffers that
 *     are obtained at the transport level. To reduce complexity and
 *     increase error-robustness these features can only be accessed
 *     using the IMsgWriter callback interface.
 *
 *     Transport clients have to call the send API at a transport
 *     interface stating the needed buffer size and providing an
 *     IMsgWriter instance. This instance will then be called with a
 *     Writeable of the apropriate size to fill in the message data.
 *     This mechanism may be used in a stack like fashion i.e.
 *     different application stack layers may add their header data and
 *     windows along the way until the highest stack layer is reached.
 *     Upon return from all stack layers the data will be sent on the
 *     transport.
**/
class UTIL_EXPORT IMsgWriter
{
public:
    virtual ~IMsgWriter() { };

    /**
     * \brief
     *    Write the \c w
     * \errorindicator
     *    return true on error and false on success
     * \errors
     *    depends on the concrete implementation of the interface
    */
    virtual bool write(const Writeable &w) = 0;
}; // class

/**
 * \brief
 *    Generic Adapter class immplementing the IMsgWriter interface
**/
class UTIL_EXPORT MsgWriterAdapter : public IMsgWriter
{
public:
    using Writer = std::function<bool(const Writeable &w)>;

    MsgWriterAdapter(Writer w)
      : m_writer{w}
    {}
    virtual ~MsgWriterAdapter() {};

    bool write (const Writeable& w) override {
        return m_writer(w);
    }

private:
   Writer m_writer;
};

} // end namespace transport
} // end namespace util

#endif
