/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#include <ipl_config.h>

#include <string.h>

#include <iplbase/exceptions.hxx>

#include <common/CommonError.hxx>

#include <osal/SysError.hxx>
#include <osal/FileSys.hxx>
#include <osal/FileInfo.hxx>
#include <osal/TreeWalker.hxx>
#include <osal/Path.hxx>
#include <osal/OpenError.hxx>

#include <util/FileSys.hxx>

namespace util
{

//! \brief
//!    Helper class for util::FileSys's recursive delete implementation
template <typename STRING>
class Deleter :
    public osal::TreeWalkerBase<STRING>::IEntryProcessor
{
public: // types
    typedef typename osal::PathTraits<STRING> Traits;
    typedef typename Traits::StringPointer StringPointer;
    typedef typename Traits::ConstStringPointer ConstStringPointer;
    typedef typename Traits::StringObj StringObj;
    typedef typename Traits::Character Character;
    typedef typename Traits::PathObj PathObj;
    typedef typename Traits::ApiObj ApiObj;

    typedef typename util::FileSysBase<STRING>::IRemoveHandler
        IRemoveHandler;
    typedef typename IRemoveHandler::RemoveReturn RemoveReturn;
    typedef typename IRemoveHandler::RemoveStatus RemoveStatus;

    typedef typename osal::TreeWalkerBase<STRING> TreeWalker;

    typedef typename TreeWalker::WalkReturn WalkReturn;

    typedef typename TreeWalker::IEntryProcessor IEntryProcessor;

    typedef typename IEntryProcessor::WalkStatus WalkStatus;
public:
    Deleter(ConstStringPointer p, IRemoveHandler *rh) IPL_NOEXCEPT :
        m_p(p), m_rh(rh)
    { }

    RemoveReturn getResult() const IPL_NOEXCEPT
    { return m_rr; }

    virtual WalkReturn processEntry(
        ConstStringPointer relpath,
        const osal::FileInfo &info,
        const WalkStatus &ws) IPL_NOEXCEPT;

    virtual WalkReturn processError(
        ConstStringPointer relpath,
        const osal::FileInfo &info,
        const WalkStatus &ws) IPL_NOEXCEPT;

private:
    ConstStringPointer m_p;
    IRemoveHandler *m_rh;
    RemoveReturn m_rr;
};

template <typename STRING>
typename Deleter<STRING>::WalkReturn
Deleter<STRING>::processEntry(
    ConstStringPointer relpath,
    const osal::FileInfo &info,
    const WalkStatus &ws) IPL_NOEXCEPT
{
    bool have_error = false;
    RemoveStatus rs(ws);

    m_rr.reset();

    if( m_rh )
    {
        IPLBASE_ABORT_ON_EXCEPTION(
            m_rr = m_rh->checkRemove(relpath, info, rs);
        )
    }

    if( m_rr.walkError() )
        return m_rr;
    else if( m_rr.skipDelete() )
    {
        m_rr.reset();
        // don't do anything else in this case
        return m_rr;
    }

    if( ws.isDir() && (ws.dirFinished() ) )
    {
        have_error = osal::FileSys::removeDir(
            static_cast<ApiObj>(static_cast<StringObj>(relpath))
            );
    }
    else if( !ws.isDir() )
    {
        have_error = osal::FileSys::removeFile(
            static_cast<ApiObj>(static_cast<StringObj>(relpath))
            );
    }

    if( have_error )                           // BRANCH_COVERAGE_UNTESTABLE
    {
        if( ipl_error.isA( osal::SysError ) )  // BRANCH_COVERAGE_UNTESTABLE
        {
            switch( ipl_error.id() )           // BRANCH_COVERAGE_UNTESTABLE
            {
            case osal::OBJECT_BUSY:
                rs.setObjectBusy();
                break;
            case osal::PERMISSION_DENIED:
                rs.setRmNoPerm();
                break;
            case osal::DIR_NOT_EMPTY:
                rs.setDirNotEmpty();
                break;
            default:
                rs.setOtherRmError();
                break;
            }
        }
        else
        {
            rs.setOtherRmError();
        }

        if( m_rh )                             // BRANCH_COVERAGE_UNTESTABLE
        {
            IPLBASE_ABORT_ON_EXCEPTION(
                m_rr = m_rh->removeError(
                    relpath, info, rs );
            )
            ipl_error.ack();
        }
        else
        {
            // keep error active in this case such that
            // client can check the error
            m_rr.setError();
        }
    }

    return m_rr;
}

template <typename STRING>
typename Deleter<STRING>::WalkReturn
Deleter<STRING>::processError(
    ConstStringPointer relpath,
    const osal::FileInfo &info,
    const WalkStatus &ws) IPL_NOEXCEPT
{
    if( ws.dirNoAccess() || ws.noInfoAvail() ) // BRANCH_COVERAGE_UNTESTABLE
    {
        // if no callback was specified then we simply have to
        // fail the operation
        if( ! m_rh )
        {
            ipl_raise( osal::SysError,
                osal::PERMISSION_DENIED,
                relpath );

            m_rr = WalkReturn().setError();
        }
        else
        {
            IPLBASE_ABORT_ON_EXCEPTION(
                // no remove specific return code information is
                // processed here. Either the client aborts
                // execution or continues.  This is evaluated by
                // TreeWalker.
                m_rr = m_rh->removeError(relpath, info, ws);
            )
        }
    }
    else
    {
        IPL_ABORT("Unknown error in removeRecursive()");
    }

    return m_rr;
}

} // end namespace
