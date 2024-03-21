#ifndef PERFDAT_TIME_HXX
#define PERFDAT_TIME_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
		Stefan Bittner
*/

#include <common/stdint.h>
#include <perfdat/Time_bits.hxx>

namespace perfdat {

	// distance between time stamps
	struct Duration {
		Duration() : diff(0) {}
		Duration(int64_t d) : diff(d) {}
		int64_t to_ms() const;
		int64_t to_us() const;
		int64_t to_ns() const;
		int64_t diff;
	};

	// point in time in som einternal representation
	struct Timestamp {
		// zero initialized timstamp
		Timestamp() {}
		void get();

		Duration operator - (const Timestamp &other) const {
			return Duration(ts - other.ts);
		}

		Timestamp_value	ts;
	};
}
#endif // PERFDAT_TIME_HXX

