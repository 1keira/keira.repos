#ifndef PERFDAT_CPULOAD_HXX_
#define PERFDAT_CPULOAD_HXX_

/*
    Copyright esolutions GmbH
    All rights reserved
 	Authors:
		Stefan Bittner
*/

#include <common/types/utility.hxx>
#include <common/types/map.hxx>
#include <common/types/vector.hxx>
#include <osal/StopWatch.hxx>
#include <osal/ProcessTNG.hxx>

namespace perfdat {
/* we measure cpu load by the relation between cpu time and wall time
 * Values should be taken at various points in time with getTimes()
 * after start() has been called.
 * geTimes returns elapsed wall time and cpu time for the period since
 * the last getTimes call or since start for the first getTimes call.
*/
class CpuLoad {
	public:
		CpuLoad(const ipl::map<osal::ProcessId, ipl::string>& others);
		~CpuLoad();
		// start both clocks
		void start();
		// stop both clocks, reset values
		void stop();
		// store wall time and cpu time per watched process in microseconds.
		// since start (for the first store call) or the last store call (for all
		// others)
		void store();
		// return the stored times, at index 0 wall time, at index 1 own process time
		// beyond that: times for processes passed in others
		const ipl::vector<osal::TimeT> getTimes() const { return m_times; }
		// return labels associated with times
		size_t size() const { return m_size; }
		size_t othersSize() const { return m_other_proc_watches.size(); }
	private:
		osal::RealtimeStopWatch		m_rt_watch;
		osal::ProcessTimeStopWatch	m_proc_watch;
		size_t						m_size; // wall time , self cpu time, others cpu time
		ipl::vector<osal::ProcessTimeStopWatch*> m_other_proc_watches;
		ipl::vector<osal::TimeT>	m_times;

		void stopOthers();
		void startOthers();
		void resetOthers();
};
}

#endif // #define PERFDAT_CPULOAD_HXX_
