/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_JOURNAL_HXX
#define TRACING_JOURNAL_HXX

#include <osal/Mutex.hxx>
#include <osal/StreamFmtFileW.hxx>
#include <tracing/tracing_dso.h>

namespace osal
{
class CalendarTime;
}

namespace tracing
{

/*!
 *    \brief
 *        Class used to write system events to a journal file.
 *
 *        It is typically used to log events when writing to ring buffer.
 */
class TRACINGIMPL_EXPORT Journal
{
public:
    /*!
     *    \brief
     *        Constructor.
     *
     *    \param
     *        file_name The journal file name with path.
     */
    explicit Journal(const std::string & file_name);

    //! \brief Indication if the journal file is valid.
    bool isValid() const
    {
        return m_valid;
    }

    /*!
     *    \brief
     *        Log a generic error event to journal.
     *
     *    \param
     *        reason The error info.
     */
    void error(const std::string & reason);

    /*!
     *    \brief
     *        Log the event that logging to file has started.
     *
     *    \param
     *        start The calender date and time info.
     *    \param
     *        path The directory path.
     */
    void logStart(const osal::CalendarTime & start, const std::string & path);

    /*!
     *    \brief
     *        Log the event that logging to file has stopped.
     *
     *    \param
     *        end The calender date and time info.
     *    \param
     *        reason The reason.
     */
    void logEnd(const osal::CalendarTime & end, const std::string & reason);

    /*!
     *    \brief
     *        Log the event that the used file got renamed.
     *
     *    \param
     *        old_name The old file name.
     *    \param
     *        new_name The new file name.
     */
    void logRename(const std::string & old_name, const std::string & new_name);

    /*!
     *    \brief
     *        Log a cycle event indicating that a ring buffer starts to overwrite
     *        data.
     *
     *    \param
     *        now The calender date and time info.
     */
    void logCycle(const osal::CalendarTime & now);

    /*!
     *    \brief
     *        Log screenshot info to journal.
     *
     *    \param
     *        now The calender date and time info.
     *    \param
     *        msg The screenshot message string. When tokenized via ':' separator
     *        into 3 parts they reflect 'path', 'display id' and 'status'.
     *    \param
     *        log_file The file name where a screenshot was written to.
     */
    void logScreenshot(const osal::CalendarTime & now, const std::string &msg,
                       const std::string &log_file);

    /*!
     *    \brief
     *        Log a generic message string to journal.
     *
     *    \param
     *        msg The message string.
     */
    void logGeneric(const std::string & msg);

protected:
    bool m_valid;
    osal::StreamFmtFileW m_file;
    osal::Mutex m_mutex;

    /*!
     *    \brief
     *        Format a calender date time info into format 'yyyymmdd_hh-mm-ss'.
     *
     *    \param
     *        ct The calender date and time info.
     *    \return
     *        The formatted string.
     */
    std::string getStringFromDate(const osal::CalendarTime & ct) const;

    //! \brief Log that a new journal is being written.
    void printHeader();

    //! \brief Log the info which is read from a version info file.
    void printVersionInfo();

    //! \brief Log the info if a 'savedpreset.json' file exists at certain location.
    void checkPreset();
};

} // end of namespace tracing

#endif /* TRACING_JOURNAL_HXX */

