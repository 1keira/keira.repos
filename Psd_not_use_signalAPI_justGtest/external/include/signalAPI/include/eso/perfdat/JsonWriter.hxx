#ifndef PERFDAT_JSON_WRITER_HXX
#define PERFDAT_JSON_WRITER_HXX

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
		Stefan Bittner
*/

#include <common/types/string.hxx>
#include <perfdat/perfdat.hxx>

namespace perfdat {

	class JsonWriter {
		public:
			JsonWriter(ipl::ostream& stream
						,const ValueDescriptions& descriptions
						);
			JsonWriter(const ipl::string& path
						,const ValueDescriptions& descriptions
						);
			~JsonWriter();
			// did the construction have errors?
			bool hasError() const;
			void finalize();
			bool writeSample(const Data& sample);
			bool writeConstants(const Data& constants);
			// TODO: write other types
			bool writeUnsigned(unsigned long long v, const ValueDescription& d);
			bool writeInt(long long int v, const ValueDescription& d);
			bool writeString(const char* v, const ValueDescription& d);
			bool writeString(const ipl::string& v, const ValueDescription& d);
			bool writeBool(bool v, const ValueDescription& d);
			bool writeFloat(double v, const ValueDescription& d);
		private:
			ipl::ofstream					m_file;
			ipl::ostream&					m_stream;
			bool							m_error;
			const ValueDescriptions&		m_descr;
			bool							m_first_sample;
			bool							m_first_value;
			bool							m_close_samples;
			bool writeDescriptions();
			bool handleFirstValue();
	};
}

#endif // PERFDAT_JSON_WRITER_HXX

