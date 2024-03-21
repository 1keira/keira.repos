/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Serializer_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_SERIALIZER_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_SERIALIZER_HXX

#include <comm/comm_dso.h>
// serializer for types from other IDL files
// own types
#include <asi/connectivity/al/messaging/StructMapAccount.hxx>
#include <asi/connectivity/al/messaging/StructOnAccountsEvent.hxx>
#include <asi/connectivity/al/messaging/StructMapHeaderEntry.hxx>
#include <asi/connectivity/al/messaging/StructMapEnvelopeVcard.hxx>
#include <asi/connectivity/al/messaging/StructMapAttachments.hxx>
#include <asi/connectivity/al/messaging/StructSimInfo.hxx>
#include <comm/commidltypes.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>
#include <util/serializer/IStructuredSerializer.hxx>

namespace util
{
    namespace serializer
    {

    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::messaging::MapAccount& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::messaging::MapAccount &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::messaging::OnAccountsEvent& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::messaging::OnAccountsEvent &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::messaging::MapHeaderEntry& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::messaging::MapHeaderEntry &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::messaging::MapEnvelopeVcard& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::messaging::MapEnvelopeVcard &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::messaging::MapAttachments& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::messaging::MapAttachments &val);
    PROXY_EXPORT bool serialize (IStructuredSerializer &stream, asi::connectivity::al::messaging::SimInfo& val);
    PROXY_EXPORT bool deserialize (IStructuredPullDeserializer &stream, asi::connectivity::al::messaging::SimInfo &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_CONNECTIVITY_AL_MESSAGING_DEFINITIONS_HXX
