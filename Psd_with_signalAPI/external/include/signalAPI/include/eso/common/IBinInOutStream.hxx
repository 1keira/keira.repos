/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef IPL_IBININOUTSTREAM_HXX
#define IPL_IBININOUTSTREAM_HXX

#include <ipl_config.h>
#include <common/ipl_namespace.hxx>

#include <common/iplcommon_dso.h>
#include <common/stdint.h>

#include <common/IBinInputStream.hxx>
#include <common/IBinOutputStream.hxx>

namespace IPL_NAMESPACE
{

/**
    \brief
        Combined binary input and output stream

        This interface pulls together IBinInputStream and IBinOutputStream to derive from in
        case you want to implement both interfaces.

        If you choose to use a stream buffer then note that for input and output two
        completely independent buffers can be applied. No merged buffer like in the C++
        streams library is maintained.

        This is especially important if you have a stream that can be seeked on, because
        both buffers have to be managed to reflect that seek accordingly.
**/
class IBinInOutStream :
    public ipl::IBinInputStream,
    public ipl::IBinOutputStream
{
public: // functions
    /**
     *    \brief
     *        Construct an input/output stream according to supplied parameters.
     *    \param[in] p_blocking
     *        Whether in/out operations are blocking or not
     *    \param[in] p_buffersize
     *        Buffer size for both input and output operations (two buffers of that size
     *        will be allocated)
     **/
    IBinInOutStream(const bool p_blocking, const size_t p_buffersize=0) IPL_NOEXCEPT :
        IBinInputStream(p_blocking, p_buffersize),
        IBinOutputStream(p_blocking, p_buffersize)
    {
        this->setBlocking(p_blocking);
    }

    /**
     *    \brief
     *        Construct an input/output stream with differing buffersizes for input and
     *        output
     **/
    IBinInOutStream(const bool p_blocking, const size_t p_inbuffersize,
                    const size_t p_outbuffersize) IPL_NOEXCEPT :
        IBinInputStream(p_blocking, p_inbuffersize),
        IBinOutputStream(p_blocking, p_outbuffersize)
    {
        this->setBlocking(p_blocking);
    }

    ~IBinInOutStream() IPL_NOEXCEPT { }

    /**
     *    \brief
     *        Returns the validity for both ends of the stream
     **/
    virtual bool isValid() const IPL_NOEXCEPT
    {
        return IBinInputStream::isValid() && IBinOutputStream::isValid();
    }

}; // end class

} // end namespace ipl

#endif /* IPL_IBININOUTSTREAM_HXX */
