#ifndef PERFDAT_HXX
#define PERFDAT_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
		Stefan Bittner
*/

#include <common/types/vector.hxx>
#include <common/types/string.hxx>
#include <common/streams/iostream.hxx>
#include <common/streams/fstream.hxx>

// performance data measurements 
namespace perfdat {

	/* Description of a single value */
	struct ValueDescription {
		ValueDescription(const ipl::string& name, const ipl::string& text, const ipl::string& unit)
		: name (name)
		, text(text)
		, unit(unit)
		{
		}

		ipl::string	name;	// value name
		ipl::string	text;	// textual description
		ipl::string unit;	// unit of measurement
	};

	typedef ipl::vector<ValueDescription> ValueDescriptions;

	class JsonWriter;

	// interface for some sort of data that can be written
	class Data {
		public:
			Data() {}
			virtual ~Data() {}
			// write yourself
			virtual void write(JsonWriter& w, const ValueDescriptions& d) const = 0;
	};
}
#endif // PERFDAT_HXX

