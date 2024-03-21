/*
    Copyright 2022 e.solutions GmbH
    All rights reserved
*/
#ifndef TRACING_CORE_CLOCK_SUSPENDMONITOR_HXX
#define TRACING_CORE_CLOCK_SUSPENDMONITOR_HXX

#include <osal/Mutex.hxx>
#include <tracing/tracing_dso.h>

namespace tracing
{

/*!
 *  \brief
 *      This class monitors subsequent timestamp offsets, removes jitter according
 *      the configured threshold and maintains the filtered offset.
 */
class TRACINGIMPL_EXPORT SuspendMonitor
{
public:
    //! \brief Default constructor.
    SuspendMonitor();

    /*!
     *  \brief
     *      Initializes the threshold for offset filtering.
     *  \param
     *      thres_ms The threshold in [ms].
     *  \param
     *      update_statistics Flag to indicate if core statistics shall be reported.
     */
    void init(uint32_t thres_ms, bool update_statistics=false);

    /*!
     *  \brief
     *      Get the filtered suspend time offset.
     *  \param
     *      offset The actual measured suspend time offset [in].
     *             It is updated with the filtered maximum [out]
     */
    void getFilteredOffset(int64_t & offset);

protected:
    //! Threshold in ns for detection of clock suspend intervals
    int64_t m_thres_ns;
    //! Filtered duration in ns where system was suspended
    int64_t m_offset;
    //! Flag to indicate if statistics reporting is enabled
    bool m_update_statistics;
    //! Synchronization mutex
    osal::Mutex m_mutex;
};

} // end of namespace tracing

#endif /* TRACING_CORE_CLOCK_SUSPENDMONITOR_HXX */
