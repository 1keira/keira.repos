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
#include <thread>
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

#ifdef ENABLE_UDP_RECEIVER
extern void runUdpDataReceiver(std::shared_ptr<vwg::sid::PSDParser::ISignalDataListener> pListener);
#endif
    
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

PsdMessageDecoder *PsdMessageDecoder::testPsdMessageDecoder()
{
    new PsdMessageDecoder();
}

void PsdMessageDecoder::testPsdMessageDecoder(PsdMessageDecoder *pInstance)
{
    delete pInstance;
    pInstance = NULL;
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
    pthread_mutex_lock(&decoderThreadMutex);
    memcpy(&hvSegment, &CurSegment, sizeof(tSelfSegment));
    pthread_mutex_unlock(&decoderThreadMutex);
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
    for (auto it : vPsdMap)
    {
        if (it->preSegmentId == PsdMapData.psdAttributSegmentID)
        {
            it->structSeparate = PsdMapData.structSeparate;
            break;
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
        for (auto &it : vPsdMap)
        {
            delete it;
            it = NULL;
        }
        vPsdMap.clear(); //empty the container
        printf("[%s] [%d]: clear the vPsdMap\n", __FUNCTION__, __LINE__);
    }
}

void PsdMessageDecoder::popUpList(std::vector<struct PsdMapData *>::iterator position)
{
    printf("[%s] [%d]: delete list's element\n", __FUNCTION__, __LINE__);
    //TODO: delete pPsdMapData and erase(pos)
    delete (*position);
    (*position) = NULL;
    vPsdMap.erase(position); //container will move on
}

void PsdMessageDecoder::pushInList()
{
    //TODO1: judge (segmentIsComplete == false) || (vPsdMap already have this preSegmentId)
    for (auto it : vPsdMap)
    {
        if (it->preSegmentId == PsdMapData.preSegmentId)
        {
            printf("[%s] [%d]: vPsdMap already have this preSegmentId\n", __FUNCTION__, __LINE__);
            return ;
        }
    }

    //TODO2: vPsdMap don't have this preSegmentId, first pushInList
    if ((PsdMapData.preSegmentId != 0) && (PsdMapData.preSegmentId != 1))
    {
        printf("[%s] [%d]: preSegmentId = %u\n", __FUNCTION__, __LINE__, PsdMapData.preSegmentId);
        tPsdMapData *pPsdMapData = new(tPsdMapData);
        if (NULL == pPsdMapData)
        {
            printf("[%s] [%d]: new failed\n", __FUNCTION__, __LINE__);
        }
        else
        {
            //TODO3: fill pPsdMapData and then emplace_back to vPsdMap
            *pPsdMapData = PsdMapData;
            vPsdMap.emplace_back(pPsdMapData);
        }
    }
}

void PsdMessageDecoder::convertRoadClass(const uint32_t &RoadClassValue)
{
    printf("[%s] [%d]: RoadClassValue = %u\n", __FUNCTION__, __LINE__, RoadClassValue);
    if (RoadClassValue == 0)
    {
        PsdMapData.psd04RoadClass = PrivateRoad;
    }
    else if (RoadClassValue == 1)
    {
        PsdMapData.psd04RoadClass = LocalRoad;
    }
    else if (RoadClassValue == 2)
    {
        PsdMapData.psd04RoadClass = CountyRoad;
    }
    else if (RoadClassValue == 3)
    {
        PsdMapData.psd04RoadClass = NationalRoad;
    }
    else if (RoadClassValue == 4)
    {
        PsdMapData.psd04RoadClass = ProvincialRoad;
    }
    else if (RoadClassValue == 5)
    {
        PsdMapData.psd04RoadClass = Expressway;
    }
    else if (RoadClassValue == 7)
    {
        PsdMapData.psd04RoadClass = Init;
    }
}

void PsdMessageDecoder::convertBranchAngle(const uint32_t &branchAngleValue)
{
    PsdMapData.branchAngle = (branchAngleValue * BRANCH_ANGLE_SCALE) * (PsdMapData.branchDirection ? -1 : 1);
    printf("[%s] [%d]: branchDirection = %u, branchAngle = %lf\n", __FUNCTION__, __LINE__, PsdMapData.branchDirection, PsdMapData.branchAngle);
}

void PsdMessageDecoder::convertCurvature(const uint32_t &endCurvatureValue, const uint32_t &startCurvatureValue)
{
    //TODO1: convert endCurvature
	PsdMapData.endCurvature = (1.0f / (1 + 0.155 * pow(endCurvatureValue, 2))) * (PsdMapData.signEndCurvature ? -1 : 1);
    printf("[%s] [%d]: signEndCurvature = %u, endCurvature = %lf\n", __FUNCTION__, __LINE__, PsdMapData.signEndCurvature, PsdMapData.endCurvature);

    //TODO2: convert startCurvature
    PsdMapData.startCurvature = (1.0f / (1 + 0.155 * pow(startCurvatureValue, 2))) * (PsdMapData.signStartCurvature ? -1 : 1);
    printf("[%s] [%d]: signStartCurvature = %u, startCurvature = %lf\n", __FUNCTION__, __LINE__, PsdMapData.signStartCurvature, PsdMapData.startCurvature);
}

void PsdMessageDecoder::calcPsd04Data(const uint32_t &RoadClassValue, const uint32_t &endCurvatureValue, const uint32_t &startCurvatureValue, const uint32_t &branchAngleValue)
{
    //TODO: calculate RoadClass, endCurvature,startCurvature, branchAngle
    convertRoadClass(RoadClassValue);
    convertCurvature(endCurvatureValue, startCurvatureValue);
    convertBranchAngle(branchAngleValue);
}

void PsdMessageDecoder::testcalcPsd04Data(const uint32_t &RoadClassValue, const uint32_t &endCurvatureValue, const uint32_t &startCurvatureValue, const uint32_t &branchAngleValue)
{
    calcPsd04Data(RoadClassValue, endCurvatureValue, startCurvatureValue, branchAngleValue);
}

std::vector<struct PsdMapData *>::iterator PsdMessageDecoder::findSegmentById(uint8_t KnownId)
{
    for (auto it = vPsdMap.begin(); it != vPsdMap.end(); it++)
    {
        if ((*it)->preSegmentId == KnownId)
        {
            return it;
        }
    }

    //Note: if not found, return invalid position
    return vPsdMap.end();
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

void PsdMessageDecoder::receivedPdu_PSD_06(RxPdu_PSD_06 const &psd06)
{
	printf("[%s] [%d]: --------------------------received Pdu_PSD_06--------------------------\n", __FUNCTION__, __LINE__);
	if (psd06.getPduStatus() == PduStatus::kValid)
	{
		printf("[%s] [%d]: kValid\n", __FUNCTION__, __LINE__);
		PsdMapData.psdAttributSegmentID = psd06.get_PSD_Attribut_Segment_ID();
		PsdMapData.psdAttribut3ID = psd06.get_PSD_Attribut_3_ID();
		PsdMapData.psdAttribut3Wert = psd06.get_PSD_Attribut_3_Wert();
		PsdMapData.psdAttribut4ID = psd06.get_PSD_Attribut_4_ID();
		PsdMapData.psdAttribut4Wert = psd06.get_PSD_Attribut_4_Wert();
		PsdMapData.psdAttribut5ID = psd06.get_PSD_Attribut_5_ID();
		PsdMapData.psdAttribut5Wert = psd06.get_PSD_Attribut_5_Wert();
	}
	else 
	if (psd06.getPduStatus() == PduStatus::kTimedOut)
	{
		printf("[%s] [%d]: kTimedOut\n", __FUNCTION__, __LINE__);
	}
	else 
	if (psd06.getPduStatus() == PduStatus::kTempNotValid)
	{
		printf("[%s] [%d]: kTempNotValid\n", __FUNCTION__, __LINE__);
	}
	else 
	if (psd06.getPduStatus() == PduStatus::kNotReceivedYet)
	{
		printf("[%s] [%d]: kNotReceivedYet\n", __FUNCTION__, __LINE__);
	}
	else
	if (psd06.getPduStatus() == PduStatus::kNotValid)
	{
		printf("[%s] [%d]: kNotValid\n", __FUNCTION__, __LINE__);
	}
}

void PsdMessageDecoder::receivedPdu_PSD_05(RxPdu_PSD_05 const &psd05)
{
	printf("[%s] [%d]: --------------------------received Pdu_PSD_05--------------------------\n", __FUNCTION__, __LINE__);
	if (psd05.getPduStatus() == PduStatus::kValid)
	{
		printf("[%s] [%d]: kValid\n", __FUNCTION__, __LINE__);
		hvSegment.curSegmentId = psd05.get_PSD_Pos_Segment_ID();
		hvSegment.curRemainLength = psd05.get_PSD_Pos_Segmentlaenge();
		hvSegment.posIsUnique = psd05.get_PSD_Pos_Standort_Eindeutig();
		const uint32_t &posLengthErr = psd05.get_PSD_Pos_Fehler_Laengsrichtung();
        if (posLengthErr == 0)
        {
            hvSegment.posLengthErr = Pos_Init;
        }
        else if (posLengthErr == 1)
        {
            hvSegment.posLengthErr = Pos_0mTo2m;
        }
        else if (posLengthErr == 2)
        {
            hvSegment.posLengthErr = Pos_2mTo5m;
        }
        else if (posLengthErr == 3)
        {
            hvSegment.posLengthErr = Pos_5mTo10m;
        }
        else if (posLengthErr == 4)
        {
            hvSegment.posLengthErr = Pos_10mTo20m;
        }
        else if (posLengthErr == 5)
        {
            hvSegment.posLengthErr =  Pos_20mTo50m;
        }
        else if (posLengthErr == 6)
        {
            hvSegment.posLengthErr =  Over50m;
        }
        else if (posLengthErr == 7)
        {
            hvSegment.posLengthErr =  OffRoad;
        }
		PsdMapData.psdAttribut1ID = psd05.get_PSD_Attribut_1_ID();
		PsdMapData.psdAttribut1Wert = psd05.get_PSD_Attribut_1_Wert();
		PsdMapData.psdAttribut2ID = psd05.get_PSD_Attribut_2_ID();
		PsdMapData.psdAttribut2Wert = psd05.get_PSD_Attribut_2_Wert();
	}
	else 
	if (psd05.getPduStatus() == PduStatus::kTimedOut)
	{
		printf("[%s] [%d]: kTimedOut\n", __FUNCTION__, __LINE__);
	}
	else 
	if (psd05.getPduStatus() == PduStatus::kTempNotValid)
	{
		printf("[%s] [%d]: kTempNotValid\n", __FUNCTION__, __LINE__);
	}
	else 
	if (psd05.getPduStatus() == PduStatus::kNotReceivedYet)
	{
		printf("[%s] [%d]: kNotReceivedYet\n", __FUNCTION__, __LINE__);
	}
	else
	if (psd05.getPduStatus() == PduStatus::kNotValid)
	{
		printf("[%s] [%d]: kNotValid\n", __FUNCTION__, __LINE__);
	}
}

void PsdMessageDecoder::receivedPdu_PSD_04(RxPdu_PSD_04 const &psd04)
{
    printf("[%s] [%d]: --------------------------received Pdu_PSD_04--------------------------\n", __FUNCTION__, __LINE__);
	/*PduStatus: PDU data are valid and up-to-date*/
	if (psd04.getPduStatus() == PduStatus::kValid)
	{
		printf("[%s] [%d]: kValid\n", __FUNCTION__, __LINE__);
		PsdMapData.preSegmentId = psd04.get_PSD_Segment_ID();
		PsdMapData.prevSegmentId = psd04.get_PSD_Vorgaenger_Segment_ID();
		PsdMapData.preSegTotalLength = psd04.get_PSD_Segmentlaenge();
		PsdMapData.signEndCurvature = psd04.get_PSD_Endkruemmung_Vorz();
		PsdMapData.mpp = psd04.get_PSD_wahrscheinlichster_Pfad();
		PsdMapData.signStartCurvature = psd04.get_PSD_Anfangskruemmung_Vorz();
		PsdMapData.branchDirection = psd04.get_PSD_Abzweigerichtung();
        //TODO: calculate Psd04 Data, RoadClass, endCurvature, startCurvature, branchAngle
        calcPsd04Data(psd04.get_PSD_Strassenkategorie(), psd04.get_PSD_Endkruemmung(), psd04.get_PSD_Anfangskruemmung(), psd04.get_PSD_Abzweigewinkel());
        
        //Note: Set whether each segment is straight or curved, straight path is one where the curvature of the start and end are the same and equal to 0
        if ((psd04.get_PSD_Anfangskruemmung() == 0) && (psd04.get_PSD_Endkruemmung() == 0))
        {
            PsdMapData.sp = 1;
        }
        else
        {
            PsdMapData.sp = 0;
        }
	}
	else 
	if (psd04.getPduStatus() == PduStatus::kTimedOut)
	{
		/*PduStatus: PDU reception timed out unexpectedly*/
		printf("[%s] [%d]: kTimedOut\n", __FUNCTION__, __LINE__);
	}
	else 
	if (psd04.getPduStatus() == PduStatus::kTempNotValid)
	{
		/*PduStatus: PDU receives no updates due to bus not active or Clamp15 off*/
		printf("[%s] [%d]: kTempNotValid\n", __FUNCTION__, __LINE__);
	}
	else 
	if (psd04.getPduStatus() == PduStatus::kNotReceivedYet)
	{
		/*PduStatus: PDU was not yet received on this device, signal data are device-local initial data*/
		printf("[%s] [%d]: kNotReceivedYet\n", __FUNCTION__, __LINE__);
	}
	else
	if (psd04.getPduStatus() == PduStatus::kNotValid)
	{
		/*PduStatus: PDU data are not valid*/
		printf("[%s] [%d]: kNotValid\n", __FUNCTION__, __LINE__);
	}
}

void runMockDataReceiver(std::shared_ptr<vwg::sid::PSDParser::ISignalDataListener> pListener)
{
	printf("[%s] [%d]: runMockDataReceiver\n", __FUNCTION__, __LINE__);
	auto mockDataReceiver = [](std::shared_ptr<vwg::sid::PSDParser::ISignalDataListener> pListener) -> void
	{
        /*--------------------------------------------------------------------------*/
		vwg::sid::PSDParser::RxPdu_PSD_04 psd04;
		//TODO1: set the signals of value, assumed value, assumed straight path to use TEST_F(mapCreateAndcalcCoordinateWithoutHeading)
		psd04.PRIVATE_set_PSD_Segment_ID(3);
        psd04.PRIVATE_set_PSD_Vorgaenger_Segment_ID(2);
        psd04.PRIVATE_set_PSD_Segmentlaenge(200);
        psd04.PRIVATE_set_PSD_Endkruemmung_Vorz(0);
        psd04.PRIVATE_set_PSD_wahrscheinlichster_Pfad(1);   //mpp
        psd04.PRIVATE_set_PSD_Anfangskruemmung_Vorz(0);
        psd04.PRIVATE_set_PSD_Abzweigerichtung(0);                 //branchDirection
        psd04.PRIVATE_set_PSD_Strassenkategorie(2);                 //CountyRoad
        psd04.PRIVATE_set_PSD_Endkruemmung(0);                     //endCurvature
        psd04.PRIVATE_set_PSD_Anfangskruemmung(0);            //startCurvature
        psd04.PRIVATE_set_PSD_Abzweigewinkel(0);                     //branchAngle

		//TODO2: set Pdu status
		psd04.PRIVATE_setPduStatus(vwg::sid::PSDParser::PduStatus::kValid);
		//TODO3: invoke receivePdu function
		pListener->receivedPdu_PSD_04(psd04);

        //TODO4: save PSD04 in list, PsdMapData.preSegmentId when (PSD_Segment_ID != 0) && (PSD_Segment_ID != 1)
        PsdMessageDecoder::getInstance()->segmentManager(true);

		//TODO5: simulate psd source data and send data at an interval of 50ms
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
        /*--------------------------------------------------------------------------*/
        vwg::sid::PSDParser::RxPdu_PSD_05 psd05;
        //TODO6: set the signals of value, assumed value, assumed straight path to use TEST_F(mapCreateAndcalcCoordinateWithoutHeading)
        psd05.PRIVATE_set_PSD_Pos_Segment_ID(3);
        psd05.PRIVATE_set_PSD_Pos_Segmentlaenge(100);
        psd05.PRIVATE_set_PSD_Pos_Standort_Eindeutig(1);         //posIsUnique
        psd05.PRIVATE_set_PSD_Pos_Fehler_Laengsrichtung(2);  //posLengthErr

        //TODO7: set Pdu status
		psd05.PRIVATE_setPduStatus(vwg::sid::PSDParser::PduStatus::kValid);

        //TODO8: invoke receivePdu function
		pListener->receivedPdu_PSD_05(psd05);
        
        //TODO9: simulate psd source data and send data at an interval of 50ms
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
        /*--------------------------------------------------------------------------*/
        //TODO10: receive valid PSD06, and saveAttributToList
        vwg::sid::PSDParser::RxPdu_PSD_06 psd06;
        //TODO11: set the signals of value

        //TODO12: set Pdu status
		psd06.PRIVATE_setPduStatus(vwg::sid::PSDParser::PduStatus::kValid);

        //TODO13: invoke receivePdu function
		pListener->receivedPdu_PSD_06(psd06);

        PsdMessageDecoder::getInstance()->saveAttributToList();
        
        //TODO14: simulate psd source data and send data at an interval of 50ms
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	};
}

void connectionStateChanged(ConnectionState newState)
{
	std::string stateName = newState == ConnectionState::kConnecting ? "connecting" : (newState == ConnectionState::kConnected ? "connected" : (newState == ConnectionState::kDisconnecting ? "disconnecting" : (newState == ConnectionState::kDisconnected ? "disconnected" : "undefined")));
	std::cout << "LHWAPP: " << "new connection state: " << stateName << std::endl;
}

void runDataReceiver(std::shared_ptr<vwg::sid::PSDParser::ISignalDataListener> pListener, RECEIVER_DATA_TYPE dataType)
{
    if (dataType == RECEIVER_DATA_TYPE::UDP)
    {
#ifdef ENABLE_UDP_RECEIVER
        runUdpDataReceiver(pListener);
#endif
    }
    else
    {
        runMockDataReceiver(pListener);
    }
}

/*Thread:PsdMessageDecoder*/
void *PsdMessageDecoderRun(void *arg)
{
    printf("[%s] [%d]: PsdMessageDecoderRun\n", __FUNCTION__, __LINE__);
    // auto &handler = getSignalDataAccessHandler();
	// auto pListener = std::make_shared<PsdMessageDecoder>();
    auto pListener = std::shared_ptr<PsdMessageDecoder>(PsdMessageDecoder::getInstance(), [](PsdMessageDecoder*){ /* The custom remover is empty */ });
	// handler.start(pListener, connectionStateChanged);
    while (true)
    {
        /*TODO1: check pPsdUsageActive*/
        if (pPsdUsageActive)
        {
            //TODO2: receive valid PSD04 05, saving , and calcPsd04Data
            #ifdef USING_MOCK_SIGNAL_API
            runDataReceiver(pListener, RECEIVER_DATA_TYPE::MOCK);
            #endif // USING_MOCK_SIGNAL_API
            /*NOTE: check HV's confidence*/
            // check HV's valid curSegmentId + posIsUnique + posLengthErr in PsdMessageDecoder.cpp
        }
        else
        {
            //TODO:pPsdUsageActive == false,segmentManager() add param control push or erase
            PsdMessageDecoder::getInstance()->segmentManager(false);
        }
        sleep(1);
    }
}
