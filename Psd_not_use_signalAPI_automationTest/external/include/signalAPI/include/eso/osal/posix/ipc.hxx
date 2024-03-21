/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_IPC_HXX
#define OSAL_IPC_HXX

namespace osal
{

/**
 * \brief
 *     transforms the platform-independent IPC object identifier \c label to
 *     a platform-dependent, conforming identifier stored at \c identifier

 *     \c size determines the number of bytes abvailable at \c identifier.
 *
 *     \c label is considered to be properly null-terminated.
 *
 *     if \c label is no valid platform-independent identifier then \c true
 *     is returned and an according error raised.
 * \return
 *     \c true on error, \c false on success
 **/
bool OSAL_EXPORT transformToIPCIdentifier(
    const char *label,
    char *identifier,
    const size_t size);

} // end ns

#endif
