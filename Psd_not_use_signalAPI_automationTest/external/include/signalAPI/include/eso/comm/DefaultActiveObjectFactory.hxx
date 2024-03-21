/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/


#ifndef COMM_DEFAULT_ACTIVE_OBJ_FACTORY_HXX
#define COMM_DEFAULT_ACTIVE_OBJ_FACTORY_HXX

#include <common/types/map.hxx>
#include <osal/sched.hxx>
#include <util/SharedPtr.hxx>
#include <comm/commtypes.hxx>
#include <comm/IActiveObjectFactory.hxx>

#include <comm/comm_dso.h>

namespace comm {
    class Core;

    /**
        \brief  The factory for Active Objects used by comm if no other active object factory is
                  assigned.

                This factory creates an active object per interface id - the handle part in the
                InstanceID is not evaluated. Thus all service instances with the same ccomm interface are
                served from the same ActiveObject instance.
     **/
    class COMM_EXPORT DefaultActiveObjectFactory : public IActiveObjectFactory {
        public:
            DefaultActiveObjectFactory();
            ~DefaultActiveObjectFactory() override;

            util::SharedPtr<ActiveObject> getActiveObject(const InstanceID&) override;
            util::SharedPtr<ActiveObject> hasActiveObject(const InstanceID&) override;
            util::SharedPtr<ActiveObject> getActiveObject(const ServiceRegistration&) override;

        private:
            // not copy-assignable
            DefaultActiveObjectFactory(const DefaultActiveObjectFactory&);
            DefaultActiveObjectFactory& operator=(const DefaultActiveObjectFactory&);
            void stop() override;
            typedef ipl::map<InterfaceID,util::SharedPtr<ActiveObject>, InterfaceIDSort> AOMap;
            AOMap   m_aoMap;

            // true on error
            bool mapNameToSchedAttr(const ServiceRegistration& reg, osal::sched::Attr& attr);

            friend class Core;
    };

} // namespace comm

#endif // COMM_DEFAULT_ACTIVE_OBJ_FACTORY_HXX

