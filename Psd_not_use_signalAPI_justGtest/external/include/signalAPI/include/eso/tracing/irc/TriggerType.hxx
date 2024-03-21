/*
   Copyright 2023 e.solutions GmbH
   All rights reserved
*/

#ifndef TRACING_IRCBACKEND_TRIGGERTYPE_HXX
#define TRACING_IRCBACKEND_TRIGGERTYPE_HXX

namespace tracing
{

enum class TriggerType
{
    TRIGGER_NONE,
    TRIGGER_SYNC,
    TRIGGER_EXPORT,
    TRIGGER_FILE_EXPORT,
    TRIGGER_BACKUP,
    TRIGGER_DELETE_DATA,
    TRIGGER_DELETE_DATA_COMPLETE,
    TRIGGER_SYNC_TIMED,
    TRIGGER_STATISTIC_DUMP,
    TRIGGER_STATISTIC_OUTPUT
};

} // end of namespace tracing

#endif
