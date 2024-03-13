/*********************************************************************************
 * Copyright (c) 202x Cariad China. All rights reserved.
 * FileName:	 PsdLocation.cpp
 * Author: 	     ZhaoZijia
 * Version :	 Ver0.1
 * Date:		 2023-11-03
 * Description: get diagnotics parameter, init config, pthread_create, PsdLocation relative calculation etc.
 *
 *********************************************************************************/
/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "../inc/PsdLocation.h"
#include "../inc/GeometricCalc.h"

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: static statement
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * LOCAL AND GLOBAL VARIABLES
 *---------------------------------------------------------------------------*/
PsdLocation *PsdLocation::pInstance = NULL;
extern pthread_mutex_t decoderThreadMutex;
extern pthread_mutex_t mapThreadMutex;
pthread_t decoderThread = 0;
pthread_t mapThread = 0;                                  
double pLateralDistTolerance = 8.0;     
double pRelativePositionAngle = 45.0; 
double pRelativeDirection = 45.0;  
double pStationaryThreshold = 50.0;  //assumption value   

/*-----------------------------------------------------------------------------
 * FUNCTION DEFINITIONS: static definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
PsdLocation *PsdLocation::getInstance()
{
    if (NULL == pInstance)
    {
        pInstance = new PsdLocation();
    }
    return pInstance;
}

PsdLocation::PsdLocation()
{
    //TODO: initialize some member variables of the PsdLocation class
    mRoMatchedSegId = 0;
    mRoMatchedNode = NULL;
    mIsMatch = false;
    mData2EventList.PsdAvailable = false;
    mData2EventList.MPP = false;
    mData2EventList.roadSegClass = RoadClass_Unknown;
    mData2EventList.relativePos = Pos_Unclassified;
    RelativeDir = PSD_Dir_Unclassified;
    mData2EventList.RvRelevancy = false;
    mData2EventList.dis2Event = 0.0;
    mData2EventList.HvDTIP = 0.0;
    mData2EventList.RvDTIP = 0.0;
    printf("[%s] [%d]: initialize mRoMatchedSegId = %u\n", __FUNCTION__, __LINE__, mRoMatchedSegId);
    printf("[%s] [%d]: initialize mRoMatchedNode = %p\n", __FUNCTION__, __LINE__, mRoMatchedNode);
    printf("[%s] [%d]: initialize mIsMatch = %d\n", __FUNCTION__, __LINE__, mIsMatch);
    printf("[%s] [%d]: initialize PsdAvailable = %d\n", __FUNCTION__, __LINE__, mData2EventList.PsdAvailable);
    printf("[%s] [%d]: initialize MPP = %d\n", __FUNCTION__, __LINE__, mData2EventList.MPP);
    printf("[%s] [%d]: initialize roadSegClass = %d\n", __FUNCTION__, __LINE__, mData2EventList.roadSegClass);
    printf("[%s] [%d]: initialize relativePos = %d\n", __FUNCTION__, __LINE__, mData2EventList.relativePos);
    printf("[%s] [%d]: initialize RelativeDir = %d\n", __FUNCTION__, __LINE__, RelativeDir);
    printf("[%s] [%d]: initialize RvRelevancy = %d\n", __FUNCTION__, __LINE__, mData2EventList.RvRelevancy);
    printf("[%s] [%d]: initialize dis2Event = %f\n", __FUNCTION__, __LINE__, mData2EventList.dis2Event);
    printf("[%s] [%d]: initialize HvDTIP = %f\n", __FUNCTION__, __LINE__, mData2EventList.HvDTIP);
    printf("[%s] [%d]: initialize RvDTIP = %f\n", __FUNCTION__, __LINE__, mData2EventList.RvDTIP);
}

PsdLocation::~PsdLocation()
{
}

float PsdLocation::accumulateChildsLength(struct TreeNode *Node)
{
    //return directly when Node is NULL
    if (NULL == Node)
    {
        return 0.0;
    }

    if (1 == Node->vChilds.size())
    {
        return static_cast<float>(Node->vChilds[0]->MapData.preSegTotalLength) + accumulateChildsLength(Node->vChilds[0]);
    }
    else
    {
        return 0.0;
    }
}

float PsdLocation::calcRoDis2Intersection(Data2Location data2Location)
{
    float RvDis2Intersection = 0.0;
    //Note: need distinguish some case, such as Ro is matched the segment of Root, Parent, Current and Childs to calculate RvDis2Intersection
    if (mRoMatchedNode->MapData.nodeAttribute != ChildSegment)
    {
        pthread_mutex_lock(&mapThreadMutex);
        float MiddleLength = accumulateChildsLength(mRoMatchedNode);
        float Ro2EndCoordDis = Haversine::haversineAirDistance(data2Location.RoPos.lat, data2Location.RoPos.Long, mRoMatchedNode->MapData.endCoordinate.latitude, mRoMatchedNode->MapData.endCoordinate.longitude);
        pthread_mutex_unlock(&mapThreadMutex);
        RvDis2Intersection = MiddleLength + Ro2EndCoordDis;
    }
    else
    {
        //mRoMatchedNode->MapData.nodeAttribute == ChildSegment, RvDis2Intersection = dis2Event - HvDTIP
        RvDis2Intersection = mData2EventList.dis2Event - mData2EventList.HvDTIP;
    }   

    printf("[%s] [%d]: RvDis2Intersection = %f\n", __FUNCTION__, __LINE__, RvDis2Intersection);
    return RvDis2Intersection;
}

float PsdLocation::calcHvDis2Intersection()
{
    float HvDTIP = 0.0;
    float ChildsTotalLength = 0.0;
    struct TreeNode *Node = NULL;

    //TODO1: use the CurSegmentId of HV to find the node where it is located.
    pthread_mutex_lock(&mapThreadMutex);
    Node = PsdMap::getInstance()->findNodeById(PsdMap::getInstance()->getTree(), PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId);
    pthread_mutex_unlock(&mapThreadMutex);

    //TODO2: If the number of child nodes of this node is greater than 1,it indicates that there is an intersection.Else it indicates a straight path, and keep finding intersection.
    pthread_mutex_lock(&mapThreadMutex);
    ChildsTotalLength = accumulateChildsLength(Node);
    pthread_mutex_unlock(&mapThreadMutex);

    //TODO3: HvDTIP = CurRemainLength + every preSegTotalLength of child nodes
    printf("[%s] [%d]: curRemainLength = %u\n", __FUNCTION__, __LINE__, PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength);
    printf("[%s] [%d]: ChildsTotalLength = %f\n", __FUNCTION__,  __LINE__, ChildsTotalLength);
    HvDTIP = PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength + ChildsTotalLength;

    //TODO4: return HvDTIP
    printf("[%s] [%d]: HvDTIP = %f\n", __FUNCTION__, __LINE__, HvDTIP);
    return HvDTIP;
}

float PsdLocation::calcDistanceToEvent(Data2Location data2Location)
{
    float dis2Event = 0.0;
    //Note: need distinguish some case, such as Ro is matched the segment of Root, Parent, Current and Childs to calculate dis2Event
    if (mRoMatchedNode->MapData.nodeAttribute == RootSegment)
    {
        //TODO: dis2Event = RoRemainLength(by haversineAirDistance) on root segment + rootNode->vChilds[0]->preSegTotalLength + (HV's preSegTotalLength - curRemainLength)
        float Ro2EndCoordDis = Haversine::haversineAirDistance(data2Location.RoPos.lat, data2Location.RoPos.Long, PsdMap::getInstance()->getTree()->MapData.endCoordinate.latitude, PsdMap::getInstance()->getTree()->MapData.endCoordinate.longitude);        
        float HvDrivedLength = PsdMap::getInstance()->getTree()->vChilds[0]->vChilds[0]->MapData.preSegTotalLength - PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength; 
        dis2Event = Ro2EndCoordDis + PsdMap::getInstance()->getTree()->vChilds[0]->MapData.preSegTotalLength + HvDrivedLength;
        printf("[%s] [%d]: Ro2EndCoordDis = %f, HvDrivedLength = %f\n", __FUNCTION__, __LINE__, Ro2EndCoordDis, HvDrivedLength);       
    }
    else
    if (mRoMatchedNode->MapData.nodeAttribute == ParentSegment)
    {
        //TODO: dis2Event = Ro2EndCoordDis(by haversineAirDistance) on parent segment + (HV's preSegTotalLength - curRemainLength)
        float Ro2EndCoordDis = Haversine::haversineAirDistance(data2Location.RoPos.lat, data2Location.RoPos.Long, PsdMap::getInstance()->getTree()->vChilds[0]->MapData.endCoordinate.latitude, PsdMap::getInstance()->getTree()->vChilds[0]->MapData.endCoordinate.longitude);
        float HvDrivedLength = PsdMap::getInstance()->getTree()->vChilds[0]->vChilds[0]->MapData.preSegTotalLength - PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength; 
        dis2Event = Ro2EndCoordDis + HvDrivedLength;
        printf("[%s] [%d]: Ro2EndCoordDis = %f, HvDrivedLength = %f\n", __FUNCTION__, __LINE__, Ro2EndCoordDis, HvDrivedLength);
    }
    else
    if (mRoMatchedNode->MapData.nodeAttribute == CurSegment)
    {
        //TODO: dis2Event = invoke haversineAirDistance Ro to Hv
        dis2Event = Haversine::haversineAirDistance(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate.latitude, PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate.longitude, data2Location.RoPos.lat, data2Location.RoPos.Long);
    }
    else
    {
        //mRoMatchedNode->MapData.nodeAttribute == ChildSegment, dis2Event = distance between Ro and the starting coordinate of Ro matched segment + ChildsTotalLength + curRemainLength of HV located segment
        //TODO: Starting with the RO-matched segmentId, it accumulates backwards to the father of each segment until it reaches the segment where HV is located
        struct TreeNode *tempNode = mRoMatchedNode; //initial as RoMatched segment
        float ChildsTotalLength = 0.0;
        printf("[%s] [%d]: tempNodeId is = %u\n", __FUNCTION__, __LINE__, tempNode->MapData.preSegmentId);
        while (tempNode->MapData.prevSegmentId != PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId)
        {
            ChildsTotalLength += tempNode->ParentNode->MapData.preSegTotalLength;
            tempNode = tempNode->ParentNode;
            printf("[%s] [%d]: ChildsTotalLength = %f, tempNodeId is = %u\n", __FUNCTION__, __LINE__, ChildsTotalLength, tempNode->MapData.preSegmentId);
        }
        tempNode = NULL;
        float Ro2StartCoordDis = Haversine::haversineAirDistance(mRoMatchedNode->MapData.startCoordinate.latitude, mRoMatchedNode->MapData.startCoordinate.longitude, data2Location.RoPos.lat, data2Location.RoPos.Long);
        dis2Event = PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength + ChildsTotalLength + Ro2StartCoordDis;
        printf("[%s] [%d]: Ro2StartCoordDis = %f, ChildsTotalLength = %f, curRemainLength = %u\n", __FUNCTION__, __LINE__, Ro2StartCoordDis, ChildsTotalLength, PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength);
    }

    printf("[%s] [%d]: dis2Event = %f\n", __FUNCTION__, __LINE__, dis2Event);
    return dis2Event;
}

bool PsdLocation::calcRvRelevancy(Data2Location data2Location)
{
    printf("[%s] [%d]: relativePos = %d, RelativeDir = %d, mRoMatchedNode->MapData.mpp = %d\n", __FUNCTION__, __LINE__, mData2EventList.relativePos, RelativeDir, mRoMatchedNode->MapData.mpp);
    printf("[%s] [%d]: mRoMatchedSegId = %u, curSegmentId = %u, structSeparate = %d\n",  __FUNCTION__, __LINE__, mRoMatchedSegId, PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId, mRoMatchedNode->MapData.structSeparate);
    if (data2Location.eventClassify == Static_Event)
    {
        //for static object
        if ((mData2EventList.relativePos == Pos_Behind) || (mRoMatchedNode->MapData.mpp == false))
        {
            mData2EventList.RvRelevancy = false;
        }
        else
        if ((mData2EventList.relativePos != Pos_Behind) && (mRoMatchedNode->MapData.mpp == true))
        {
            mData2EventList.RvRelevancy = true;
        }
    }
    else
    if (data2Location.eventClassify == Dynamic_Event)
    {
        if ((mRoMatchedSegId == PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId) && (RelativeDir == PSD_Dir_Oncoming) && (mRoMatchedNode->MapData.structSeparate == 1 || mRoMatchedNode->MapData.structSeparate == 2))
        {
            mData2EventList.RvRelevancy = false;
        }
        else
        if ((RelativeDir == PSD_Dir_AwayFromBehind) || (RelativeDir == PSD_Dir_AwayFromLeft) || (RelativeDir == PSD_Dir_AwayFromRight) || (RelativeDir == PSD_Dir_Unreachable))
        {
            mData2EventList.RvRelevancy = false;
        }
        else
        if ((RelativeDir == PSD_Dir_Oncoming) || (RelativeDir == PSD_Dir_Ahead) || (RelativeDir == PSD_Dir_ComingFromLeft) || (RelativeDir == PSD_Dir_ComingFromRight) || (RelativeDir == PSD_Dir_ComingFromBehind))
        {
            mData2EventList.RvRelevancy = true;
        }
    }

    printf("[%s] [%d]: RvRelevancy = %d\n", __FUNCTION__, __LINE__, mData2EventList.RvRelevancy);
    return mData2EventList.RvRelevancy;
}

RelativeDirection_PSD PsdLocation::calcRelativeDirection(Data2Location data2Location)
{
    RelativeDirection_PSD realativeDirection = PSD_Dir_Unclassified;

    printf("[%s] [%d]: roadSegClass = %d, relativePos = %d, RvSpeed = %lf, headingDelta = %lf\n", __FUNCTION__, __LINE__, mData2EventList.roadSegClass, mData2EventList.relativePos, data2Location.RvSpeed, data2Location.headingDelta);
    //TODO1: calculate Unreachable case
    if ((mData2EventList.roadSegClass == RoadClass_highway) && (mData2EventList.relativePos == Pos_Left || mData2EventList.relativePos == Pos_Right))
    {
        realativeDirection = PSD_Dir_Unreachable;
    }
    else
    if ((mData2EventList.relativePos == Pos_Behind) && (data2Location.RvSpeed < pStationaryThreshold))
    {
        realativeDirection = PSD_Dir_Unreachable;
    }
    else
    if ((mData2EventList.relativePos == Pos_Ahead) && ((data2Location.headingDelta >= 0.0 && data2Location.headingDelta <= pRelativeDirection)  || (data2Location.headingDelta >= (360.0 - pRelativeDirection) && data2Location.headingDelta <= 360.0)))
    {
        realativeDirection = PSD_Dir_Ahead;
    }
    else 
    if ((mData2EventList.relativePos == Pos_Ahead) && (data2Location.headingDelta >= (180.0 - pRelativeDirection) && data2Location.headingDelta <= (180.0 + pRelativeDirection)))
    {
        realativeDirection = PSD_Dir_Oncoming;
    }
    else
    if ((mData2EventList.relativePos == Pos_Behind) && ((data2Location.headingDelta >= 0.0 && data2Location.headingDelta <= pRelativeDirection)  || (data2Location.headingDelta >= (360.0 - pRelativeDirection) && data2Location.headingDelta <= 360.0)))
    {
        realativeDirection = PSD_Dir_ComingFromBehind;
    }
    else
    if ((mData2EventList.relativePos == Pos_Behind) && (data2Location.headingDelta >= (180.0 - pRelativeDirection) && data2Location.headingDelta <= (180.0 + pRelativeDirection)))
    {
        realativeDirection = PSD_Dir_AwayFromBehind;
    }
    else
    if ((mData2EventList.relativePos == Pos_Left) && (data2Location.headingDelta >= (90.0 - pRelativeDirection) && data2Location.headingDelta <= (90.0 + pRelativeDirection)))
    {
        realativeDirection = PSD_Dir_ComingFromLeft;
    }
    else
    if ((mData2EventList.relativePos == Pos_Left) && (data2Location.headingDelta >= (270.0 - pRelativeDirection) && data2Location.headingDelta <= (270.0 + pRelativeDirection)))
    {
        realativeDirection = PSD_Dir_AwayFromLeft;
    }
    else
    if ((mData2EventList.relativePos == Pos_Right) && (data2Location.headingDelta >= (90.0 - pRelativeDirection) && data2Location.headingDelta <= (90.0 + pRelativeDirection)))
    {
        realativeDirection = PSD_Dir_AwayFromRight;
    }
    else 
    if ((mData2EventList.relativePos == Pos_Right) && (data2Location.headingDelta >= (270.0 - pRelativeDirection) && data2Location.headingDelta <= (270.0 + pRelativeDirection)))
    {
        realativeDirection = PSD_Dir_ComingFromRight;
    }

    printf("[%s] [%d]: realativeDirection = %d\n", __FUNCTION__, __LINE__, realativeDirection);
    return realativeDirection;
}

RelativePosition PsdLocation::calcRelativePosition(Data2Location data2Location)
{
    RelativePosition RelativePosition= Pos_Unclassified;

    //TODO1: convert (latitude, longitude) to (x, y) about Hv and Ro
    Position3D_D hvPos;
    hvPos.lat = PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate.latitude;
    hvPos.Long = PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate.longitude;
    hvPos.elevation = 0.0;
    Point deltaXY = GeometricCalc::coordinateTransform(hvPos, PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, data2Location.RoPos);
    printf("[%s] [%d]: x = %lf\n", __FUNCTION__, __LINE__, deltaXY.x);
    printf("[%s] [%d]: y = %lf\n", __FUNCTION__, __LINE__, deltaXY.y);
    printf("[%s] [%d]: accumulateBranchAngle = %lf\n", __FUNCTION__, __LINE__, mRoMatchedNode->MapData.accumulateBranchAngle);

    //TODO2: set RelativePosition of Ro
    if (deltaXY.x < 0.0)
    {
        RelativePosition = Pos_Behind;
    }
    else
    {
        //TODO3: convert accumulateBranchAngle to positive
        if (mRoMatchedNode->MapData.accumulateBranchAngle < 0.0)
        {
            mRoMatchedNode->MapData.accumulateBranchAngle += 360.0;
        }

        //TODO4: use mRoMatchedNode->MapData.accumulateBranchAngle to judge RelativePosition
        if ((mRoMatchedNode->MapData.accumulateBranchAngle > pRelativePositionAngle) && (mRoMatchedNode->MapData.accumulateBranchAngle < (180.0 - pRelativePositionAngle)))
        {
            RelativePosition = Pos_Right;
        }
        else
        if ((mRoMatchedNode->MapData.accumulateBranchAngle > (270.0 - pRelativePositionAngle)) && (mRoMatchedNode->MapData.accumulateBranchAngle < (360.0 - pRelativePositionAngle)))
        {
            RelativePosition = Pos_Left;
        }
        else
        if (((mRoMatchedNode->MapData.accumulateBranchAngle >= (360.0 - pRelativePositionAngle)) && (mRoMatchedNode->MapData.accumulateBranchAngle <= 360.0 )) || 
            ((mRoMatchedNode->MapData.accumulateBranchAngle >= 0.0) && (mRoMatchedNode->MapData.accumulateBranchAngle <= pRelativePositionAngle )))
        {
            RelativePosition = Pos_Ahead;
        }
    }

    printf("[%s] [%d]: RelativePosition = %d\n", __FUNCTION__, __LINE__, RelativePosition);
    return RelativePosition;
}

RoadSegmentClass PsdLocation::calcRoadSegmentClass()
{
    struct TreeNode *hvLocatedNode = NULL;
    RoadSegmentClass RoadClass = RoadClass_Unknown;

    pthread_mutex_lock(&mapThreadMutex);
    hvLocatedNode = PsdMap::getInstance()->findNodeById(PsdMap::getInstance()->getTree(), PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId);
    pthread_mutex_unlock(&mapThreadMutex);
    printf("[%s] [%d]: find the hvLocatedNode = %p\n", __FUNCTION__, __LINE__, hvLocatedNode);

    if (NULL == hvLocatedNode)
    {
        RoadClass = RoadClass_Unknown;
        printf("[%s] [%d]: curSegmentId is not in mTree\n", __FUNCTION__, __LINE__);
    }
    else
    {
        if (5 == hvLocatedNode->MapData.psd04RoadClass)
        {
            RoadClass = RoadClass_highway;
        }
        else
        if ((3 == hvLocatedNode->MapData.psd04RoadClass) || (4 == hvLocatedNode->MapData.psd04RoadClass))
        {
            RoadClass = RoadClass_Non_urban;
        }
        else
        if ((1 == hvLocatedNode->MapData.psd04RoadClass)||(2 == hvLocatedNode->MapData.psd04RoadClass))
        {
            RoadClass = RoadClass_Urban;
        }
        else
        {
            RoadClass = RoadClass_Unknown;
        }
    }

    printf("[%s] [%d]: RoadClass = %d\n", __FUNCTION__, __LINE__, RoadClass);
    return RoadClass;
}

bool PsdLocation::RoMatchSegment(Position3D_D RoPoint)
{
    //TODO1: in order for the following variables ro start with an invalid value when each time this function is invoked
    mIsMatch = false; 
    mRoMatchedSegId = 0;
    mRoMatchedNode = NULL;

    //TODO2: iterate over all elements in the vPsdMap and trigger actually RoMatch when vPsdMap.segIsInTree == true
    // pthread_mutex_lock(&decoderThreadMutex);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        if ((*it)->segIsInTree == true)
        {
            //TODO3: transform RoPoint, segment's startCoord, endCoord and vSampleCoord of  the type of Postion3D to Point (x, y), consider sp and curve
            if ((*it)->sp == true)
            {
                /*segment is straight path*/
                Position3D_D startCoord;
                startCoord.lat = (*it)->startCoordinate.latitude;
                startCoord.Long = (*it)->startCoordinate.longitude;
                startCoord.elevation = 0.0;

                Position3D_D endCoord;
                endCoord.lat = (*it)->endCoordinate.latitude;
                endCoord.Long = (*it)->endCoordinate.longitude;
                endCoord.elevation = 0.0;

                Point startPoint, endPoint;
                startPoint = GeometricCalc::coordinateTransform(RoPoint, PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, startCoord);
                endPoint = GeometricCalc::coordinateTransform(RoPoint, PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, endCoord);
                printf("[%s] [%d]: startPoint.x = %lf, startPoint.y = %lf\n", __FUNCTION__, __LINE__, startPoint.x, startPoint.y);
                printf("[%s] [%d]: endPoint.x = %lf, endPoint.y = %lf\n", __FUNCTION__, __LINE__, endPoint.x, endPoint.y);

                //TODO4: calculate Orthogonal Distance and Beta,  Alpha between Ro(considered as the origin) and AB 
                double A = endPoint.x - startPoint.x; //vertical coordinate of point2 - vertical coordinate of point1
                double B = startPoint.y - endPoint.y; //horizontal coordinate of point1 horizontal coordinate of point2
                double C = startPoint.y * (startPoint.x - endPoint.x) + startPoint.x * (endPoint.y - startPoint.y); //y1 * (x1 - x2) + x1 * (y2 - y1)   
                double orthogonalDistance = std::fabs(C) / sqrt(pow(A, 2) + pow(B, 2)); //|Ax0+By0+C| / sqrt(A*A+B*B), (x0, y0) is considered as Ro coordinate origin
                printf("[%s] [%d]: orthogonalDistance = %lf\n", __FUNCTION__, __LINE__, orthogonalDistance);

                // double Alpha = std::fabs(atan2(startPoint.y, startPoint.x) - atan2(startPoint.y - endPoint.y, startPoint.x - endPoint.x));
                // double Beta = std::fabs(atan2(endPoint.y - startPoint.y, endPoint.x - startPoint.x) - atan2(endPoint.y, endPoint.x));
                double Alpha = std::fabs(atan2(startPoint.x, startPoint.y) - atan2(startPoint.x - endPoint.x, startPoint.y - endPoint.y));
                double Beta = std::fabs(atan2(endPoint.x - startPoint.x, endPoint.y - startPoint.y) - atan2(endPoint.x, endPoint.y));
                printf("[%s] [%d]: Alpha: atan2(startPoint.x, startPoint.y) = %lf, atan2(startPoint.x - endPoint.x, startPoint.y - endPoint.y) = %lf\n", __FUNCTION__, __LINE__, atan2(startPoint.x, startPoint.y), atan2(startPoint.x - endPoint.x, startPoint.y - endPoint.y));
                printf("[%s] [%d]: Beta: atan2(endPoint.x - startPoint.x, endPoint.y - startPoint.y) = %lf, atan2(endPoint.x, endPoint.y) = %lf\n", __FUNCTION__, __LINE__, atan2(endPoint.x - startPoint.x, endPoint.y - startPoint.y), atan2(endPoint.x, endPoint.y));
                printf("[%s] [%d]: Alpha = %lf, Beta = %lf\n", __FUNCTION__, __LINE__, Alpha, Beta);

                //TODO5: judge ((0 <= Beta && Beta <= 2*M_PI/3) && (0 <= Alpha && Alpha <= 2*M_PI/3)) && (0 <= Orthogonal Distance && Orthogonal Distance < pLateralDistTolerance)
                if (((0.0 <= Beta && Beta <= 2*M_PI/3) && (0.0 <= Alpha && Alpha <= 2*M_PI/3)) && (0.0 <= orthogonalDistance && orthogonalDistance < pLateralDistTolerance))   
                {
                    //TODO6: record mRoMatchedSegId, find mRoMatchedNode in mTree, mIsMatch = true, break the cycle
                    mIsMatch = true;
                    mRoMatchedSegId = (*it)->preSegmentId;
                    printf("[%s] [%d]: current tree Id = %u\n", __FUNCTION__, __LINE__, PsdMap::getInstance()->getTree()->MapData.preSegmentId);
                    mRoMatchedNode = PsdMap::getInstance()->findNodeById(PsdMap::getInstance()->getTree(), mRoMatchedSegId);

                    // pthread_mutex_unlock(&decoderThreadMutex);
                    printf("[%s] [%d]: mIsMatch = %d\n", __FUNCTION__, __LINE__, mIsMatch);
                    printf("[%s] [%d]: mRoMatchedSegId = %u\n", __FUNCTION__, __LINE__, mRoMatchedSegId);
                    printf("[%s] [%d]: mRoMatchedNode = %p\n", __FUNCTION__, __LINE__, mRoMatchedNode);
                    return mIsMatch;
                }
            }
            else
            {
                /*segment is curve*/
                std::vector<struct Coordinates> vAllCoord;
                //TODO: store the startCoordinate of curve segment 
                vAllCoord.push_back((*it)->startCoordinate); 

                //TODO: store all the sampling coordinates into vAllCoord container
                for (auto pos = (*it)->vSampleCoord.begin(); pos != (*it)->vSampleCoord.end(); pos++)
                {
                    vAllCoord.push_back((*pos));
                }
                //TODO: store the endCoordinate of curve segment 
                vAllCoord.push_back((*it)->endCoordinate); 

                //TODO: judging all coordinates matched relevantly with Ro
                for (auto place = vAllCoord.begin(); place != (vAllCoord.end()-1); place++)
                {
                    Position3D_D Coord_1;
                    Coord_1.lat = (*place).latitude;
                    Coord_1.Long = (*place).longitude;
                    Coord_1.elevation = 0.0;

                    Position3D_D Coord_2;
                    Coord_2.lat = (*(place+1)).latitude;
                    Coord_2.Long = (*(place+1)).longitude;
                    Coord_2.elevation = 0.0;

                    Point Point_1, Point_2;
                    Point_1 = GeometricCalc::coordinateTransform(RoPoint, PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, Coord_1);
                    Point_2 = GeometricCalc::coordinateTransform(RoPoint, PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, Coord_2);
                    printf("[%s] [%d]: Point_1.x = %lf, Point_1.y = %lf\n", __FUNCTION__, __LINE__, Point_1.x, Point_1.y);
                    printf("[%s] [%d]: Point_2.x = %lf, Point_2.y = %lf\n", __FUNCTION__, __LINE__, Point_2.x, Point_2.y);

                    double A = Point_2.x - Point_1.x; //vertical coordinate of point2 - vertical coordinate of point1
                    double B = Point_1.y - Point_2.y; //horizontal coordinate of point1 horizontal coordinate of point2
                    double C = Point_1.y * (Point_1.x - Point_2.x) + Point_1.x * (Point_2.y - Point_1.y); //y1 * (x1 - x2) + x1 * (y2 - y1)     
                    double orthogonalDistance = std::fabs(C) / sqrt(pow(A, 2) + pow(B, 2)); //|Ax0+By0+C| / sqrt(A*A+B*B), (x0, y0) is considered as Ro coordinate origin 
                    printf("[%s] [%d]: orthogonalDistance = %lf\n", __FUNCTION__, __LINE__, orthogonalDistance);

                    double Alpha = std::fabs(atan2(Point_1.x, Point_1.y) - atan2(Point_1.x - Point_2.x, Point_1.y - Point_2.y));
                    double Beta = std::fabs(atan2(Point_2.x - Point_1.x, Point_2.y - Point_1.y) - atan2(Point_2.x, Point_2.y));
                    printf("[%s] [%d]: Alpha = %lf, Beta = %lf\n", __FUNCTION__, __LINE__, Alpha, Beta);

                    if (((0.0 <= Beta && Beta <= 2*M_PI/3) && (0.0 <= Alpha && Alpha <= 2*M_PI/3)) && (0.0 <= orthogonalDistance && orthogonalDistance < pLateralDistTolerance))   
                    {
                        mIsMatch = true;
                        mRoMatchedSegId = (*it)->preSegmentId;
                        mRoMatchedNode = PsdMap::getInstance()->findNodeById(PsdMap::getInstance()->getTree(), mRoMatchedSegId);
                        // pthread_mutex_unlock(&decoderThreadMutex);
                        printf("[%s] [%d]: mIsMatch = %d\n", __FUNCTION__, __LINE__, mIsMatch);
                        printf("[%s] [%d]: mRoMatchedSegId = %u\n", __FUNCTION__, __LINE__, mRoMatchedSegId);
                        printf("[%s] [%d]: mRoMatchedNode = %p\n", __FUNCTION__, __LINE__, mRoMatchedNode);
                        return mIsMatch;
                    }
                }
            }
        }
    }
    
    //TODO: vPsdMap is NULL, do nothing
    return mIsMatch;
}

bool PsdLocation::getMPP(uint8_t RoMatchedSegId)
{
    bool isMPP = false;
    struct TreeNode *node = NULL;

    //TODO: find KnownId relative Segment's node
    pthread_mutex_lock(&mapThreadMutex);
    node = PsdMap::getInstance()->findNodeById(PsdMap::getInstance()->getTree(), RoMatchedSegId);
    pthread_mutex_unlock(&mapThreadMutex);

    if (true == node->MapData.mpp)
    {
        isMPP = true;
    }

    printf("[%s] [%d]: isMPP = %d\n", __FUNCTION__, __LINE__, isMPP);
    return isMPP;
}

bool PsdLocation::getPsdAvailable()
{
    printf("[%s] [%d]: MapMutexStatus = %d\n", __FUNCTION__, __LINE__, PsdMap::getInstance()->getMapMutexStatus());
    printf("[%s] [%d]: curSegmentId = %d\n", __FUNCTION__, __LINE__, PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId);
    printf("[%s] [%d]: posIsUnique = %d\n", __FUNCTION__, __LINE__, PsdMessageDecoder::getInstance()->getSelfSegment().posIsUnique);
    printf("[%s] [%d]: posLengthErr = %d\n", __FUNCTION__, __LINE__, PsdMessageDecoder::getInstance()->getSelfSegment().posLengthErr);
    //TODO1: judge psd05 and orther influence factor whether available or not 
    if ((true == PsdMap::getInstance()->getMapMutexStatus()) ||
        (0 == PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId) ||
        (1 == PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId) ||
        (false == PsdMessageDecoder::getInstance()->getSelfSegment().posIsUnique)  ||
        (Pos_Init == PsdMessageDecoder::getInstance()->getSelfSegment().posLengthErr)||
        (Over50m == PsdMessageDecoder::getInstance()->getSelfSegment().posLengthErr)||
        (OffRoad == PsdMessageDecoder::getInstance()->getSelfSegment().posLengthErr))
    {
        mData2EventList.PsdAvailable = false;
    }
    else
    {
        mData2EventList.PsdAvailable = true;
    }

    return mData2EventList.PsdAvailable;
}

void PsdLocation::getEventDistance()
{
}

/*PsdROLocation*/
Data2EventList PsdLocation::getPsdRoLocation(Data2Location data2Location)
{
    //TODO1: fill Data2EventList structure
    printf("[%s] [%d]: Enter\n", __FUNCTION__, __LINE__);
    mData2EventList.PsdAvailable = getPsdAvailable();
    printf("[%s] [%d]: PsdAvailable = %d\n", __FUNCTION__, __LINE__, mData2EventList.PsdAvailable);

    printf("[%s] [%d]: RoPos.lat = %lf, RoPos.Long = %lf\n", __FUNCTION__, __LINE__, data2Location.RoPos.lat, data2Location.RoPos.Long);
    //TODO2: Ro macth HV's segments
    mIsMatch = RoMatchSegment(data2Location.RoPos);

    //TODO3: setting invalid value when Psd data is not available or Ro not macth HV's segments
    if ((false == mData2EventList.PsdAvailable) || (false == mIsMatch))
    {
        mData2EventList.MPP = false;
        mData2EventList.roadSegClass = RoadClass_Unknown;
        mData2EventList.relativePos = Pos_Unclassified;
        RelativeDir = PSD_Dir_Unclassified;
        mData2EventList.RvRelevancy = false;
        mData2EventList.dis2Event = 0.0;
        mData2EventList.HvDTIP = 0.0;
        mData2EventList.RvDTIP = 0.0;
    }
    else
    {
        //TODO3: calculate valid value if (true == mData2EventList.PsdAvailable) && (true == mIsMatch)
        mData2EventList.MPP = getMPP(mRoMatchedSegId);
        mData2EventList.roadSegClass = calcRoadSegmentClass();
        mData2EventList.relativePos = calcRelativePosition(data2Location);
        RelativeDir = calcRelativeDirection(data2Location);
        mData2EventList.RvRelevancy = calcRvRelevancy(data2Location);
        mData2EventList.dis2Event = calcDistanceToEvent(data2Location);
        if (mData2EventList.dis2Event >= pPsdValidDistance)
        {
            printf("[%s] [%d]: actual distance between RO and HV over the  pPsdValidDistance\n", __FUNCTION__, __LINE__);        
            mData2EventList.PsdAvailable = false;
            mData2EventList.MPP = false;
            mData2EventList.roadSegClass = RoadClass_Unknown;
            mData2EventList.relativePos = Pos_Unclassified;
            RelativeDir = PSD_Dir_Unclassified;
            mData2EventList.RvRelevancy = false;
            mData2EventList.dis2Event = 0.0;
            mData2EventList.HvDTIP = 0.0;
            mData2EventList.RvDTIP = 0.0;
        }

        if ((data2Location.RvSpeed != 0.0) && (RelativeDir == PSD_Dir_ComingFromLeft || RelativeDir == PSD_Dir_ComingFromRight))
        {
            mData2EventList.HvDTIP = calcHvDis2Intersection();
            mData2EventList.RvDTIP = calcRoDis2Intersection(data2Location);
            printf("[%s] [%d]: HvDTIP = %f\n", __FUNCTION__, __LINE__, mData2EventList.HvDTIP);
            printf("[%s] [%d]: RvDTIP = %f\n", __FUNCTION__, __LINE__, mData2EventList.RvDTIP);
        }
    }

    printf("[%s] [%d]: MPP = %d\n", __FUNCTION__, __LINE__, mData2EventList.MPP);
    printf("[%s] [%d]: roadSegClass = %d\n", __FUNCTION__, __LINE__, mData2EventList.roadSegClass);
    printf("[%s] [%d]: relativePos = %d\n", __FUNCTION__, __LINE__, mData2EventList.relativePos);
    printf("[%s] [%d]: RelativeDir = %d\n", __FUNCTION__, __LINE__, RelativeDir);
    printf("[%s] [%d]: RvRelevancy = %d\n", __FUNCTION__, __LINE__, mData2EventList.RvRelevancy);
    printf("[%s] [%d]: dis2Event = %f\n", __FUNCTION__, __LINE__, mData2EventList.dis2Event);

    return mData2EventList;
}

void PsdLocation::createMapThread()
{
    pthread_create(&mapThread, NULL, PsdMapRun, NULL);
    if (pthread_detach(mapThread) != 0) 
    {
        printf("Error: could not detach mapThread.\n");
    }
}

void PsdLocation::createDecoderThread()
{
    pthread_create(&decoderThread, NULL, PsdMessageDecoderRun, NULL);
    if (pthread_detach(decoderThread) != 0) 
    {
        printf("Error: could not detach decoderThread.\n");
    }
}

void PsdLocation::initPsdData()
{
    tPsdMapData PsdMapData = {0};
    tSelfSegment SelfSegment = {0};
    PsdMessageDecoder::getInstance()->setPsdMapData(PsdMapData);
    PsdMessageDecoder::getInstance()->setSelfSegment(SelfSegment);
    PsdMessageDecoder::getInstance()->getVPsdMap().clear();
}

void PsdLocation::start()
{
    initPsdData();
    createDecoderThread();
    createMapThread();
}