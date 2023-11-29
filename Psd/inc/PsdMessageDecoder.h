/*********************************************************************************
 * Copyright (c) 202x Cariad China. All rights reserved.
 * FileName:	 PsdMessageDecoder.h
 * Author: 	     ZhaoZijia
 * Version :	 Ver0.1
 * Date:		 2023-11-03
 * Description: Psd raw data to be got and calculated.
 *
 *********************************************************************************/

#ifndef _PSDMESSAGEDECODER_H_
#define _PSDMESSAGEDECODER_H_

/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include <iostream>
#include <cstdint>
#include <vector>
#include <pthread.h>

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/
 const double HeadingAccuracyThreshold = 4.5;
 
/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/
typedef enum eRoadSegmentClass{
    RoadClass_Unkown = 0,
    RoadClass_highway = 1,
    RoadClass_Non_urban = 2,
    RoadClass_Urban = 3
}RoadSegmentClass;

//Psd04RoadClass
typedef enum ePsd04RoadClass{
    PrivateRoad = 0,
    LocalRoad = 1,
    CountyRoad = 2,
    NationalRoad = 3,
    ProvincialRoad = 4,
    Expressway = 5,
    Init = 7
}Psd04RoadClass;

//NodeAttribute
typedef enum NodeAttribute{
    RootSegment = 1,
    ParentSegment = 2,
    CurSegment = 3,
    ChildSegment = 4,
    RootAndCurSegment
}e_NodeAttribute;

//Position Length Error
typedef enum PosLengthErr{
    Pos_Init = 0,
    Pos_0mTo2m = 1,
    Pos_2mTo5m = 2,
    Pos_5mTo10m = 3,
    Pos_10mTo20m = 4,
    Pos_20mTo50m = 5,
    Over50m = 6,
    OffRoad = 7
}e_PosLengthErr;

//information about the separation zone
typedef enum StructSeparate
{
    NoSeperation = 0, 
    StructuralSeperation = 1,
    SeperationButNoStructural = 2,
    NoInfo = 3
}e_StructSeparate;

//distance
typedef struct Offset{
    double distanceX;
    double distanceY;
}tOffset;

//Coordinates Point
typedef struct Coordinates{
    double latitude;        //North to be +, South to be -
	double longitude;    //East to be +, West to be -
}tCoordinates;

//PsdMapData
typedef	struct PsdMapData{
	/*from PSD_04*/
	uint8_t preSegmentId;                             //predicted segment identifier
	uint8_t prevSegmentId;                          //the previous identifier of segment
    uint16_t preSegTotalLength;                 //total segment length
    Psd04RoadClass psd04RoadClass;     //the road class of every segments
	double  endCurvature;		                      //end curvature
    bool       signEndCurvature;                    //positive or negative sign on endCurvature, 0-positive, 1-negative
	bool       mpp;                                                //most posibile path of HV drived
	bool       sp;                                                     //straight path
	bool	   segmentIsComplete;                //integrity of PSD_04
	double  startCurvature;	                          //start curvature
    bool       signStartCurvature;                  //positive or negative sign on startCurvature, 0-positive, 1-negative
	bool       branchDirection;	                      //branching direction relative to the previous segment at the branch point, 0-right, 1-left 
	double  branchAngle; 	                          //branching angle relative to the previous segment at the branch point

	/*extra needed*/
    double accumulateBranchAngle;        //indicates the branching angle of each segment with respect to the HV's segment  
    tOffset accumulateXY;                              //indicates the offset of each segment with respect to the HV's position  
	bool     segIsInTree;                                     //identifies that segment has been grouped into the tree
	e_NodeAttribute	 nodeAttribute;         //identifies that segment is root, parent, current, child
	tCoordinates  startCoordinate;             //starting coordinate for each segments, current segment endpoint = next segment startpoint
	tCoordinates  endCoordinate;               //ending coordinate for each segments
    std::vector<struct Coordinates> vSampleCoord;//each sampled latitude and longitude coordinate in the curve case, the storage order should be from start to end
    e_StructSeparate structSeparate;        //information about the separation zone
	uint8_t psdAttributSegmentID;            //PSD_Attribut_Segment_ID, corresponding PreSegmentId, from PSD_06
    uint8_t psdAttribut1ID;                            //PSD_Attribut_1_ID, monitor Attribute ID == 4, from PSD_05  
    uint8_t psdAttribut1Wert;                       //PSD_Attribut_1_Wert, from PSD_05 
    uint8_t psdAttribut2ID;                            //PSD_Attribut_2_ID, monitor Attribute ID == 4, from PSD_05
    uint8_t psdAttribut2Wert;                      //PSD_Attribut_2_Wert, from PSD_05
    uint8_t psdAttribut3ID;                           //PSD_Attribut_3_ID, monitor Attribute ID == 4, from PSD_06
    uint8_t psdAttribut3Wert;                     //PSD_Attribut_3_Wert, from PSD_06
    uint8_t psdAttribut4ID;                          //PSD_Attribut_4_ID, monitor Attribute ID == 4, from PSD_06
    uint8_t psdAttribut4Wert;                     //PSD_Attribut_4_Wert, from PSD_06
    uint8_t psdAttribut5ID;                          //PSD_Attribut_5_ID, monitor Attribute ID == 4, from PSD_06
    uint8_t psdAttribut5Wert;                    //PSD_Attribut_5_Wert, from PSD_06
}tPsdMapData;

//SelfSegment
typedef struct SelfSegment{
    /*from PSD_05*/
	uint8_t	curSegmentId;                     //the segmentId where HV is currently located
	uint8_t curRemainLength;             //the remain length of HV current segment
	bool    posIsUnique;                           //indicates whether the location is unique, whether HV's position is consistent with the current segment, default:0
    e_PosLengthErr  posLengthErr;   //longitudinal errors in positioning, default:0
    /*extra needed*/
    uint8_t lastSegmentId;                    //for judging whether update Map or not, what time to save it?---after mapCreate and mapUpdate
    tCoordinates hvCoordinate;          //getHvPosition() from receiver
    double hvHeading;                            //getHvHeading() from receiver
}tSelfSegment;
/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: extern
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/
 
/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
class PsdMessageDecoder{
public:
    /**
     * @brief Get the Instance object
     * @return PsdMessageDecoder* 
     */
    static PsdMessageDecoder* getInstance();

    tSelfSegment hvSegment;                                         /** <  HV's segment information from PSD_05*/
    
    tPsdMapData PsdMapData;                                       /** <  each segment information*/
    
    std::vector<struct PsdMapData *> vPsdMap;     /** <  container for storing information about each segment*/
    
    pthread_mutex_t decoderThreadMutex;             /** <  Mutex for PsdMessageDecoder thread*/
    
    /**
     * @brief Putting PsdMapData into container when PsdUsageActive is true, clearing the container when PsdUsageActive is false
     * @param PsdUsageActive (true Psd active) 
     * @param PsdUsageActive (false Psd inactive)
     */
    void segmentManager(bool PsdUsageActive);

    /**
     * @brief Find the segment info with the specified id  in the list
     * @param KnownId 
     * @return std::vector<struct PsdMapData *>::iterator
     */
    std::vector<struct PsdMapData *>::iterator findSegmentById(uint8_t KnownId);
//private:
    /**
     * @brief Calculate PSD_04 data
     */
    void calcPsd04Data();

    /**
     * @brief Convert start && end Curvature from uint8_t to double type
     */
    void convertCurvature();

    /**
     * @brief Convert branchAngle from uint8_t to double type
     */
    void convertBranchAngle();

    /**
     * @brief PsdMapData emplace in container
     */
    void pushInList();

    /**
     * @brief PsdMapData erase out container 
     * @param position (the position in the container to be deleted)
     */
    void popUpList(std::vector<struct PsdMapData *>::iterator position);

    /**
     * @brief Clear the container
     */
    void clearList();

    /**
     * @brief Check StructSeparate info and save in container
     */
    void saveAttributToList();

    /**
     * @brief Get the Self Segment object
     * @return tSelfSegment 
     */
    tSelfSegment getSelfSegment();

    /**
     * @brief Set the Self Segment object
     * @param SelfSegment 
     */
    void setSelfSegment(tSelfSegment SelfSegment);

    /**
     * @brief Set the Psd Map Data object
     * @param psdMapData 
     */
    void setPsdMapData(tPsdMapData psdMapData);

    /**
     * @brief Get the container with PsdMapData
     * @return std::vector<struct PsdMapData *>& 
     */
    std::vector<struct PsdMapData *>& getVPsdMap();

    /**
     * @brief  Construct a new PsdMessageDecoder object
     */
    PsdMessageDecoder(/* args */);

    /**
     * @brief Destroy the PsdMessageDecoder object
     */
    ~PsdMessageDecoder();

    static PsdMessageDecoder* pInstance;  /**<A pointer used to return the object of  the class of PsdMessageDecoder*/
};

void* PsdMessageDecoderRun(void *arg);

#endif /*_PSDMESSAGEDECODER_H_*/

