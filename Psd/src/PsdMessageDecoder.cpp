/*********************************************************************************
 * Copyright (c) 202x Cariad China. All rights reserved.
 * FileName:	 PsdMessageDecoder.cpp
 * Author: 	     ZhaoZijia
 * Version :	 Ver0.1
 * Date:		 2023-11-03
 * Description: Psd raw data to be got and calculated.
 *
 *********************************************************************************/
/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <cmath>
#include "../inc/PsdMessageDecoder.h"

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/
#define BRANCH_ANGLE_SCALE 1.417323

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: static statement
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * LOCAL AND GLOBAL VARIABLES
 *---------------------------------------------------------------------------*/
//temporarily use buff storage 
PsdMessageDecoder *PsdMessageDecoder::pInstance = NULL;
pthread_mutex_t decoderThreadMutex = PTHREAD_MUTEX_INITIALIZER;
    
/*-----------------------------------------------------------------------------
 * FUNCTION DEFINITIONS: static definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
PsdMessageDecoder *PsdMessageDecoder::getInstance()
{
    if (NULL == pInstance)
    {
        pInstance = new PsdMessageDecoder();
    }
    return pInstance;
}

PsdMessageDecoder::PsdMessageDecoder(/* args */)
{
}

PsdMessageDecoder::~PsdMessageDecoder()
{
}

std::vector<struct PsdMapData *>& PsdMessageDecoder::getVPsdMap()
{
    return vPsdMap;
}

void PsdMessageDecoder::setPsdMapData(tPsdMapData psdMapData)
{
    memcpy(&PsdMapData, &psdMapData, sizeof(tPsdMapData));
}

void PsdMessageDecoder::setSelfSegment(tSelfSegment CurSegment)
{
    memcpy(&hvSegment, &CurSegment, sizeof(tSelfSegment));
}

tSelfSegment PsdMessageDecoder::getSelfSegment()
{
    return hvSegment;
}

void PsdMessageDecoder::saveAttributToList()
{
    printf("[%s] [%d]: PsdAttribut_1_ID = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut1ID);
    printf("[%s] [%d]: PsdAttribut_1_Wert = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut1Wert);
    printf("[%s] [%d]: PsdAttribut_2_ID = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut2ID);
    printf("[%s] [%d]: PsdAttribut_2_Wert = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut2Wert);
    printf("[%s] [%d]: PsdAttribut_3_ID = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut3ID);
    printf("[%s] [%d]: PsdAttribut_3_Wert = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut3Wert);
    printf("[%s] [%d]: PsdAttribut_4_ID = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut4ID);
    printf("[%s] [%d]: PsdAttribut_4_Wert = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut4Wert);
    printf("[%s] [%d]: PsdAttribut_5_ID = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut5ID);
    printf("[%s] [%d]: PsdAttribut_5_Wert = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttribut5Wert);

    if (PsdMapData.psdAttribut1ID == 4)
    {
        PsdMapData.structSeparate = static_cast<e_StructSeparate>(PsdMapData.psdAttribut1Wert);
    }
    else
    if (PsdMapData.psdAttribut2ID == 4)
    {
        PsdMapData.structSeparate = static_cast<e_StructSeparate>(PsdMapData.psdAttribut2Wert);
    }
    else
    if (PsdMapData.psdAttribut3ID == 4)
    {
        PsdMapData.structSeparate = static_cast<e_StructSeparate>(PsdMapData.psdAttribut3Wert);
    }
    else
    if (PsdMapData.psdAttribut4ID == 4)
    {
        PsdMapData.structSeparate = static_cast<e_StructSeparate>(PsdMapData.psdAttribut4Wert);
    }
    else
    if (PsdMapData.psdAttribut5ID == 4)
    {
        PsdMapData.structSeparate = static_cast<e_StructSeparate>(PsdMapData.psdAttribut5Wert);
    }

    printf("[%s] [%d]: psdAttributSegmentID = %u\n", __FUNCTION__, __LINE__, PsdMapData.psdAttributSegmentID);
    printf("[%s] [%d]: structSeparate = %u\n", __FUNCTION__, __LINE__, PsdMapData.structSeparate);
    pthread_mutex_lock(&decoderThreadMutex);
    for (auto it = vPsdMap.begin(); it != vPsdMap.end(); it++)
    {
        if ((*it)->preSegmentId == PsdMapData.psdAttributSegmentID)
        {
            (*it)->structSeparate = PsdMapData.structSeparate;
        }
    }
    pthread_mutex_unlock(&decoderThreadMutex);
}

void PsdMessageDecoder::clearList()
{
    if (vPsdMap.empty())
    {
        printf("[%s] [%d]: vPsdMap is already empty\n", __FUNCTION__, __LINE__);
        return ;
    }
    else
    {
        //for gtest: The pointer is not new, the address of the variable stored directly in the unit test
        // for (auto it = vPsdMap.begin(); it != vPsdMap.end(); it++)
        // {
        //     delete *it;
        // }
        vPsdMap.clear(); //empty the container
        printf("[%s] [%d]: clear the vPsdMap\n", __FUNCTION__, __LINE__);
    }
}

void PsdMessageDecoder::popUpList(std::vector<struct PsdMapData *>::iterator position)
{
    printf("[%s] [%d]: delete list's element\n", __FUNCTION__, __LINE__);
    //TODO: delete pPsdMapData and erase(pos)
    //for gtest: The pointer is not new, the address of the variable stored directly in the unit test
    //delete (*position);
    vPsdMap.erase(position); //container will move on
}

void PsdMessageDecoder::pushInList()
{
    //TODO1: judge (segmentIsComplete == false) || (vPsdMap already have this preSegmentId)
    for (auto it = vPsdMap.begin(); it != vPsdMap.end(); it++)
    {
        if ((*it)->preSegmentId == PsdMapData.preSegmentId)
        {
            printf("[%s] [%d]: vPsdMap already have this preSegmentId\n", __FUNCTION__, __LINE__);
            return ;
        }
    }

    if (false == PsdMapData.segmentIsComplete)
    {
        printf("[%s] [%d]: segment is not complete\n", __FUNCTION__, __LINE__);
        return ;
    }
    else
    {   
        //TODO2: vPsdMap don't have this preSegmentId, first pushInList
        tPsdMapData *pPsdMapData = new(tPsdMapData);
        //for gtest
        // if (NULL == pPsdMapData)
        // {
        //     printf("[%s] [%d]: new failed\n", __FUNCTION__, __LINE__);
        // }
        // else
        // {
            //TODO3: fill pPsdMapData and then emplace_back to vPsdMap
            *pPsdMapData = PsdMapData;
            vPsdMap.emplace_back(pPsdMapData);
        // }
    }
}

void PsdMessageDecoder::convertBranchAngle()
{
    PsdMapData.branchAngle = (PsdMapData.branchAngle * BRANCH_ANGLE_SCALE) * (PsdMapData.branchDirection ? -1 : 1);
    printf("[%s] [%d]: branchDirection = %u\n", __FUNCTION__, __LINE__, PsdMapData.branchDirection);
    printf("[%s] [%d]: branchAngle = %lf\n", __FUNCTION__, __LINE__, PsdMapData.branchAngle);
}

void PsdMessageDecoder::convertCurvature()
{
    //TODO1: convert endCurvature
	PsdMapData.endCurvature = (1.0f / (1 + 0.155 * pow(PsdMapData.endCurvature, 2))) * (PsdMapData.signEndCurvature ? -1 : 1);
    printf("[%s] [%d]: signEndCurvature = %u\n", __FUNCTION__, __LINE__, PsdMapData.signEndCurvature);
	printf("[%s] [%d]: endCurvature: %lf\n", __FUNCTION__, __LINE__, PsdMapData.endCurvature);

    //TODO2: convert startCurvature
    PsdMapData.startCurvature = (1.0f / (1 + 0.155 * pow(PsdMapData.startCurvature, 2))) * (PsdMapData.signStartCurvature ? -1 : 1);
    printf("[%s] [%d]: signStartCurvature = %u\n", __FUNCTION__, __LINE__, PsdMapData.signStartCurvature);
	printf("[%s] [%d]: startCurvature: %lf\n", __FUNCTION__, __LINE__, PsdMapData.startCurvature);
}

void PsdMessageDecoder::calcPsd04Data()
{
    //TODO: calculate endCurvature,startCurvature, branchAngle
    convertCurvature();
    convertBranchAngle();
}

void PsdMessageDecoder::segmentManager(bool PsdUsageActive)
{
    if (PsdUsageActive)
    {
        pthread_mutex_lock(&decoderThreadMutex);
        pushInList();
        pthread_mutex_unlock(&decoderThreadMutex);
    }
    else
    {
        pthread_mutex_lock(&decoderThreadMutex);
        clearList();
        pthread_mutex_unlock(&decoderThreadMutex);
    }
}

