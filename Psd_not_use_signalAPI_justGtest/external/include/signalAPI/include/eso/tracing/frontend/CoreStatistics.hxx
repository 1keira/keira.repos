/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef TRACING_CORESTATISTICS_HXX
#define TRACING_CORESTATISTICS_HXX

namespace tracing
{

//! \brief Flags to be used for Frontend::registerStatisticsKey()
struct CoreStatistics
{
    //! No special handling of statistics value.
    static const uint8_t FLAG_NONE = 0;
    //! DEPRECATED! Currently not supported. \deprecated
    static const uint8_t FLAG_AVERAGE = 1;
    //! Store the sum of all submitted values.
    static const uint8_t FLAG_INCREMENT = 2;
    //! Reset the stored value when a statistic trace is generated.
    static const uint8_t FLAG_RESET = 4;
    //! Store the maximum value submitted.
    static const uint8_t FLAG_MAX = 8;
};

} // end of namespace tracing

#endif /* TRACING_CORESTATISTICS_HXX */

