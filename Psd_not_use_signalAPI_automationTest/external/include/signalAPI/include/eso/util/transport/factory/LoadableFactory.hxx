/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_TRANSPORT_LOADABLE_FACTORY_HXX
#define UTIL_TRANSPORT_LOADABLE_FACTORY_HXX

#include <ipl_config.h>

#include <util/util_dso.h>
#include <util/transport/factory/IFactory.hxx>
#include <common/types/string.hxx>

namespace util {
namespace transport {

class ISpawnFactory;

typedef const char*				(*FactoryNameFct)();
typedef const char*         	(*FactoryTypeFct)();
typedef IFactory*				(*FactoryCreateFct)(const ipl::string& cfg);
typedef void					(*FactoryDestroyFct)(IFactory*);
typedef ISpawnFactory*			(*SpawnFactoryCreateFct)(const ipl::string& cfg);
typedef void					(*SpawnFactoryDestroyFct)(ISpawnFactory*);

//! Struct with create/destroy functions for simple factories
struct LoadableSimpleAllocator {
    FactoryCreateFct		create;				// create factory
    FactoryDestroyFct		destroy;			// destroy factory
};

//! Struct with create/destroy functions for spawn factories
struct LoadableSpawnAllocator {
    SpawnFactoryCreateFct	create;				// create factory
    SpawnFactoryDestroyFct	destroy;			// destroy factory
};

//! Struct with create/destroy/query functions for simple factories
struct LoadableFactory {
    FactoryNameFct 			name;				// query factory name
    FactoryTypeFct			type;				// query factory type
    LoadableSimpleAllocator	simple;				// create/destroy simple factor
    LoadableSpawnAllocator	spawn;				// create/destroy spawn factory
};
//! The name of the exported LoadableFactoryFct function
extern UTIL_EXPORT const char* LoadableFactoryFctName;

extern UTIL_EXPORT const char* DEFAULT_LOADABLE_SUFFIX;

//! create path to shared object from config string
ipl::string makeLoadableFactoryPath(const ipl::string& config) IPL_NOEXCEPT;

}
}

extern "C" {
/**
 *	\brief
 *		Typedef for a function returning a struct LoadableFactory
 *
 *		Loadable factories can export a function with this signature.
 **/
typedef util::transport::LoadableFactory* (*LoadableFactoryFct)();

}
#endif /* UTIL_TRANSPORT_LOADABLE_FACTORY_HXX */

