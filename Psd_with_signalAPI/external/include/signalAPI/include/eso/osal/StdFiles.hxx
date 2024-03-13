/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OSAL_STDFILES_HXX
#define OSAL_STDFILES_HXX

#include <ipl_config.h>

#include <common/streams/istream.hxx>
#include <common/streams/ostream.hxx>

#include <osal/osal_dso.h>
#include <osal/osal.hxx>
#include <osal/StreamBinFileR.hxx>
#include <osal/StreamBinFileW.hxx>
#include <osal/FmtFileWrapper.hxx>

namespace osal
{

/**
 *    \brief
 *        A StreamBinFile representation for the stdin file

 *        This is a OSAL stream-based access file object for the stdin file handle i.e. it
 *        matches the ipl::cin object.
 **/
class OSAL_EXPORT StdinBinFile :
    public osal::StreamBinFileR
{
public:
    StdinBinFile(const size_t read_buffer = 0) IPL_NOEXCEPT;

    ~StdinBinFile() IPL_NOEXCEPT
    {
        // that will never fail :-)
        //
        // destructor must be overwritten to allow overwritten
        // definiton of close to be called at destruction time!
        StdinBinFile::close();
    }

    //! stdin should never be closed
    bool close() IPL_NOEXCEPT
    { this->m_file = OSAL_INVALID_FILE_HANDLE; return false; }
}; // end class

typedef FmtFileWrapper<StdinBinFile, ipl::istream, StdinBinFile::ReadFlags> StdinFmtFile;

/**
 *    \brief
 *        A BinFile representation for the stdout stream

 *        This is a OSAL stream-based access file object for the stdout file handle i.e. it
 *        matches the ipl::cout object.
 **/
class OSAL_EXPORT StdoutBinFile :
    public osal::StreamBinFileW
{
public:
    StdoutBinFile(const size_t write_buffer = 0) IPL_NOEXCEPT;

    ~StdoutBinFile() IPL_NOEXCEPT
    {
        // that will never fail :-)
        //
        // destructor must be overwritten to allow overwritten
        // definiton of close to be called at destruction time!
        StdoutBinFile::close();
    }

    //! stdout should never be closed
    virtual bool close() IPL_NOEXCEPT
    { this->m_file = OSAL_INVALID_FILE_HANDLE; return false; }
}; // end class

typedef FmtFileWrapper<StdoutBinFile, ipl::ostream, StdoutBinFile::WriteFlags> StdoutFmtFile;

/**
 *    \brief
 *        A BinFile representation for the stderr stream

 *        This is a OSAL stream-based access file object for the stderr file handle i.e. it
 *        matches the ipl::cerr object
 **/
class OSAL_EXPORT StderrBinFile :
    public osal::StreamBinFileW
{
public:
    StderrBinFile(const size_t write_buffer = 0) IPL_NOEXCEPT;

    ~StderrBinFile() IPL_NOEXCEPT
    {
        // that will never fail :-)
        //
        // destructor must be overwritten to allow overwritten
        // definiton of close to be called at destruction time!
        StderrBinFile::close();
    }

    //! stderr should never be closed
    bool close() IPL_NOEXCEPT
    { this->m_file = OSAL_INVALID_FILE_HANDLE; return false; }
}; // end class

typedef FmtFileWrapper<StderrBinFile, ipl::ostream, StderrBinFile::WriteFlags> StderrFmtFile;

} // end osal

#endif
