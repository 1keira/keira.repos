/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
        
#ifndef TRACING_ICLIENTHELPER_HXX
#define TRACING_ICLIENTHELPER_HXX

#include <ipl_config.h>
#include <common/types/string.hxx>
#include <common/stdint.h>
#include <common/iplcommon_dso.h>

namespace tracing
{

class IClient;

/*!
 *  \brief
 *      Interface class for a client helper.
 *
 *      It allows easy access to a tracing client.
 */
class IPLCOMMON_EXPORT IClientHelper
{
public:
    virtual ~IClientHelper() IPL_NOEXCEPT = 0;
    //! brief Initialize the tracing system.
    virtual bool init(const ipl::string & name,
                      const ipl::string & type = "client",
                      bool readConfig = true) IPL_NOEXCEPT = 0;

    //! brief Leave the tracing system.
    virtual void exit() IPL_NOEXCEPT = 0;
    //! brief Provides the client instance.
    virtual IClient * getClient() IPL_NOEXCEPT = 0;

    //! brief Set the client helper instance.
    static void setClientHelper(IClientHelper * helper) IPL_NOEXCEPT;
    //! brief Reset the client helper instance.
    static void resetClientHelper() IPL_NOEXCEPT;
};

inline IClientHelper::~IClientHelper() IPL_NOEXCEPT {}

} // end of namespace tracing

#endif /* TRACING_ICLIENTHELPER_HXX */

