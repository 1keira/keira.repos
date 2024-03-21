#ifndef PERFDAT_PROCESSARG_HXX_
#define PERFDAT_PROCESSARG_HXX_

/*
    Copyright esolutions GmbH
    All rights reserved
 	Authors:
		Stefan Bittner
*/


#include <common/types/map.hxx>
#include <common/types/vector.hxx>
#include <common/types/string.hxx>
#include <osal/ProcessTNG.hxx>

namespace perfdat {

	/* Helper to create a map of process id to name
	 * from arguments that ar either
	 * process name,
	 * proces name:label
	 * process id
	 */
	class ProcessArg {
		public:
			typedef ipl::map<osal::ProcessId, ipl::string> Map;
			ProcessArg(const ipl::vector< ipl::string >& args);
			const Map& getMap() const { return m_map; } 
		private:
			// string to int, returns true if can't be converted, false otherwise
			bool toInt (const ipl::string& thing, unsigned long& value );

			// convert to map from input
			void argsToMap( const ipl::vector< ipl::string >& in);

			Map m_map;
	};
}

#endif // PERFDAT_PROCESSARG_HXX_
