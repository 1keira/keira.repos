#ifndef OSAL_GHSSERVERCONNECTION_HXX
#define OSAL_GHSSERVERCONNECTION_HXX

/*
    Copyright e.solutions GmbH
    All rights reserved
    Authors:
        Joerg Kupietz
*/

#include <ipl_config.h>

#include <osal/integrity/GHSConnectionBase.hxx>
#include <osal/integrity/GHSConnection.hxx>

namespace osal
{

class OSAL_EXPORT GHSServerConnection :
   public GHSConnectionBase
{
public:
    GHSServerConnection (const ipl::string& p_listen_address);

    virtual ~GHSServerConnection ();
    bool enableListen ();
    GHSConnection::Description acceptConnection ();

protected:
    virtual bool performRead (void* const p_read_buffer,
            const size_t p_max_bytes, size_t &p_bytes_read);

    virtual bool performWrite (const void* const p_write_buffer,
            const size_t p_max_bytes, size_t &p_bytes_written);

    virtual bool performFlush ();
};

} // end namespace osal

#endif /* OSAL_GHSSERVERCONNECTION_HXX */

