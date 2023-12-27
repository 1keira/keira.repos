/*********************************************************************************
 * Copyright (c) 202x Cariad China. All rights reserved.
 * FileName:	 PsdMap.cpp
 * Author: 	     ZhaoZijia
 * Version :	 Ver0.1
 * Date:		 2023-11-03
 * Description: create, update and clear PsdMap, calculate latitude and logitude coordinates
 *
 *********************************************************************************/

/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "../inc/PsdMap.h"

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/
#define P_PSD_Usage_Active 1

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: static statement
 *---------------------------------------------------------------------------*/
static uint8_t lastSize = 0;        //indicates the size of the vPsdMap container capacity to be recorded in order to trigger mapUpdate
static uint8_t count = 0;            //indicates number of inserted elements in the database
static bool doInsert = false;     //indicates whether an action has been inserted in the traversal
static uint8_t lastSegmentId = 0;

/*-----------------------------------------------------------------------------
 * LOCAL AND GLOBAL VARIABLES
 *---------------------------------------------------------------------------*/
PsdMap *PsdMap::pInstance = NULL;
extern pthread_mutex_t decoderThreadMutex;
pthread_mutex_t mapThreadMutex = PTHREAD_MUTEX_INITIALIZER;
/*-----------------------------------------------------------------------------
 * FUNCTION DEFINITIONS: static definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/

PsdMap *PsdMap::getInstance()
{
    if (NULL == pInstance)
    {
        printf("[%s] [%d]: first new a pInstance\n", __FUNCTION__, __LINE__);
        pInstance = new PsdMap();
    }
    return pInstance;
}

PsdMap::PsdMap(/* args */)
{
    mTree = NULL;
}

PsdMap::~PsdMap()
{
}

void PsdMap::setMapMutexStatus(bool MutexStatus)
{
    mMapMutexIsLocked = MutexStatus;
}

bool PsdMap::getMapMutexStatus()
{
    return mMapMutexIsLocked;
}

void PsdMap::setTree(struct TreeNode *Node)
{
    mTree = Node;
}

struct TreeNode *PsdMap::getTree()
{
    return mTree;
}

tOffset PsdMap::calcHeadingXY(double Heading, double distanceX, double distanceY)
{
    tOffset Offset = {0.0, 0.0};
    printf("[%s] [%d]: Heading = %f\n", __FUNCTION__, __LINE__, Heading);
    double HeadingRad = Haversine::toRadians(Heading);
    printf("[%s] [%d]: HeadingRad = %f\n", __FUNCTION__, __LINE__, HeadingRad);
    Offset.distanceX = distanceX * cos(HeadingRad) - distanceY * sin(HeadingRad);
    Offset.distanceY = distanceX * sin(HeadingRad) + distanceY * cos(HeadingRad);
    printf("[%s] [%d]: coordinate system rotated X = %f\n", __FUNCTION__, __LINE__, Offset.distanceX);
    printf("[%s] [%d]: coordinate system rotated Y = %f\n", __FUNCTION__, __LINE__, Offset.distanceY);

    return Offset;
}

tOffset PsdMap::calcStraightXYOffset(double Length, double accumulateBranchAngle)
{
    tOffset Offset = {0.0, 0.0};
    printf("[%s] [%d]: Length = %f, accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Length, accumulateBranchAngle);
    double accumulateBranchAngleRad = Haversine::toRadians(accumulateBranchAngle);
    printf("[%s] [%d]: accumulateBranchAngleRad = %f\n", __FUNCTION__, __LINE__, accumulateBranchAngleRad);
    Offset.distanceX = Length * cos(accumulateBranchAngleRad);
    Offset.distanceY = Length * sin(accumulateBranchAngleRad);
    printf("[%s] [%d]: straight offset X with accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Offset.distanceX);
    printf("[%s] [%d]: straight offset Y with accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Offset.distanceY);

    return Offset;
}

tOffset PsdMap::calcCurveXYOffset(double S, double A0_square, double A1_square, double accumulateBranchAngle)
{
    tOffset Offset = {0.0, 0.0};
    // printf("[%s] [%d]: S = %lf\n", __FUNCTION__, __LINE__, S);
    // printf("[%s] [%d]: sin(0 / 2 * A0_square) = %lf\n", __FUNCTION__, __LINE__, sin(0 / 2 * A0_square));
    // printf("[%s] [%d]: pow(S, 2) = %lf, A1_square = %lf, pow(S, 2) / A1_square = %lf\n", __FUNCTION__, __LINE__, pow(S, 2), A1_square, pow(S, 2) / A1_square);
    // printf("[%s] [%d]: sin(pow(S, 2) / 2 * A1_square) = %lf\n", __FUNCTION__, __LINE__, sin(pow(S, 2) / 2 * A1_square));
    // printf("[%s] [%d]: sin(BranchAngleRad) = %lf\n", __FUNCTION__, __LINE__, sin(BranchAngleRad));
    double accumulateBranchAngleRad = Haversine::toRadians(accumulateBranchAngle);
    Offset.distanceX = (S * (cos(0 / 2 * A0_square) + cos(pow(S, 2) / 2 * A1_square)) / 2) * cos(accumulateBranchAngleRad);
    Offset.distanceY = (S * (sin(0 / 2 * A0_square) + sin(pow(S, 2) / 2 * A1_square)) / 2) * sin(accumulateBranchAngleRad);
    printf("[%s] [%d]: curve offset X with accumulateBranchAngleRad = %f\n", __FUNCTION__, __LINE__, Offset.distanceX);
    printf("[%s] [%d]: curve offset Y with accumulateBranchAngleRad = %f\n", __FUNCTION__, __LINE__, Offset.distanceY);

    return Offset;
}

struct PsdMapData PsdMap::calcChildSegmentCoordinate(struct TreeNode *childNode)
{
    printf("[%s] [%d]: Is childSegment\n", __FUNCTION__, __LINE__);
    //HV's childs, start point: startCoordinate, destination point: endCoordinate
    if (childNode->MapData.sp == 1)
    {
        //XY: indicates the offset of child's segment relative HV's segment
        tOffset XY = calcStraightXYOffset(childNode->MapData.preSegTotalLength, childNode->MapData.accumulateBranchAngle);
        if ((childNode->ParentNode->MapData.nodeAttribute == CurSegment) || (childNode->ParentNode->MapData.nodeAttribute == RootAndCurSegment))
        {
            childNode->MapData.accumulateXY.distanceX = disHv2EndBeforeRotatingCoord.distanceX + XY.distanceX;
            childNode->MapData.accumulateXY.distanceY = disHv2EndBeforeRotatingCoord.distanceY+ XY.distanceY;
        }
        else
        {
            //summary offset = the offset of all previous segments relative to the HV segment + the offset of the this segment relative to the HV segment
            childNode->MapData.accumulateXY.distanceX =  childNode->ParentNode->MapData.accumulateXY.distanceX + XY.distanceX;
            childNode->MapData.accumulateXY.distanceY =  childNode->ParentNode->MapData.accumulateXY.distanceY + XY.distanceY;
        }
        printf("[%s] [%d]: accumulateXY.distanceX = %f, accumulateXY.distanceY = %f\n", __FUNCTION__, __LINE__, childNode->MapData.accumulateXY.distanceX, childNode->MapData.accumulateXY.distanceY);
        
        //rotate coordinate system,  this is based on the direction in which the HV is driving
        XY = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, childNode->MapData.accumulateXY.distanceX, childNode->MapData.accumulateXY.distanceY);
        childNode->MapData.endCoordinate = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY.distanceY, XY.distanceX);
    }
    else
    {
        double finalRemainLength = 0.0;
        tCoordinates SampleCoord = childNode->MapData.startCoordinate;
        tOffset XY = {0.0, 0.0};
        double Ssum = 0.0;
        double KSsum = 0.0;
        double S = 0.0;
        double L = childNode->MapData.preSegTotalLength;
        double R = 1.0 / std::fabs(childNode->MapData.startCurvature);
        double K0 = childNode->MapData.startCurvature;
        double KL = childNode->MapData.endCurvature;
        double Kstart = K0;
        double A0_square = 0.0 / K0;
        double A1_square = childNode->MapData.preSegTotalLength / KL;
        double variableCurveAngleRad = 0.0; 
        double sampleRotationAngleRad = 0.0;    
        double arcRotationAngleRad = 0.0;
        if ((childNode->ParentNode->MapData.nodeAttribute == CurSegment) || (childNode->ParentNode->MapData.nodeAttribute == RootAndCurSegment))
        {
            //TODO: ChildSegment's accumulateBranchAngle should be += accumulateBranchAngleHv2End before sampling
            childNode->MapData.accumulateBranchAngle += accumulateBranchAngleHv2End;
            //TODO: ChildSegment's accumulateXY should be == disHv2EndBeforeRotatingCoord before sampling
            childNode->MapData.accumulateXY.distanceX = disHv2EndBeforeRotatingCoord.distanceX;
            childNode->MapData.accumulateXY.distanceY = disHv2EndBeforeRotatingCoord.distanceY;
        }
        else
        {
            //Note: ChildSegment's accumulateXY should be == previous segment's accumulateXY before sampling
            childNode->MapData.accumulateXY.distanceX = childNode->ParentNode->MapData.accumulateXY.distanceX;
            childNode->MapData.accumulateXY.distanceY = childNode->ParentNode->MapData.accumulateXY.distanceY;
        }
        while (1)
        {
            S = 2 * R * acos((R - MaxRoadError) / R);
            printf("[%s] [%d]: R = %f\n", __FUNCTION__, __LINE__, R);
            Ssum += S;
            if (Ssum > L)
            {
                break;
            }
            printf("[%s] [%d]: Ssum = %f\n", __FUNCTION__, __LINE__, Ssum);
            KSsum = K0 + (KL - K0) / L * Ssum;  //next sample point curvature
            A1_square = Ssum / KSsum;
            // deltaBranchAngleRad = 2 * atan((KSsum - Kstart) / (1 + Kstart * KSsum));
            sampleRotationAngleRad = acos((R-MaxRoadError)/R);
            childNode->MapData.accumulateBranchAngle += Haversine::toDegrees(sampleRotationAngleRad);
            printf("[%s] [%d]: sampleRotationAngle = %f accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(sampleRotationAngleRad), childNode->MapData.accumulateBranchAngle);
            XY = calcCurveXYOffset(S, A0_square, A1_square, childNode->MapData.accumulateBranchAngle);
            childNode->MapData.accumulateXY.distanceX +=  XY.distanceX;
            childNode->MapData.accumulateXY.distanceY +=   XY.distanceY;
            printf("[%s] [%d]: accumulateXY.distanceX = %f, accumulateXY.distanceY = %f\n", __FUNCTION__, __LINE__, childNode->MapData.accumulateXY.distanceX, childNode->MapData.accumulateXY.distanceY);  
            XY = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, childNode->MapData.accumulateXY.distanceX, childNode->MapData.accumulateXY.distanceY);
            SampleCoord = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY.distanceY, XY.distanceX);
            childNode->MapData.vSampleCoord.push_back(SampleCoord);
            //update next cyclic value
            R = 1.0 / std::fabs(KSsum);
            A0_square = A1_square;
            Kstart = KSsum;
        }
        //calculate child's curvature endCoordinate
        finalRemainLength = L - (Ssum - S);
        printf("[%s] [%d]: finalRemainLength = %f\n", __FUNCTION__, __LINE__, finalRemainLength);
        if (KL == Kstart)
        {
            arcRotationAngleRad = (finalRemainLength / R) * (childNode->MapData.signStartCurvature ? -1 : 1);
            childNode->MapData.accumulateBranchAngle += Haversine::toDegrees(arcRotationAngleRad);
            printf("[%s] [%d]: arcRotationAngle = %f accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(arcRotationAngleRad), childNode->MapData.accumulateBranchAngle);
        }
        else
        {
            variableCurveAngleRad = 2 * atan((KL - Kstart) / (1 + Kstart * KL)); 
            childNode->MapData.accumulateBranchAngle += Haversine::toDegrees(variableCurveAngleRad);
            printf("[%s] [%d]: variableCurveAngle = %f accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(variableCurveAngleRad), childNode->MapData.accumulateBranchAngle);
        }
        XY = calcCurveXYOffset(finalRemainLength, A0_square, L / KL, childNode->MapData.accumulateBranchAngle);
        
        childNode->MapData.accumulateXY.distanceX +=  XY.distanceX;
        childNode->MapData.accumulateXY.distanceY +=   XY.distanceY;
        printf("[%s] [%d]: accumulateXY.distanceX = %f, accumulateXY.distanceY = %f\n", __FUNCTION__, __LINE__, childNode->MapData.accumulateXY.distanceX, childNode->MapData.accumulateXY.distanceY);  
        XY = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, childNode->MapData.accumulateXY.distanceX, childNode->MapData.accumulateXY.distanceY);
        
        childNode->MapData.endCoordinate = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY.distanceY, XY.distanceX);
        printf("[%s] [%d]: childSegment's endCoordinate latitude = %f  longitude = %f\n", __FUNCTION__, __LINE__, childNode->MapData.endCoordinate.latitude, childNode->MapData.endCoordinate.longitude);
    }

    return childNode->MapData;
}

struct PsdMapData PsdMap::calcRootOrParentSegmentCoordinate(struct TreeNode *rootOrParentNode)
{
    printf("[%s] [%d]: Is rootSegment or parentSegment\n", __FUNCTION__, __LINE__);
    //HV's root or parent: calculate the destination coordinates in reverse, start point: endCoordinate, destination point: startCoordinate
    if (rootOrParentNode->MapData.sp == 1)
    {
        //XY: indicates the offset of root's or parent's segment relative HV's segment
        tOffset XY = calcStraightXYOffset(rootOrParentNode->MapData.preSegTotalLength *(-1), rootOrParentNode->MapData.accumulateBranchAngle);
        //the two segments's accumulateXY before and after the HV's segment should be distinguished, and the location of the HV should be used as the coordinate origin
        if (((rootOrParentNode->vChilds.at(0))->MapData.nodeAttribute == CurSegment) || ((rootOrParentNode->vChilds.at(0))->MapData.nodeAttribute == RootAndCurSegment))
        {
            rootOrParentNode->MapData.accumulateXY.distanceX = disHv2StartBeforeRotatingCoord.distanceX + XY.distanceX;
            rootOrParentNode->MapData.accumulateXY.distanceY = disHv2StartBeforeRotatingCoord.distanceY+ XY.distanceY;
        }
        else 
        {
            rootOrParentNode->MapData.accumulateXY.distanceX = (rootOrParentNode->vChilds.at(0))->MapData.accumulateXY.distanceX + XY.distanceX;
            rootOrParentNode->MapData.accumulateXY.distanceY = (rootOrParentNode->vChilds.at(0))->MapData.accumulateXY.distanceY + XY.distanceY;
        }
        printf("[%s] [%d]: accumulateXY.distanceX = %f, accumulateXY.distanceY = %f\n", __FUNCTION__, __LINE__, rootOrParentNode->MapData.accumulateXY.distanceX, rootOrParentNode->MapData.accumulateXY.distanceY);

        XY = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, rootOrParentNode->MapData.accumulateXY.distanceX, rootOrParentNode->MapData.accumulateXY.distanceY);
        rootOrParentNode->MapData.startCoordinate = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY.distanceY, XY.distanceX);
    }
    else
    {
        double finalRemainLength = 0.0;
        tCoordinates SampleCoord = {0.0, 0.0};
        tOffset XY = {0.0, 0.0};
        double Ssum = 0.0;
        double KSsum = 0.0;
        double S = 0.0;
        double L = rootOrParentNode->MapData.preSegTotalLength;
        double R = 1.0 / std::fabs(rootOrParentNode->MapData.endCurvature);
        double K0 = rootOrParentNode->MapData.endCurvature;
        double KL = rootOrParentNode->MapData.startCurvature;
        double Kstart = K0;
        double A0_square = 0.0 / K0;
        double A1_square = rootOrParentNode->MapData.preSegTotalLength / KL;
        double variableCurveAngleRad = 0.0;                                            
        double sampleRotationAngleRad = 0.0;                                        
        double arcRotationAngleRad = 0.0;
        
        if (((rootOrParentNode->vChilds.at(0))->MapData.nodeAttribute == CurSegment) || ((rootOrParentNode->vChilds.at(0))->MapData.nodeAttribute == RootAndCurSegment))
        {
            //TODO: ParentSegment's accumulateBranchAngle should be += accumulateBranchAngleHv2Start before sampling
            rootOrParentNode->MapData.accumulateBranchAngle += accumulateBranchAngleHv2Start;
            //TODO: ParentSegment's accumulateXY should be == disHv2StartBeforeRotatingCoord before sampling
            rootOrParentNode->MapData.accumulateXY.distanceX = disHv2StartBeforeRotatingCoord.distanceX ;
            rootOrParentNode->MapData.accumulateXY.distanceY = disHv2StartBeforeRotatingCoord.distanceY;
        }
        else
        {
            //Note: RootSegment's accumulateXY should be == ParentSegment's accumulateXY before sampling
            rootOrParentNode->MapData.accumulateXY.distanceX = (rootOrParentNode->vChilds.at(0))->MapData.accumulateXY.distanceX;
            rootOrParentNode->MapData.accumulateXY.distanceY = (rootOrParentNode->vChilds.at(0))->MapData.accumulateXY.distanceY;
        }
        while (1)
        {
            S = 2 * R * acos((R - MaxRoadError) / R);
            printf("[%s] [%d]: R = %f\n", __FUNCTION__, __LINE__, R);
            Ssum += S;
            if (Ssum > L)
            {
                break;
            }
            printf("[%s] [%d]: Ssum = %f\n", __FUNCTION__, __LINE__, Ssum);
            KSsum = K0 + (KL - K0) / L * Ssum;  //next sample point curvature
            A1_square = Ssum / KSsum;
            // variableCurveAngleRad = 2 * atan((KSsum - Kstart) / (1 + Kstart * KSsum));
            sampleRotationAngleRad = acos((R-MaxRoadError)/R);
            rootOrParentNode->MapData.accumulateBranchAngle += Haversine::toDegrees(sampleRotationAngleRad);
            printf("[%s] [%d]: sampleRotationAngle = %f accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(sampleRotationAngleRad), rootOrParentNode->MapData.accumulateBranchAngle);
            XY = calcCurveXYOffset(S*(-1), A0_square, A1_square, rootOrParentNode->MapData.accumulateBranchAngle);
            rootOrParentNode->MapData.accumulateXY.distanceX +=  XY.distanceX;
            rootOrParentNode->MapData.accumulateXY.distanceY +=   XY.distanceY;
            printf("[%s] [%d]: accumulateXY.distanceX = %f, accumulateXY.distanceY = %f\n", __FUNCTION__, __LINE__, rootOrParentNode->MapData.accumulateXY.distanceX, rootOrParentNode->MapData.accumulateXY.distanceY);  
            XY = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, rootOrParentNode->MapData.accumulateXY.distanceX, rootOrParentNode->MapData.accumulateXY.distanceY);
            SampleCoord = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY.distanceY, XY.distanceX);
            rootOrParentNode->MapData.vSampleCoord.insert(rootOrParentNode->MapData.vSampleCoord.begin(), SampleCoord);
            //update next cyclic value
            R = 1.0 / std::fabs(KSsum);
            A0_square = A1_square;
            Kstart = KSsum;
        }
        //calculate curvature startCoordinate
        finalRemainLength = L - (Ssum - S);
        printf("[%s] [%d]: finalRemainLength = %f\n", __FUNCTION__, __LINE__, finalRemainLength);
        if (KL == Kstart)
        {
            arcRotationAngleRad = (finalRemainLength / R) * (rootOrParentNode->MapData.signStartCurvature ? -1 : 1);
            rootOrParentNode->MapData.accumulateBranchAngle += Haversine::toDegrees(arcRotationAngleRad);
            printf("[%s] [%d]: arcRotationAngle = %f accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(arcRotationAngleRad), rootOrParentNode->MapData.accumulateBranchAngle);
        }
        else
        {
            variableCurveAngleRad = 2 * atan((KL - Kstart) / (1 + Kstart * KL)); 
            rootOrParentNode->MapData.accumulateBranchAngle += Haversine::toDegrees(variableCurveAngleRad);
            printf("[%s] [%d]: variableCurveAngle = %f accumulateBranchAngle = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(variableCurveAngleRad), rootOrParentNode->MapData.accumulateBranchAngle);
        }
        XY = calcCurveXYOffset(finalRemainLength*(-1), A0_square, L / KL, rootOrParentNode->MapData.accumulateBranchAngle);
        rootOrParentNode->MapData.accumulateXY.distanceX +=  XY.distanceX;
        rootOrParentNode->MapData.accumulateXY.distanceY +=   XY.distanceY;
        printf("[%s] [%d]: accumulateXY.distanceX = %f, accumulateXY.distanceY = %f\n", __FUNCTION__, __LINE__, rootOrParentNode->MapData.accumulateXY.distanceX, rootOrParentNode->MapData.accumulateXY.distanceY);  
        XY = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, rootOrParentNode->MapData.accumulateXY.distanceX, rootOrParentNode->MapData.accumulateXY.distanceY);
        rootOrParentNode->MapData.startCoordinate = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY.distanceY, XY.distanceX);
        printf("[%s] [%d]: rootSegment or parentSegment's startCoordinate latitude = %f  longitude = %f\n", __FUNCTION__, __LINE__, rootOrParentNode->MapData.startCoordinate.latitude, rootOrParentNode->MapData.startCoordinate.longitude);
    }

    return rootOrParentNode->MapData;
}

struct PsdMapData PsdMap::calcCurSegmentCoordinate(struct TreeNode *curNode)
{
    printf("[%s] [%d]: Is curSegment or rootAndcurSegment\n", __FUNCTION__, __LINE__);
    //straight path, calc the start and end coordinates of HV's segment
    if (curNode->MapData.sp == 1)
    {
    /*HV's endCoordinate*/
        accumulateBranchAngleHv2End = 0.0;  //because of straight path has not accumulateBranchAngle
        //XY: indicates the offset of current's segment relative HV's position
        tOffset XY_1 = calcStraightXYOffset(PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength, curNode->MapData.accumulateBranchAngle);
        //summary offset = the offset of the current segment relative to HV's position
        disHv2EndBeforeRotatingCoord.distanceX =  XY_1.distanceX;
        disHv2EndBeforeRotatingCoord.distanceY =   XY_1.distanceY;
        printf("[%s] [%d]: disHv2EndBeforeRotatingCoord.distanceX = %f, disHv2EndBeforeRotatingCoord.distanceY = %f\n", __FUNCTION__, __LINE__, disHv2EndBeforeRotatingCoord.distanceX, disHv2EndBeforeRotatingCoord.distanceY);  
        //rotate coordinate system,  this is based on the direction in which the HV is driving            
        XY_1 = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, disHv2EndBeforeRotatingCoord.distanceX, disHv2EndBeforeRotatingCoord.distanceY);
        //Y<->Horizontal Distance<->deltaLon, X<->Vertical Distance<->deltaLat
        curNode->MapData.endCoordinate = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY_1.distanceY, XY_1.distanceX); 
        printf("[%s] [%d]: HV's endCoordinate latitude = %f  longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.endCoordinate.latitude, curNode->MapData.endCoordinate.longitude);
    /*HV's startCoordinate*/
        accumulateBranchAngleHv2Start = 0.0; 
        tOffset XY_2 = calcStraightXYOffset((curNode->MapData.preSegTotalLength - PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength)*(-1), curNode->MapData.accumulateBranchAngle);
        //summary offset = the offset of the current segment relative to HV's position
        disHv2StartBeforeRotatingCoord.distanceX =  XY_2.distanceX;
        disHv2StartBeforeRotatingCoord.distanceY =   XY_2.distanceY;
        printf("[%s] [%d]: disHv2StartBeforeRotatingCoord.distanceX = %f, disHv2StartBeforeRotatingCoord.distanceY = %f\n", __FUNCTION__, __LINE__, disHv2StartBeforeRotatingCoord.distanceX, disHv2StartBeforeRotatingCoord.distanceY);
        XY_2 = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, disHv2StartBeforeRotatingCoord.distanceX, disHv2StartBeforeRotatingCoord.distanceY);
        
        //Y<->Horizontal Distance<->deltaLon, X<->Vertical Distance<->deltaLat
        curNode->MapData.startCoordinate = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY_2.distanceY, XY_2.distanceX);
        printf("[%s] [%d]: HV's startCoordinate latitude = %f  longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.startCoordinate.latitude, curNode->MapData.startCoordinate.longitude);
    }
    else
    {
        /*HV's endCoordinate*/
        double finalRemainLength = 0.0;
        tCoordinates SampleCoord = {0.0, 0.0};
        tOffset XY_1 = {0.0, 0.0};
        double Ssum = 0.0;
        double KSsum = 0.0;
        double S = 0.0;
        double L = curNode->MapData.preSegTotalLength;                      //total length of HV's segment
        double R = 1.0 / std::fabs(curNode->MapData.startCurvature);//initial radius of curvature
        double K0 = curNode->MapData.startCurvature;                            //segment initial curvature
        double KL = curNode->MapData.endCurvature;                             //segment terminal curvature
        double Kstart = 0.0;                                                                                      //save the curvature of the current sampling point
        double A0_square = 0.0;                                                                            //cyclic override calculations, to be kept up to date
        double A1_square = 0.0;                                                                            //cyclic override calculations, to be kept up to date
        double DrivedLength = L - PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength;  //distance drived by HV on current segment
        double KdrivedLength = K0 + (KL - K0) / L * DrivedLength;       //curvature of the current segment position of HV
        double variableCurveAngleRad = 0.0;                                                //indicate the angle of rotation between any two points of the variable curvature curve
        double sampleRotationAngleRad = 0.0;                                            //indicate the angle of rotation when sampling
        double arcRotationAngleRad = 0.0;                                                     //indicate the angle of rotation of the arc
        accumulateBranchAngleHv2End = 0.0;
        K0 = KdrivedLength;                                                                                 //starting calculation from HV's position
        Kstart = KdrivedLength;                                                                          //only the first Kstart == K0
        R = 1.0 / std::fabs(KdrivedLength);                                                     //starting radius of curvature from HV's position
        //calculate the sampling points between the HV's starting point and the end of HV's segment
        while (1)
        {
            S = 2 * R * acos((R - MaxRoadError) / R);
            printf("[%s] [%d]: R = %f\n", __FUNCTION__, __LINE__, R);
            Ssum += S;
            if (Ssum > PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength)
            {
                break;
            }
            printf("[%s] [%d]: Ssum = %f\n", __FUNCTION__, __LINE__, Ssum);
            KSsum = K0 + (KL - K0) / PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength * Ssum; //next sample point curvature
            A1_square = Ssum / KSsum;
            // variableCurveAngleRad = 2 * atan((KSsum - Kstart) / (1 + Kstart * KSsum));
            //Note: using the sampling rotation angle when the number of samples is greater than 1
            sampleRotationAngleRad = acos((R-MaxRoadError)/R);
            accumulateBranchAngleHv2End += Haversine::toDegrees(sampleRotationAngleRad);
            printf("[%s] [%d]: sampleRotationAngle = %f accumulateBranchAngleHv2End = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(sampleRotationAngleRad), accumulateBranchAngleHv2End);
            XY_1 = calcCurveXYOffset(S, A0_square, A1_square, accumulateBranchAngleHv2End);
            disHv2EndBeforeRotatingCoord.distanceX +=  XY_1.distanceX;
            disHv2EndBeforeRotatingCoord.distanceY +=   XY_1.distanceY;
            printf("[%s] [%d]: disHv2EndBeforeRotatingCoord.distanceX = %f, disHv2EndBeforeRotatingCoord.distanceY = %f\n", __FUNCTION__, __LINE__, disHv2EndBeforeRotatingCoord.distanceX, disHv2EndBeforeRotatingCoord.distanceY);  
            XY_1 = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, disHv2EndBeforeRotatingCoord.distanceX, disHv2EndBeforeRotatingCoord.distanceY);
            SampleCoord = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY_1.distanceY, XY_1.distanceX);
            curNode->MapData.vSampleCoord.push_back(SampleCoord);
            //update next cyclic value
            R = 1.0 / std::fabs(KSsum);
            A0_square = A1_square;
            Kstart = KSsum;
        }
        //calculate curvature endCoordinate
        finalRemainLength = PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength - (Ssum - S);
        printf("[%s] [%d]: finalRemainLength = %f\n", __FUNCTION__, __LINE__, finalRemainLength);
        if (KL == Kstart)
        {
            //for arc
            arcRotationAngleRad = (finalRemainLength / R) * (curNode->MapData.signStartCurvature ? -1 : 1);
            accumulateBranchAngleHv2End += Haversine::toDegrees(arcRotationAngleRad);
            printf("[%s] [%d]: arcRotationAngle = %f accumulateBranchAngleHv2End = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(arcRotationAngleRad), accumulateBranchAngleHv2End);
        }
        else
        {
           //for variable curvature curve
            variableCurveAngleRad = 2 * atan((KL - Kstart) / (1 + Kstart * KL)); 
            accumulateBranchAngleHv2End += Haversine::toDegrees(variableCurveAngleRad);
            printf("[%s] [%d]: variableCurveAngle = %f accumulateBranchAngleHv2End = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(variableCurveAngleRad), accumulateBranchAngleHv2End);
        }            
        XY_1 = calcCurveXYOffset(finalRemainLength, A0_square, PsdMessageDecoder::getInstance()->getSelfSegment().curRemainLength / KL, accumulateBranchAngleHv2End);
        
        disHv2EndBeforeRotatingCoord.distanceX +=  XY_1.distanceX;
        disHv2EndBeforeRotatingCoord.distanceY +=   XY_1.distanceY;
        printf("[%s] [%d]: disHv2EndBeforeRotatingCoord.distanceX = %f, disHv2EndBeforeRotatingCoord.distanceY = %f\n", __FUNCTION__, __LINE__, disHv2EndBeforeRotatingCoord.distanceX, disHv2EndBeforeRotatingCoord.distanceY);     
        XY_1 = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, disHv2EndBeforeRotatingCoord.distanceX, disHv2EndBeforeRotatingCoord.distanceY);
        curNode->MapData.endCoordinate = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY_1.distanceY, XY_1.distanceX);
        printf("[%s] [%d]: HV's endCoordinate latitude = %f  longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.endCoordinate.latitude, curNode->MapData.endCoordinate.longitude);
        /*HV's startCoordinate*/
        tOffset XY_2 = {0.0, 0.0};
        accumulateBranchAngleHv2Start = 0.0;
        K0 = KdrivedLength;
        Kstart = KdrivedLength;
        KL = curNode->MapData.startCurvature;
        R = 1.0 / std::fabs(KdrivedLength);
        Ssum = 0.0;
        A0_square = 0.0 / KdrivedLength;
        while (1)
        {
            S = 2 * R * acos((R - MaxRoadError) / R);
            printf("[%s] [%d]: R = %f\n", __FUNCTION__, __LINE__, R);
            Ssum += S;
            if (Ssum > DrivedLength)
            {
                break;
            }
            printf("[%s] [%d]: Ssum = %f\n", __FUNCTION__, __LINE__, Ssum);
            KSsum = K0 + (KL - K0) / DrivedLength * Ssum;//next sample point curvature
            A1_square = Ssum / KSsum;
            // variableCurveAngleRad = 2 * atan((KSsum - Kstart) / (1 + Kstart * KSsum));
            sampleRotationAngleRad = acos((R-MaxRoadError)/R);
            accumulateBranchAngleHv2Start += Haversine::toDegrees(sampleRotationAngleRad);
            printf("[%s] [%d]: sampleRotationAngle = %f accumulateBranchAngleHv2Start = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(sampleRotationAngleRad), accumulateBranchAngleHv2Start);
            XY_2 = calcCurveXYOffset(S*(-1), A0_square, A1_square, accumulateBranchAngleHv2Start);
            disHv2StartBeforeRotatingCoord.distanceX +=  XY_2.distanceX;
            disHv2StartBeforeRotatingCoord.distanceY +=   XY_2.distanceY;
            printf("[%s] [%d]: disHv2StartBeforeRotatingCoord.distanceX = %f, disHv2StartBeforeRotatingCoord.distanceY = %f\n", __FUNCTION__, __LINE__, disHv2StartBeforeRotatingCoord.distanceX, disHv2StartBeforeRotatingCoord.distanceY);  
            XY_2 = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, disHv2StartBeforeRotatingCoord.distanceX, disHv2StartBeforeRotatingCoord.distanceY);
            SampleCoord = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY_2.distanceY, XY_2.distanceX);
            curNode->MapData.vSampleCoord.insert(curNode->MapData.vSampleCoord.begin(), SampleCoord);
            //update next cyclic value
            R = 1.0 / std::fabs(KSsum);
            A0_square = A1_square;
            Kstart = KSsum;
        }
        //calculate curvature startCoordinate
        finalRemainLength = DrivedLength - (Ssum - S);
        printf("[%s] [%d]: finalRemainLength = %f\n", __FUNCTION__, __LINE__, finalRemainLength);
        if (KL == Kstart)
        {
            arcRotationAngleRad = (finalRemainLength / R) * (curNode->MapData.signStartCurvature ? -1 : 1);
            accumulateBranchAngleHv2Start += Haversine::toDegrees(arcRotationAngleRad);
            printf("[%s] [%d]: arcRotationAngle = %f accumulateBranchAngleHv2Start = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(arcRotationAngleRad), accumulateBranchAngleHv2Start);
        }
        else
        {
            variableCurveAngleRad = 2 * atan((KL - Kstart) / (1 + Kstart * KL)); 
            accumulateBranchAngleHv2Start += Haversine::toDegrees(variableCurveAngleRad);
            printf("[%s] [%d]: variableCurveAngle = %f accumulateBranchAngleHv2Start = %f\n", __FUNCTION__, __LINE__, Haversine::toDegrees(variableCurveAngleRad), accumulateBranchAngleHv2Start);
        }
        XY_2 = calcCurveXYOffset(finalRemainLength*(-1), A0_square, DrivedLength / KL, accumulateBranchAngleHv2Start);
        disHv2StartBeforeRotatingCoord.distanceX +=  XY_2.distanceX;
        disHv2StartBeforeRotatingCoord.distanceY +=   XY_2.distanceY;
        printf("[%s] [%d]: disHv2StartBeforeRotatingCoord.distanceX = %f, disHv2StartBeforeRotatingCoord.distanceY = %f\n", __FUNCTION__, __LINE__, disHv2StartBeforeRotatingCoord.distanceX, disHv2StartBeforeRotatingCoord.distanceY);  
        XY_2 = calcHeadingXY(PsdMessageDecoder::getInstance()->getSelfSegment().hvHeading, disHv2StartBeforeRotatingCoord.distanceX, disHv2StartBeforeRotatingCoord.distanceY);
        curNode->MapData.startCoordinate = Haversine::calcDestination(PsdMessageDecoder::getInstance()->getSelfSegment().hvCoordinate, XY_2.distanceY, XY_2.distanceX);
        printf("[%s] [%d]: HV's startCoordinate latitude = %f  longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.startCoordinate.latitude, curNode->MapData.startCoordinate.longitude);
    }

    return curNode->MapData;
}

struct PsdMapData PsdMap::calcCoordinate(struct TreeNode *Node)
{
    //HV's segment
    if ((Node->MapData.nodeAttribute == CurSegment) || (Node->MapData.nodeAttribute == RootAndCurSegment))
    {
        Node->MapData = calcCurSegmentCoordinate(Node);
    }
    else
    if ((Node->MapData.nodeAttribute == RootSegment)||(Node->MapData.nodeAttribute == ParentSegment))
    {
        Node->MapData = calcRootOrParentSegmentCoordinate(Node);
    }
    else
    if (Node->MapData.nodeAttribute == ChildSegment)
    {
        Node->MapData = calcChildSegmentCoordinate(Node);
    }

    return Node->MapData;
}

struct TreeNode *PsdMap::findNodeById(struct TreeNode *Node, uint8_t KnownId)
{
    struct TreeNode *result = NULL;
    if (NULL == Node)
    {
        return NULL;
    }

    if (KnownId == Node->MapData.preSegmentId)
    {
        return Node;
    }

    for (auto it = Node->vChilds.begin(); it != Node->vChilds.end(); it++)
    {
        result = findNodeById((*it), KnownId);
        if (NULL != result)
        {
            printf("[%s] [%d]: result = %p\n", __FUNCTION__, __LINE__, result);
            return result;
        }
    }

    printf("[%s] [%d]: result = %p\n", __FUNCTION__, __LINE__, result);
    //all nodes not find
    return NULL;
}

void PsdMap::deleteNodeExceptCurrent(struct TreeNode *Node)
{
    for (auto it = Node->vChilds.begin(); it != Node->vChilds.end(); it++)
    {
        if (PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId != (*it)->MapData.preSegmentId)
        {
            deleteSubTree(*it);
            Node->vChilds.erase(it);  //Note: after erasing, the next element of vector whether << or not?
            it -= 1; 
        }
        //Note: else it++, goto check the next childNode
    }
}

void PsdMap::deleteSubTree(struct TreeNode *Node)
{
    //return directly when node is NULL
    if (NULL == Node)
    {
        return ;
    }
    
    for (auto it = Node->vChilds.begin(); it != Node->vChilds.end(); it++)
    {
        deleteSubTree(*it);
    }

    //TODO: erase vPsdMap, finding position by Id.
    pthread_mutex_lock(&decoderThreadMutex);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        if ((*it)->preSegmentId == Node->MapData.preSegmentId)
        {
            PsdMessageDecoder::getInstance()->popUpList(it); //clear the data domain of this node
            break;
        }
    }
    pthread_mutex_unlock(&decoderThreadMutex);

    Node->ParentNode = NULL;
    //delete Node;
    //for gtest
    Node = NULL;
}

struct TreeNode *PsdMap::deleteOldRoot()
{
    //return directly when mTree is NULL
    if (NULL == mTree)
    {
        return NULL;
    }
    else
    {
        //TODO1: find the node of Segment in tree by Id
        printf("[%s] [%d]: old parentNode = %u is newRoot\n", __FUNCTION__, __LINE__, mTree->vChilds.at(0)->MapData.preSegmentId);
        struct TreeNode *newRoot = mTree->vChilds.at(0);

        //TODO2: update the nodeAttribute of newRoot and the prevSegmentId of newRoot
        newRoot->ParentNode = NULL;
        newRoot->MapData.nodeAttribute = RootSegment;
        newRoot->MapData.prevSegmentId = mTree->vChilds.at(0)->MapData.preSegmentId;

        //TODO3: erase vPsdMap, finding position by the Id of old rootNode.
        pthread_mutex_lock(&decoderThreadMutex);
        for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
        {
            if ((*it)->preSegmentId == mTree->MapData.preSegmentId)
            {
                PsdMessageDecoder::getInstance()->popUpList(it); //point the position of container element
                break;
            }
        }
        pthread_mutex_unlock(&decoderThreadMutex);
        //TODO4: free the memory space occupied by the old rootNode
        //delete mTree; 
        //for gtest
        mTree = NULL;
        return newRoot;
    }
}

void PsdMap::clearNodeOutTree(struct TreeNode *Node)
{
    for (auto it = Node->vChilds.begin(); it != Node->vChilds.end(); it++)
    {
        clearNodeOutTree(*it);
    }
    printf("[%s] [%d]: clear Node = %p\n", __FUNCTION__, __LINE__, Node);
    Node->ParentNode = NULL;
    // delete Node;
    //for gtest
    Node = NULL;
}

void PsdMap::dfsCalcChildCoord(struct TreeNode *Node)
{
    if (Node == NULL)
    {
        return ;
    }
    std::vector<struct PsdMapData *>::iterator iter;
    //calculate end coordinate
    for (auto it = Node->vChilds.begin(); it != Node->vChilds.end(); it++)
    {
        //The starting point of each child is equal to the end point of the previous one
        pthread_mutex_lock(&mapThreadMutex);
        mMapMutexIsLocked = true;
        (*it)->MapData.startCoordinate = Node->MapData.endCoordinate; 
        (*it)->MapData.accumulateBranchAngle = Node->MapData.accumulateBranchAngle + (*it)->MapData.branchAngle; 
        (*it)->MapData = calcCoordinate(*it);
        pthread_mutex_unlock(&mapThreadMutex);
        mMapMutexIsLocked = false;
        pthread_mutex_lock(&decoderThreadMutex);
        iter = PsdMessageDecoder::getInstance()->findSegmentById((*it)->MapData.preSegmentId);
        *(*iter) =  (*it)->MapData;
        pthread_mutex_unlock(&decoderThreadMutex);
    }

    for (auto child : Node->vChilds)
    {
        dfsCalcChildCoord(child);
    }
}

void PsdMap::updateChildNode(std::vector<struct PsdMapData *>::iterator it)
{
    struct TreeNode *tempNode = findNodeById(mTree, (*it)->prevSegmentId);
    printf("[%s] [%d]: tempNode is = %p, preSegmentId = %u, prevSegmentId = %u, segIsInTree = %d\n", __FUNCTION__, __LINE__, tempNode, (*it)->preSegmentId, (*it)->prevSegmentId, (*it)->segIsInTree);
    if (NULL != tempNode)
    {
        //TODO1: filter conditions for root, parent and current, because they're already in mTree
        if ((tempNode->MapData.nodeAttribute == RootSegment) || (tempNode->MapData.nodeAttribute == ParentSegment))
        {
            //Note: skip this it, traverse the next one
            return ;
        }
        else
        {   
            //TODO2: just mount child node, tempNode is the node with (*it)->prevSegmentId 
            if (tempNode->vChilds.size() > 5)
            {
                printf("[%s] [%d]: tempNode->vChilds.size() > 5, stop insert this child to the tempNode instead, should goto insert next child\n", __FUNCTION__, __LINE__);
                return ;
            }
            /*insert childs*/
            if (((*it)->segIsInTree == false) && (tempNode->MapData.preSegmentId == (*it)->prevSegmentId))
            {
                struct TreeNode *childNode = insertChildNode(tempNode, it);
                printf("[%s] [%d]: childNode's preSegmentId = %u\n", __FUNCTION__, __LINE__, childNode->MapData.preSegmentId);
            }
            else
            {
                count += 1;
                printf("[%s] [%d]: some nodes are already in tree\n", __FUNCTION__, __LINE__);
            }
        }
    }
    else 
    {
        doInsert = false;
        printf("[%s] [%d]: goto check the next segment info from vPsdMap\n", __FUNCTION__,  __LINE__);
    }   
}

void PsdMap::updateOtherNode()
{
    //return directly when mTree is NULL
    if (NULL == mTree)
    {
        return ;
    }

    if (mTree->MapData.nodeAttribute == RootAndCurSegment)
    {
        mTree->ParentNode = NULL;
        mTree->MapData.nodeAttribute = ParentSegment;
        //Note: delete brother nodes except the CurSegment 
        deleteNodeExceptCurrent(mTree);
        mTree->vChilds.at(0)->MapData.nodeAttribute = CurSegment;
        count = 2; //for updateChildNode, count will be cleared as 0 after the update
    }
    else 
    if (mTree->MapData.nodeAttribute == ParentSegment)
    {
        mTree->ParentNode = NULL;
        mTree->MapData.nodeAttribute = RootSegment;
        mTree->vChilds.at(0)->MapData.nodeAttribute = ParentSegment;
        //Note: delete brother nodes except the CurSegment
        deleteNodeExceptCurrent(mTree->vChilds.at(0));
        mTree->vChilds.at(0)->vChilds.at(0)->MapData.nodeAttribute = CurSegment;
        count = 3; //for updateChildNode, count will be cleared as 0 after the update
    }
    else 
    if (mTree->MapData.nodeAttribute == RootSegment)
    {
        //this RootSegment is new root
        //TODO1: find HV's last current node, lastCurNode is newParent
        struct TreeNode *lastCurNode = findNodeById(mTree, lastSegmentId);
        printf("[%s] [%d]: lastCurNode = %u is newParent\n", __FUNCTION__, __LINE__, lastCurNode->MapData.preSegmentId);

        //TODO2: update the nodeAttribute of lastCurNode
        lastCurNode->MapData.nodeAttribute = ParentSegment;

        //TODO3: lastCurNode's(this is now ParentSegment) childs need to be deleteed except current segment
        deleteNodeExceptCurrent(lastCurNode);

        //TODO4: find HV current node, curNode is newCurrent, lastCurNode->vChilds.at(0) also newCurrent
        struct TreeNode *curNode = findNodeById(mTree, PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId);
        printf("[%s] [%d]: curNode  = %p\n", __FUNCTION__, __LINE__, curNode);

        //TODO5: update the nodeAttribute of curNode
        if (curNode != NULL)
        {
            printf("[%s] [%d]: curNode  = %u\n", __FUNCTION__, __LINE__, curNode->MapData.preSegmentId);
            curNode->MapData.nodeAttribute = CurSegment;
        }
        count = 3; //for updateChildNode, count will be cleared as 0 after the update
    }
}

void PsdMap::updateRootNode()
{
    if (mTree->MapData.nodeAttribute == RootAndCurSegment)
    {
        //Note: do not delete root node, need change nodeAttribute  to parent node
        return ;
    }
    else
    if (mTree->MapData.nodeAttribute == ParentSegment)
    {
        //Note: do not delete parent node, need change nodeAttribute to root node
        return ;
    }
    else 
    if (mTree->MapData.nodeAttribute == RootSegment)
    {
        //Note:  delete old root node only if the mTree attribute is RootSegment
        printf("[%s] [%d]: old RootNode = %u\n", __FUNCTION__, __LINE__, mTree->MapData.preSegmentId);
        mTree = deleteOldRoot();
        printf("[%s] [%d]: new RootNode = %u\n", __FUNCTION__, __LINE__, mTree->MapData.preSegmentId);
    }
}

struct TreeNode *PsdMap::createNode()
{
    struct TreeNode *newNode = new(struct TreeNode);
    if (NULL == newNode)
    {
        printf("[%s] [%d]: new failed\n", __FUNCTION__, __LINE__);
        return NULL;
    }
    else
    {
        printf("[%s] [%d]: newNode = %p\n", __FUNCTION__, __LINE__, newNode);
        return newNode;
    }
}

struct TreeNode *PsdMap::insertChildNode(struct TreeNode *tempNode, std::vector<struct PsdMapData *>::iterator it)
{
    struct TreeNode *childNode = createNode();
    printf("[%s] [%d]: childNode = %p\n", __FUNCTION__, __LINE__, childNode);
    pthread_mutex_lock(&decoderThreadMutex);
    (*it)->segIsInTree = true;
    (*it)->nodeAttribute = ChildSegment;
    childNode->MapData = *(*it);
    pthread_mutex_unlock(&decoderThreadMutex);
    childNode->ParentNode = tempNode;
    childNode->vChilds.clear();
    tempNode->vChilds.push_back(childNode);
    count += 1;
    doInsert = true;

    return childNode;
}

struct TreeNode *PsdMap::insertParentNode(struct TreeNode *Node, std::vector<struct PsdMapData *>::iterator it)
{
    struct TreeNode *parentNode = createNode();
    printf("[%s] [%d]: parentNode = %p\n", __FUNCTION__, __LINE__, parentNode);
    pthread_mutex_lock(&decoderThreadMutex);
    (*it)->segIsInTree = true;
    (*it)->nodeAttribute = ParentSegment;
    parentNode->MapData = *(*it);
    pthread_mutex_unlock(&decoderThreadMutex);
    mTree = parentNode;  //mTree is updated as parentNode
    parentNode->ParentNode = NULL;
    parentNode->vChilds.push_back(Node);
    Node->ParentNode = parentNode;
    count += 1;
    doInsert = true;

    return parentNode;
}

struct TreeNode *PsdMap::insertRootNode(struct TreeNode *Node, std::vector<struct PsdMapData *>::iterator it)
{
    struct TreeNode *rootNode = createNode();
    printf("[%s] [%d]: rootNode = %p\n", __FUNCTION__, __LINE__, rootNode);
    //consider whether or not to add a mutex_lock
    pthread_mutex_lock(&decoderThreadMutex);
    (*it)->segIsInTree = true;
    (*it)->nodeAttribute = RootSegment;
    rootNode->MapData = *(*it);
    pthread_mutex_unlock(&decoderThreadMutex);
    mTree = rootNode;   //mTree is updated as rootNode
    rootNode->ParentNode = NULL;
    rootNode->vChilds.push_back(Node);
    Node->ParentNode = rootNode; //Node is still parentNode
    count += 1;
    doInsert = true;

    return rootNode;
}

void PsdMap::insertNode(struct TreeNode *Node, std::vector<struct PsdMapData *>::iterator it)
{    
    printf("[%s] [%d]: (*it)->preSegmentId = %u's segIsInTree = %d\n", __FUNCTION__,  __LINE__, (*it)->preSegmentId, (*it)->segIsInTree);
    /*HV's parent or root*/
    if (Node->MapData.prevSegmentId == (*it)->preSegmentId)
    {
        if ((*it)->segIsInTree == false) 
        {
            /*HV's root*/
            if ((*it)->preSegmentId == (*it)->prevSegmentId)
            {
                struct TreeNode *rootNode = insertRootNode(Node, it);
                rootNode->MapData.endCoordinate = Node->MapData.startCoordinate;
                //the branch angle of the parent relative to the root, because it is calculated backwards from the segment where the HV is located.
                rootRelativeParentAngle = Node->MapData.branchAngle;   
                //accumulateBranchAngle relative to HV's segment, for PsdLocation module to calcRelativePosition.
                rootNode->MapData.accumulateBranchAngle = Node->MapData.accumulateBranchAngle + rootRelativeParentAngle; 
                rootNode->MapData = calcCoordinate(rootNode);
                pthread_mutex_lock(&decoderThreadMutex);
                *(*it) = rootNode->MapData;  
                pthread_mutex_unlock(&decoderThreadMutex);
                if (rootNode->MapData.sp == 1)
                {
                    printf("[%s] [%d]: %u's startCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, rootNode->MapData.preSegmentId, rootNode->MapData.startCoordinate.latitude, rootNode->MapData.startCoordinate.longitude);
                    printf("[%s] [%d]: %u's endCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, rootNode->MapData.preSegmentId, rootNode->MapData.endCoordinate.latitude, rootNode->MapData.endCoordinate.longitude);
                }
                else
                {
                    printf("[%s] [%d]: %u's startCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, rootNode->MapData.preSegmentId, rootNode->MapData.startCoordinate.latitude, rootNode->MapData.startCoordinate.longitude);
                    for (auto it = rootNode->MapData.vSampleCoord.begin(); it != rootNode->MapData.vSampleCoord.end(); it++)
                    {
                        printf("[%s] [%d]: %u's SampleCoord: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, rootNode->MapData.preSegmentId, it->latitude, it->longitude);
                    }
                    printf("[%s] [%d]: %u's endCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, rootNode->MapData.preSegmentId, rootNode->MapData.endCoordinate.latitude, rootNode->MapData.endCoordinate.longitude);
                }
            }
            else
            {
                /*HV's parent*/
                struct TreeNode *parentNode = insertParentNode(Node, it);
                parentNode->MapData.endCoordinate = Node->MapData.startCoordinate;
                //the branch angle of the parent relative to the current, because it is calculated backwards from the segment where the HV is located.
                parentRelativeCurrentAngle = Node->MapData.branchAngle;   //use current relative parent's branchAngle as to accumulate, parentNode->MapData.branchAngle is still itself branchAngle(relative to root)
                //accumulateBranchAngle relative to HV's segment, for PsdLocation module to calcRelativePosition.
                parentNode->MapData.accumulateBranchAngle = Node->MapData.accumulateBranchAngle + parentRelativeCurrentAngle; 
                parentNode->MapData = calcCoordinate(parentNode);
                pthread_mutex_lock(&decoderThreadMutex);
                *(*it) = parentNode->MapData;  
                // (*it)->branchAngle = parentRelativeCurrentAngle;  //save parentRelativeCurrentAngle as new parent's branchAngle to list, but parentNode->MapData.branchAngle is still parent relative root in mTree
                pthread_mutex_unlock(&decoderThreadMutex);
                if (parentNode->MapData.sp == 1)
                {
                    printf("[%s] [%d]: %u's startCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, parentNode->MapData.preSegmentId, parentNode->MapData.startCoordinate.latitude, parentNode->MapData.startCoordinate.longitude);
                    printf("[%s] [%d]: %u's endCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, parentNode->MapData.preSegmentId, parentNode->MapData.endCoordinate.latitude, parentNode->MapData.endCoordinate.longitude);
                }
                else
                {
                    printf("[%s] [%d]: %u's startCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, parentNode->MapData.preSegmentId, parentNode->MapData.startCoordinate.latitude, parentNode->MapData.startCoordinate.longitude);
                    for (auto it = parentNode->MapData.vSampleCoord.begin(); it != parentNode->MapData.vSampleCoord.end(); it++)
                    {
                        printf("[%s] [%d]: %u's SampleCoord: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, parentNode->MapData.preSegmentId, it->latitude, it->longitude);
                    }
                    printf("[%s] [%d]: %u's endCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, parentNode->MapData.preSegmentId, parentNode->MapData.endCoordinate.latitude, parentNode->MapData.endCoordinate.longitude);
                }
            }
        }
        else
        {
            printf("[%s] [%d]: root or parent nodes are already in tree\n", __FUNCTION__,  __LINE__);
        }
    }
    
    /*traverse the mTree, finding the childs node from the current tree*/
    struct TreeNode *tempNode = findNodeById(mTree, (*it)->prevSegmentId);
    printf("[%s] [%d]: tempNode is = %p, preSegmentId = %u, prevSegmentId = %u, segIsInTree = %d\n", __FUNCTION__, __LINE__, tempNode, (*it)->preSegmentId, (*it)->prevSegmentId, (*it)->segIsInTree);
    if (NULL != tempNode)
    {
        /*HV's childs*/
        if (tempNode->vChilds.size() > 5)
        {
            printf("[%s] [%d]: tempNode->vChilds.size() > 5, stop insert this child to the tempNode instead, should goto insert next child\n", __FUNCTION__, __LINE__);
            return ;
        }
        /*insert childs*/
        if (((*it)->segIsInTree == false) && (tempNode->MapData.preSegmentId == (*it)->prevSegmentId))
        {
            struct TreeNode *childNode = insertChildNode(tempNode, it);
            //the end coordinates of the previous segment are equal to the start coordinates of this segment
            childNode->MapData.startCoordinate = tempNode->MapData.endCoordinate;  
            //the cumulative branch angle of this segment is equal to the cumulative branch angle of the previous segment add the branch angle relative to the previous segment
            childNode->MapData.accumulateBranchAngle = tempNode->MapData.accumulateBranchAngle + childNode->MapData.branchAngle; 
            childNode->MapData = calcCoordinate(childNode);
            pthread_mutex_lock(&decoderThreadMutex);
            *(*it) = childNode->MapData; 
            pthread_mutex_unlock(&decoderThreadMutex);
            printf("[%s] [%d]: childNode's preSegmentId = %u\n", __FUNCTION__, __LINE__, childNode->MapData.preSegmentId);
            if (childNode->MapData.sp == 1)
            {
                printf("[%s] [%d]: %u's startCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, childNode->MapData.preSegmentId, childNode->MapData.startCoordinate.latitude, childNode->MapData.startCoordinate.longitude);
                printf("[%s] [%d]: %u's endCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, childNode->MapData.preSegmentId, childNode->MapData.endCoordinate.latitude, childNode->MapData.endCoordinate.longitude);
            }
            else
            {
                printf("[%s] [%d]: %u's startCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, childNode->MapData.preSegmentId, childNode->MapData.startCoordinate.latitude, childNode->MapData.startCoordinate.longitude);
                for (auto it = childNode->MapData.vSampleCoord.begin(); it != childNode->MapData.vSampleCoord.end(); it++)
                {
                    printf("[%s] [%d]: %u's SampleCoord: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, childNode->MapData.preSegmentId, it->latitude, it->longitude);
                }
                printf("[%s] [%d]: %u's endCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, childNode->MapData.preSegmentId, childNode->MapData.endCoordinate.latitude, childNode->MapData.endCoordinate.longitude);
            }
        }
        else
        {
            printf("[%s] [%d]: some nodes are already in tree\n", __FUNCTION__, __LINE__);
        }
    }
    else 
    {
        doInsert = false;
        printf("[%s] [%d]: goto check the next segment info from vPsdMap\n", __FUNCTION__,  __LINE__);
    }   
}

void PsdMap::insertNodeInTree()
{
    struct TreeNode *curNode = createNode();
    printf("[%s] [%d]: curNode = %p\n", __FUNCTION__, __LINE__, curNode);

    //TODO1: using HV information to create the first Node in Tree
    if (NULL != curNode)
    {
        //TODO2: find where curSegmentId is in vPsdMap and save HV's information to the curNode
        pthread_mutex_lock(&decoderThreadMutex);
        struct PsdMapData *HvMapData = curIdIsInList();
        pthread_mutex_unlock(&decoderThreadMutex);
        HvMapData->segIsInTree = true;
        //At the beginning, the segment where the HV was located was also the root segment
        if (HvMapData->preSegmentId == HvMapData->prevSegmentId)
        {
            HvMapData->nodeAttribute = RootAndCurSegment;
        }
        else
        {
            HvMapData->nodeAttribute = CurSegment;    
        }
        curNode->MapData = *HvMapData;
        mTree = curNode;
        curNode->ParentNode = NULL;
        curNode->vChilds.clear();
        curNode->MapData.accumulateBranchAngle = 0.0; //HV's segment, for PsdLocation module to calcRelativePosition.
        count += 1;
        doInsert = true;
        printf("[%s] [%d]: count = %u\n", __FUNCTION__, __LINE__, count);
        printf("[%s] [%d]: current tree is = %p, current tree Id is = %u, curSegmentId is = %u\n", __FUNCTION__, __LINE__, mTree, mTree->MapData.preSegmentId, PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId);

        //TODO3: calculate HV's endCoordinate and startCoordinate
        curNode->MapData = calcCoordinate(curNode);
        //TODO4: save the calculated data back into the list
        pthread_mutex_lock(&decoderThreadMutex);
        *HvMapData = curNode->MapData;  
        pthread_mutex_unlock(&decoderThreadMutex);
        if (curNode->MapData.sp == 1)
        {
            printf("[%s] [%d]: %u's startCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.preSegmentId, curNode->MapData.startCoordinate.latitude, curNode->MapData.startCoordinate.longitude);
            printf("[%s] [%d]: %u's endCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.preSegmentId, curNode->MapData.endCoordinate.latitude, curNode->MapData.endCoordinate.longitude);
        }
        else
        {
            printf("[%s] [%d]: %u's startCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.preSegmentId, curNode->MapData.startCoordinate.latitude, curNode->MapData.startCoordinate.longitude);
            for (auto it = curNode->MapData.vSampleCoord.begin(); it != curNode->MapData.vSampleCoord.end(); it++)
            {
                printf("[%s] [%d]: %u's SampleCoord: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.preSegmentId, it->latitude, it->longitude);
            }
            printf("[%s] [%d]: %u's endCoordinate: latitude = %f, longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.preSegmentId, curNode->MapData.endCoordinate.latitude, curNode->MapData.endCoordinate.longitude);
        }

        //TODO5: insert other Nodes in tree
        while ((count < PsdMessageDecoder::getInstance()->getVPsdMap().size()) && (doInsert == true))
        {
            for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
            {
                //Note: count > vPsdMap.size() need to stop creat map
                if (count >= PsdMessageDecoder::getInstance()->getVPsdMap().size())
                {
                    printf("[%s] [%d]: count >= size()\n", __FUNCTION__, __LINE__);
                    break ;
                }
                insertNode(mTree, it);
            }
        }

        //TODO6: reset the count and offset for mapUpdate after all elements being inserted in tree
        count = 0;
        doInsert = false;
    }
    else
    {
        printf("[%s] [%d]: curNode create failed, not mapCreate anymore\n", __FUNCTION__, __LINE__);
        return ;
    }
}

void PsdMap::mapClear(struct TreeNode *Node)
{
    printf("[%s] [%d]: --------------------------mapClear------------------------------\n", __FUNCTION__, __LINE__);
    pthread_mutex_lock(&mapThreadMutex);
    mMapMutexIsLocked = true;
    printf("[%s] [%d]: Node = %p\n", __FUNCTION__, __LINE__, Node);
    clearNodeOutTree(Node);
    //for gtest
    mTree = NULL;
    printf("[%s] [%d]: tree = %p has been cleared\n", __FUNCTION__, __LINE__, getTree());
    pthread_mutex_unlock(&mapThreadMutex);
    mMapMutexIsLocked = false;
}

void PsdMap::mapUpdate()
{
    printf("[%s] [%d]: --------------------------mapUpdate------------------------------\n", __FUNCTION__, __LINE__);
    //TODO1: update root 
    pthread_mutex_lock(&mapThreadMutex);
    mMapMutexIsLocked = true;
    updateRootNode();
    printf("[%s] [%d]: updateRootNode fullfill\n", __FUNCTION__, __LINE__);
    pthread_mutex_unlock(&mapThreadMutex);
    mMapMutexIsLocked = false;

    //TODO2: update parent, current and delete childs 
    pthread_mutex_lock(&mapThreadMutex);
    mMapMutexIsLocked = true;
    updateOtherNode();
    printf("[%s] [%d]: updateOtherNode\n", __FUNCTION__, __LINE__);
    pthread_mutex_unlock(&mapThreadMutex);
    mMapMutexIsLocked = false;

    //TODO3: insert new child nodes
    pthread_mutex_lock(&mapThreadMutex);
    mMapMutexIsLocked = true;
    doInsert = true; //just for the fisrt step in mapUpdate
    while ((count < PsdMessageDecoder::getInstance()->getVPsdMap().size()) && (doInsert == true))
    {
        for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
        {
            //Note: count > vPsdMap.size() need to stop creat map
            if (count >= PsdMessageDecoder::getInstance()->getVPsdMap().size())
            {
                printf("[%s] [%d]: count >= size()\n", __FUNCTION__, __LINE__);
                break ;
            }
            //Only the action of the mounted child nodes are not calculated 
            updateChildNode(it);
        }
    }
    pthread_mutex_unlock(&mapThreadMutex);
    mMapMutexIsLocked = false;

    //TODO4: all the child nodes enter the tree and then iterate through the tree from the beginning to calculate the latitude and longitude coordinates of each node
    printf("[%s] [%d]: --------------------------updateCoordinate------------------------------\n", __FUNCTION__, __LINE__);
    /*1: calculate current segment's start (latitude, longitude) and end (latitude, longitude)*/
    pthread_mutex_lock(&decoderThreadMutex);
    uint8_t curSegmentId = PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId;
    pthread_mutex_unlock(&decoderThreadMutex);
    pthread_mutex_lock(&mapThreadMutex);
    mMapMutexIsLocked = true;
    struct TreeNode *curNode = findNodeById(mTree, curSegmentId);
    curNode->MapData.accumulateBranchAngle = 0.0;
    curNode->MapData = calcCoordinate(curNode);
    pthread_mutex_unlock(&mapThreadMutex);
    mMapMutexIsLocked = false;
    //Note: save the calculated data back into the list
    pthread_mutex_lock(&decoderThreadMutex);
    std::vector<struct PsdMapData *>::iterator iter = PsdMessageDecoder::getInstance()->findSegmentById(curSegmentId);
    *(*iter) =  curNode->MapData;
    pthread_mutex_unlock(&decoderThreadMutex);
    printf("[%s] [%d]: current.startCoordinate.latitude = %f, startCoordinate.longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.startCoordinate.latitude, curNode->MapData.startCoordinate.longitude);
    printf("[%s] [%d]: current.endCoordinate.latitude = %f, endCoordinate.longitude = %f\n", __FUNCTION__, __LINE__, curNode->MapData.endCoordinate.latitude, curNode->MapData.endCoordinate.longitude);
    /*2: if current segment's parent, root not null, to calculate theirs start (latitude, longitude)*/
    if (curNode->ParentNode != NULL)
    {
        pthread_mutex_lock(&mapThreadMutex);
        mMapMutexIsLocked = true;
        curNode->ParentNode->MapData.endCoordinate = curNode->MapData.startCoordinate;
        //the branch angle of the parent relative to the current, because it is calculated backwards from the segment where the HV is located.
        parentRelativeCurrentAngle = curNode->MapData.branchAngle;   //use current relative parent's branchAngle as to accumulate, parentNode->MapData.branchAngle is still itself branchAngle(relative to root)
        //accumulateBranchAngle relative to HV's segment, for PsdLocation module to calcRelativePosition.
        curNode->ParentNode->MapData.accumulateBranchAngle = curNode->MapData.accumulateBranchAngle + parentRelativeCurrentAngle; 
        curNode->ParentNode->MapData = calcCoordinate(curNode->ParentNode);
        pthread_mutex_unlock(&mapThreadMutex);
        mMapMutexIsLocked = false;
        pthread_mutex_lock(&decoderThreadMutex);
        iter = PsdMessageDecoder::getInstance()->findSegmentById(curNode->ParentNode->MapData.preSegmentId);
        *(*iter) =  curNode->ParentNode->MapData;
        pthread_mutex_unlock(&decoderThreadMutex);
        printf("[%s] [%d]: parent.startCoordinate.latitude = %f, startCoordinate.longitude = %f\n", __FUNCTION__, __LINE__, curNode->ParentNode->MapData.startCoordinate.latitude, curNode->ParentNode->MapData.startCoordinate.longitude);
        printf("[%s] [%d]: parent.endCoordinate.latitude = %f, endCoordinate.longitude = %f\n", __FUNCTION__, __LINE__, curNode->ParentNode->MapData.endCoordinate.latitude, curNode->ParentNode->MapData.endCoordinate.longitude);
        //Note: if the current tree has a root, the coordinates of the root will be calculated, if the root is null, it will not be calculated
        if (curNode->ParentNode->ParentNode != NULL)
        {
            pthread_mutex_lock(&mapThreadMutex);
            mMapMutexIsLocked = true;
            curNode->ParentNode->ParentNode->MapData.endCoordinate = curNode->ParentNode->MapData.startCoordinate; 
            rootRelativeParentAngle = curNode->ParentNode->MapData.branchAngle;
            curNode->ParentNode->ParentNode->MapData.accumulateBranchAngle = curNode->ParentNode->MapData.accumulateBranchAngle + rootRelativeParentAngle;
            curNode->ParentNode->ParentNode->MapData = calcCoordinate(curNode->ParentNode->ParentNode);
            pthread_mutex_unlock(&mapThreadMutex);
            mMapMutexIsLocked = false;
            pthread_mutex_lock(&decoderThreadMutex);
            iter = PsdMessageDecoder::getInstance()->findSegmentById(curNode->ParentNode->ParentNode->MapData.preSegmentId);
            *(*iter) =  curNode->ParentNode->ParentNode->MapData;
            pthread_mutex_unlock(&decoderThreadMutex);
            printf("[%s] [%d]: root.startCoordinate.latitude = %f, startCoordinate.longitude = %f\n", __FUNCTION__, __LINE__, curNode->ParentNode->ParentNode->MapData.startCoordinate.latitude, curNode->ParentNode->ParentNode->MapData.startCoordinate.longitude);
            printf("[%s] [%d]: root.endCoordinate.latitude = %f, endCoordinate.longitude = %f\n", __FUNCTION__, __LINE__, curNode->ParentNode->ParentNode->MapData.endCoordinate.latitude, curNode->ParentNode->ParentNode->MapData.endCoordinate.longitude);
        }
    }
    /*3: DFS the tree, calculate all child nodes's end (latitude, longitude) starting with curNode*/
    dfsCalcChildCoord(curNode);

    //TODO5: reset the count and offset for mapUpdate after all elements being inserted in tree
    count = 0;
    doInsert = false;
}

void PsdMap::mapCreate()
{
    printf("[%s] [%d]: --------------------------mapCreate------------------------------\n", __FUNCTION__, __LINE__);
    pthread_mutex_lock(&mapThreadMutex);
    mMapMutexIsLocked = true;
    insertNodeInTree();
    pthread_mutex_unlock(&mapThreadMutex);
    mMapMutexIsLocked = false;
}

struct PsdMapData *PsdMap::curIdIsInList()
{
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        if ((*it)->preSegmentId == PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId)
        {
            printf("[%s] [%d]: curSegmentId is in list = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
            return (*it);
        }
    }

    printf("[%s] [%d]: curSegmentId is not in List\n", __FUNCTION__, __LINE__);
    return NULL;
}

/*Thread: PsdMap*/
void *PsdMapRun(void *arg)
{
    int8_t CurSegId = -1;
    while (true)
    {
        /*TODO1: check pPsdUsageActive*/
        if (pPsdUsageActive)
        {
            /*TODO2: check HV's confidence*/
            // check HV's valid curSegmentId + posIsUnique + posLengthErr + (lat, lon) + heading + headingAccuracy(for filter invalid heading) in PsdMessageDecoder.cpp
            /*TODO3: check tree whether is NULL or not*/
            if (NULL == PsdMap::getInstance()->getTree())
            {
                /*TODO4: find CurSegId success*/
                pthread_mutex_lock(&decoderThreadMutex);
                CurSegId = PsdMap::getInstance()->curIdIsInList()->preSegmentId;
                pthread_mutex_unlock(&decoderThreadMutex);

                /*TODO5: mapCreate*/
                if (-1 != CurSegId)
                {
                    PsdMap::getInstance()->mapCreate();
                    //TODO6: record lastSegmentId = curSegmentId, lastSize = vPsdMap.size()
                    lastSegmentId = PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId;
                    lastSize = PsdMessageDecoder::getInstance()->getVPsdMap().size();
                }
            }
            else
            {
                /*trigger mapUpdate*/
                if (( PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId !=  lastSegmentId) && (lastSize !=  PsdMessageDecoder::getInstance()->getVPsdMap().size()))
                {
                    PsdMap::getInstance()->mapUpdate();
                    //TODO6: record lastSegmentId = curSegmentId, lastSize = vPsdMap.size()
                    lastSegmentId =  PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId;
                    lastSize = PsdMessageDecoder::getInstance()->getVPsdMap().size();
                }
            }
        }
        else
        {
            /*TODO: clear tree + clearList in pPsdUsageActive == false case*/
            if (NULL != PsdMap::getInstance()->getTree())
            {
                PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
            }
            PsdMessageDecoder::getInstance()->segmentManager(false);
        }
    }
}
