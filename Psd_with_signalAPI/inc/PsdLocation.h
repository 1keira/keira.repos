/*********************************************************************************
 * Copyright (c) 202x Cariad China. All rights reserved.
 * FileName:	 PsdLocation.h
 * Author: 	     ZhaoZijia
 * Version :	 Ver0.1
 * Date:		 2023-11-03
 * Description: get diagnotics parameter, init config, pthread_create, PsdLocation relative calculation etc.
 *
 *********************************************************************************/

#ifndef _PSDLOCATION_H_
#define _PSDLOCATION_H_

/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include "PsdMessageDecoder.h"
#include "PsdMap.h"
#include "Haversine.h"
#include "GeometricCalc.h"

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS: global
 *---------------------------------------------------------------------------*/
//eRelativePosition
typedef enum eRelativePosition
{
    Pos_Unclassified = 0,
    Pos_Ahead = 1,
    Pos_Behind = 2,
    Pos_Left = 3,
    Pos_Right = 4
}RelativePosition;

//eRelativeDirection
typedef enum eRelativeDirection_PSD
{
    PSD_Dir_Unclassified = 0, 
    PSD_Dir_Unreachable = 1,
    PSD_Dir_Oncoming = 2,
    PSD_Dir_Ahead = 3,
    PSD_Dir_ComingFromLeft = 4, 
    PSD_Dir_ComingFromRight = 5, 
    PSD_Dir_ComingFromBehind = 6,
    PSD_Dir_AwayFromLeft = 7, 
    PSD_Dir_AwayFromRight = 8,
    PSD_Dir_AwayFromBehind = 9
}RelativeDirection_PSD;

//eEventClassification
typedef enum eEventClassification
{
	Instantanceous_Event = 0,
	Static_Event                     = 1,
	Dynamic_Event              = 2
}EventClassification;

//sData2EventList
typedef struct sData2EventList{
	bool PsdAvailable;                                   /** <  psd whether available or not*/
	bool MPP;                                                    /** <  most posible path*/
    float dis2Event;                                         /** <  real road distance between Hv and Ro*/
    RelativePosition relativePos;              /** <  Ro relative Hv*/
    RoadSegmentClass roadSegClass;   /** <  road segment class*/
    bool RvRelevancy;                                   /** < Ro is on the driving route of Hv or has potential threat to Hv*/
	float HvDTIP;                                              /** <  distance from Hv's position to intersection*/
	float RvDTIP;                                               /** <  distance from Ro's position to intersection*/
}Data2EventList;

//sData2Location
typedef struct sData2Location{
	Position3D_D RoPos;
	double headingDelta;
    float RvSpeed;
    EventClassification eventClassify;     /** <  the status of remote object */
}Data2Location;

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: extern
 *---------------------------------------------------------------------------*/
extern double pLateralDistTolerance;    /** <  p_lateral_dist_tolerance*/
extern double pRelativePositionAngle; /** <  p_relative_position_angle, default value == 45 degrees*/ 
extern double pRelativeDirection;           /** <  p_relative_direction, default value == 45 degrees*/
extern double pStationaryThreshold;    /** <  p_StationaryThreshold*/           
/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/
const double pPsdValidDistance = 250.0;

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
class PsdLocation{
public:
    /**
     * @brief Get the Instance object
     * @return PsdLocation* 
     */
    static PsdLocation *getInstance();

    /**
     * @brief Start the entire psd module
     */
    void start();

    /**
     * @brief Get the Psd Ro Location object
     * @param data2Location 
     * @return Data2EventList 
     */
    Data2EventList getPsdRoLocation(Data2Location data2Location);

    /**
     * @brief Get the Event Distance object (reserved for V2I)
     */
    void getEventDistance();

    /**
     * @brief Access private PsdLocation for gtest 
     * @return PsdLocation* 
     */
    static  PsdLocation *testPsdLocation();

    /**
     * @brief Access private ~PsdLocation for gtest 
     */
    static void testPsdLocation(PsdLocation *pInstance);

    /**
     * @brief Test PsdAvailable for gtest
     * @return true 
     * @return false 
     */
    bool testgetPsdAvailable();

    /**
     * @brief Test calcRoadSegmentClass
     * @return RoadSegmentClass 
     */
    RoadSegmentClass testcalcRoadSegmentClass();

    /**
     * @brief Test accumulateChildsLength for gtest
     * @param Node 
     * @return float 
     */
    float testaccumulateChildsLength(struct TreeNode *Node);
    
private:

    pthread_t decoderThread;                        /** <  decoderThread's Id*/

    pthread_t mapThread;                                /** <  mapThread's Id*/

    uint8_t mRoMatchedSegId;                       /** <  Ro Matched Segment Id*/

    struct TreeNode *mRoMatchedNode;   /** <  Ro Matched Segment Node*/

    Data2EventList mData2EventList;           /** <  Data return to EventList*/

    bool mIsMatch;                                                /** <  Ro whether matched on HV's segments, default value == false*/

    RelativeDirection_PSD RelativeDir;        /** <  Ro relative Hv*/

    /**
     * @brief Initialice Psd relative Data
     */
    void initPsdData();

    /**
     * @brief Create a Decoder Thread object
     */
    void createDecoderThread();

    /**
     * @brief Create a Map Thread object
     */
    void createMapThread();

    /**
     * @brief Get the Psd Available object (Psd whether available or not)
     * @return true (Psd is available)
     * @return false (Psd is not available)
     */
    bool getPsdAvailable();

    /**
     * @brief Using Ro matched predictive segmentId to judge Ro whether is driving on the mpp segment of HV or not
     * @param KnownId 
     * @return true 
     * @return false 
     */
    bool getMPP(uint8_t KnownId);

    /**
     * @brief Ro match Segment
     * @param RoPoint 
     * @return true (Ro matched one segment)
     * @return false (Ro not matched one segment)
     */
    bool RoMatchSegment(Position3D_D RoPoint);

    /**
     * @brief Hv's Road Class
     * @return RoadSegmentClass 
     */
    RoadSegmentClass calcRoadSegmentClass();

    /**
     * @brief Ro Relative Position to Hv
     * @param data2Location 
     * @return RelativePosition 
     */
    RelativePosition calcRelativePosition(Data2Location data2Location);

    /**
     * @brief Ro Relative Direction to Hv
     * @param data2Location 
     * @return Ro Relative Direction to Hv
     */
    RelativeDirection_PSD calcRelativeDirection(Data2Location data2Location);

    /**
     * @brief Ro Relevancy to Hv
     * @param data2Location 
     * @return true (relevant)
     * @return false (irrelevant)
     */
    bool calcRvRelevancy(Data2Location data2Location);

    /**
     * @brief real road distance between Hv and Ro
     * @param data2Location 
     * @return float (unit: meter, accuracy: float)
     */
    float calcDistanceToEvent(Data2Location data2Location);

    /**
     * @brief DTIP Hv Distance to Intersection
     * @return float (unit: meter, accuracy: float)
     */
    float calcHvDis2Intersection();

    /**
     * @brief DTIP Rv Distance to Intersection
     * @param data2Location 
     * @return float (unit: meter, accuracy: float)
     */
    float calcRoDis2Intersection(Data2Location data2Location);

    /**
     * @brief Accumulate childnodes's preSegmentLength
     * @param Node 
     * @return float (unit: meter, accuracy: float)
     */
    float accumulateChildsLength(struct TreeNode *Node);
    
    /**
     * @brief Construct a new PsdLocation object
     */
    PsdLocation(/* args */);

    /**
     * @brief Destroy the PsdLocation object
     */
    ~PsdLocation();

    static PsdLocation *pInstance;  /**<A pointer used to return the object of  the class of PsdLocation*/
};

#endif /* _PSDLOCATION_H_ */
