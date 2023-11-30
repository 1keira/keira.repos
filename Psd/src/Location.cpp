/*********************************************************************************
 * Copyright (c) 202x Cariad China. All rights reserved.
 * FileName:	 PsdMap.h
 * Author: 	     ZhaoZijia
 * Version :	 Ver0.1
 * Date:		 2023-11-30
 * Description: start thread, init Psd data
 *
 *********************************************************************************/
/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include "../inc/Location.h"
#include "../inc/PsdLocation.h"

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: static statement
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * LOCAL AND GLOBAL VARIABLES
 *---------------------------------------------------------------------------*/
extern pthread_t decoderThread;   
extern pthread_t mapThread; 

/*-----------------------------------------------------------------------------
 * FUNCTION DEFINITIONS: static definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
Location::Location()
{
}

Location::~Location()
{
}

void Location::start()
{
    PsdLocation::getInstance()->initPsdData();
    PsdLocation::getInstance()->createDecoderThread();
    PsdLocation::getInstance()->createMapThread();

    pthread_join(decoderThread, NULL);
    pthread_join(mapThread, NULL);
}