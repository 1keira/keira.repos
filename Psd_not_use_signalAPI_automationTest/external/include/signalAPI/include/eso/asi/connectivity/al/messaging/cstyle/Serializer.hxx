/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template CStyleSerializer_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_MESSAGING_SERIALIZER_CSTYLE_HXX
#define ASI_CONNECTIVITY_AL_MESSAGING_SERIALIZER_CSTYLE_HXX

#include <comm/comm_dso.h>
#include <comm/commidltypes.hxx>
#include <common/types/vector.hxx>
#include <asi/connectivity/al/messaging/cstyle/StructMapAccount.hxx>
#include <asi/connectivity/al/messaging/cstyle/StructOnAccountsEvent.hxx>
#include <asi/connectivity/al/messaging/cstyle/StructMapHeaderEntry.hxx>
#include <asi/connectivity/al/messaging/cstyle/StructMapEnvelopeVcard.hxx>
#include <asi/connectivity/al/messaging/cstyle/StructMapAttachments.hxx>
#include <asi/connectivity/al/messaging/cstyle/StructSimInfo.hxx>
#include <util/serializer/IStructuredSerializer.hxx>
#include <util/serializer/IStructuredPullDeserializer.hxx>

namespace asi
{
namespace connectivity
{
namespace al
{
namespace messaging
{
namespace  cstyle
{
struct MapAccount;
struct OnAccountsEvent;
struct MapHeaderEntry;
struct MapEnvelopeVcard;
struct MapAttachments;
struct SimInfo;
} // cstyle
} // namespace asi
} // namespace connectivity
} // namespace al
} // namespace messaging

namespace util
{
    namespace serializer
    {

    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::MapAccount& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapAccount &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::OnAccountsEvent& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::OnAccountsEvent &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::MapHeaderEntry& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapHeaderEntry &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::MapEnvelopeVcard& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapEnvelopeVcard &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::MapAttachments& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::MapAttachments &val);
    // structured serializer interface
    bool serialize (IStructuredSerializer &s, const asi::connectivity::al::messaging::cstyle::SimInfo& val);
    bool deserialize (IStructuredPullDeserializer &s, asi::connectivity::al::messaging::cstyle::SimInfo &val);

    }  // end of namespace serializer
}  // end of namespace util

#endif// ASI_CONNECTIVITY_AL_MESSAGING_SERIALIZER_CSTYLE_HXX
