/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_IDENTITY_HXX
#define COMM_IDENTITY_HXX

#include <comm/comm_dso.h>
#include <comm/commtypes.hxx>

#include <string>

namespace comm {

    /*! Instance id, Version hash (interface key) and name */
    struct IdentityArgs {
        static const std::string UNKNOWN_SERVICE;

        IdentityArgs(const InstanceID& iid, const InterfaceKey& ikey, const std::string& iname
                    , bool discoverable=true)
        : m_iid{iid}
        , m_ikey{ikey}
        , m_iname{iname}
        , m_discoverable{discoverable}
        {}

        explicit IdentityArgs(const InstanceID& iid)
        : m_iid(iid)
        , m_ikey(InterfaceKey::null())
        , m_iname(UNKNOWN_SERVICE)
        {}

        const InstanceID&       m_iid;                  // instance id
        const InterfaceKey&     m_ikey;                 // interface key
        const std::string&      m_iname;                // interface name
        bool                    m_discoverable{true};   // discoverable service

        bool isDiscoverable() const { return m_discoverable; }
    };


    struct Identity {
        Identity() = default;

        explicit Identity(const IdentityArgs& ia)
        : m_iid{ia.m_iid}
        , m_ikey{ia.m_ikey}
        , m_iname{ia.m_iname}
        , m_discoverable{ia.m_discoverable}
        {}

        const char* getInterfaceName() const        { return m_iname.empty() ? nullptr : m_iname.c_str(); }
        const InterfaceKey& getInterfaceKey() const { return m_ikey; }
        const InstanceID& getInstanceID() const     { return m_iid; }

        void setIKey(const InterfaceKey& ikey)      { m_ikey=ikey; }
        void setInterfaceName(const char* name)     { if (name) m_iname=name; else m_iname.clear();}
        InstanceID& getInstanceID(bool)             { return m_iid; }
        bool isDiscoverable() const                 { return m_discoverable; }


        InstanceID          m_iid;
        InterfaceKey        m_ikey;
        std::string         m_iname;
        bool                m_discoverable{true};   // default is discoverable
    };
}

#endif // COMM_IDENTITY_HXX
// vim: ts=4 sw=4:

