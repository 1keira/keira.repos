/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_FILETRANSFER_HXX
#define TRACING_FILETRANSFER_HXX

#include <osal/Path.hxx>
#include <osal/FileInfo.hxx>
#include <util/crypt/DigestEngine.hxx>

namespace tracing
{
//! \brief FileStatusFlags constant definitions.
struct FileStatusFlags
{
    static const int8_t AVAILABLE          = 1 << 0;
    static const int8_t IS_FILE            = 1 << 1;
    static const int8_t READABLE           = 1 << 2;
    static const int8_t ERROR_IN_OPERATION = 1 << 3;
    static const int8_t UPLOAD             = 1 << 4;
};

//! \brief FileTransferFlags constant definitions.
struct FileTransferFlags
{
    static const int8_t FIRST_BLOCK = 1 << 0;
    static const int8_t LAST_BLOCK  = 1 << 1;
    static const int8_t UPLOAD      = 1 << 4;
};

//! \brief DigestType constant definitions.
struct DigestType
{
    static const int8_t DIGEST_NONE = 0;
    static const int8_t DIGEST_MD5  = 1;
    static const int8_t DIGEST_SHA1 = 2;
};

/*!
 * \brief
 *   FileStatus structure.
 *
 * Note: the order of members in this struct does not reflect
 *       their serialization order in FileStatusMessages!
 */
struct FileStatus
{
    int32_t                    id;          //! Transfer ID assigned by the trace core.
    int8_t                     flag;        //! File transfer flags, \sa FileStatusFlags.
    int64_t                    size;        //! File size.
    osal::FileTime             mtime;       //! Last modification time of file.
    osal::Path                 path;        //! Path to the file transferred.
    int8_t                     digest_type; //! Type of message digest, \sa DigestType.
    util::DigestEngine::Digest digest;      //! Message digest of file contents.
};

/*!
 * \brief
 *   Callback interface for file transfers.
 */
class IFileOperationFinishedCallback
{
public:
    //! \brief Virtual destructor.
    virtual ~IFileOperationFinishedCallback() = 0;

    /*!
     *    \brief
     *        Callback to indicate that file operation has finished.
     *
     *    \param
     *        status The file status info \sa FileStatus.
     */
    virtual void fileOperationFinished(const FileStatus & status) = 0;
};

inline IFileOperationFinishedCallback::~IFileOperationFinishedCallback() {/* nop */}

/*!
 * \brief
 *     Derive from this for "pseudo" file transfers, i.e. transferring a chunk of
 *     memory via the file transfer mechanism.
 */
class IFileTransferData
{
public:
    //! \brief Virtual destructor.
    virtual ~IFileTransferData() = 0;
    //! \brief Implement according to IBinInputStream::read() semantics.
    virtual int_fast8_t read(void * const p_read_buffer, const size_t p_max_bytes,
                             size_t & p_bytes_read) = 0;
    //! \brief Shall return true, if data was read completely.
    virtual bool endOfStream() const = 0;
    //! \brief After this is called, you can free all resources associated with
    //!        this transfer. This is called exactly once.
    virtual void dispose() = 0;
};

inline IFileTransferData::~IFileTransferData() {/* nop */}

} // end of namespace tracing

#endif /* TRACING_FILETRANSFER_HXX */

