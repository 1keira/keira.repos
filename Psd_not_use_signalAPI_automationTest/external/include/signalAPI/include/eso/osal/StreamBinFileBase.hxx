/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_STREAMBINFILEBASE_HXX
#define OSAL_STREAMBINFILEBASE_HXX

#include <ipl_config.h>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/BinFileBase.hxx>

namespace osal {

    /**
    *    \brief
    *        Base class for stream-based, binary access to files

    *        This base class introduces stream-based access to files. This is the most common way
    *        of doing i/o with files. The system maintains a file position pointer within the
    *        file from where a number of bytes can be transferred into a client provided buffer
    *        or written to from a client provided buffer, respectively.
    *
    *        If the file corresponds to a regular file or in some case special device files that
    *        support it then the client can call seek() to move the file position pointer to an
    *        arbitrary position in the file. This is mainly a special property of regular files.
    *        For this reason I decided not to introduce the seek() method in the abstract binary
    *        stream classes for now. You can never seek on communication streams for example
    *        sockets, serial lines and alike. Thus the benefit of having seek() in the general
    *        stream abstraction would be small. Another way would have been to introduce a
    *        general "seekable binary stream" class on top of binary streams but I found it would
    *        be overkill.
    **/
    class OSAL_EXPORT StreamBinFileBase :
        public BinFileBase
    {
    public: // types

        /**
        *    \brief
        *        Data type used in seek() function.
        **/
        enum SeekDirection
        {
            //! perform seek relative to the current file pointer position
            CURPOS,
            //! perform seek relative to the begin of the file (position zero)
            BEGIN,
            //! perform seek relative to the end of the file
            END
        };

        /**
        *    \brief
        *        Seek to a new read/write position in the file

        *        The file position pointer will be moved to \c offset relative to \c
        *        direction. The new absolute file position will be returned in \c newpos.
        *
        *        Note that if you have your file opened for writing and you move the file
        *        position beyond the end of file and start writing data there then you may
        *        end up with "holes" in your file i.e. the file seems to be bigger then it
        *        actually is (FileInfo.getSize() would be bigger then FileInfo.getBlocks() *
        *        FileInfo.getBlockSize()).
        *
        *        This function is virtual to allow derived classes to perform additional
        *        actions upon seeking. This is necessary as seeking can e.g. mess up
        *        buffering schemes.
        *    \return
        *        true on error, false otherwise
        *    \errorindicator
        *        via return code
        *    \errors
        *        osal::SysError with IDs
        *
        *        - INVALID_ARGUMENT if the resulting file position is invalid (e.g. a
        *        negative file position pointer would be the result)
        *        - INTEGRITY_ERROR on severe internal errors
        *        - UNKNOWN_ERROR on other occasions
        **/
        virtual bool seek(int offset, const SeekDirection direction, size_t &newpos) IPL_NOEXCEPT;

    protected: // functions

        //! Constructs an invalid stream binary file
        StreamBinFileBase() IPL_NOEXCEPT :
            BinFileBase()
        { }
    };

}  // end of namespace osal

#endif
