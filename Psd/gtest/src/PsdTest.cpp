#include <gtest/gtest.h>
#include <cstdint>
#include <cmath>
#include <cerrno>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "../../inc/PsdMap.h"
#include "../../inc/PsdLocation.h"
#include "../../inc/PsdMessageDecoder.h"

#define BRANCH_ANGLE_SCALE 1.417323

/**
 * @brief PsdMapTest
 */

class PsdMapTest : public testing::Test
{
protected:
    PsdMap *pInstance;
    PsdMap *getInstance()
    {
        if (NULL == pInstance)
        {
            pInstance = new PsdMap();
        }
        return pInstance;
    }

    void SetUp()
    {
        pInstance = NULL;
    }
    void TerDown()
    {
        delete pInstance;
    }
};

#if 0
/*mapCreate*/
/*basic intersection with straight path: heading == 0.0*/
TEST_F(PsdMapTest, mapCreateAndcalcCoordinateWithoutHeading)
{
    struct PsdMapData MapData_1, MapData_2, MapData_3, MapData_4;
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 200;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0;
    MapData_1.branchDirection = 0;
    MapData_1.branchAngle = 0.0;
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 100; //segTotalLength == 200, drivedLength = 100
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 0.0;
    curSegment.hvCoordinate = {31.260682, 121.303785};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's child Segment, preSegmentId == 4, prevSegmentId = 3
    MapData_2.preSegmentId = 4;
    MapData_2.prevSegmentId = 3;
    MapData_2.preSegTotalLength = 200;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 0;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -90.0;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's child Segment, preSegmentId == 5, prevSegmentId = 3
    MapData_3.preSegmentId = 5;
    MapData_3.prevSegmentId = 3;
    MapData_3.preSegTotalLength = 200;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 0.0;
    MapData_3.mpp = 1;
    MapData_3.sp = 1;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 0.0;
    MapData_3.branchDirection = 0; //ahead
    MapData_3.branchAngle = 0.0;
    MapData_3.segIsInTree = false;

    //MapData_4 as HV's child Segment, preSegmentId == 6, prevSegmentId = 3
    MapData_4.preSegmentId = 6;
    MapData_4.prevSegmentId = 3;
    MapData_4.preSegTotalLength = 200;
    MapData_4.psd04RoadClass = CountyRoad;
    MapData_4.endCurvature = 0.0;
    MapData_4.mpp = 0;
    MapData_4.sp = 1;
    MapData_4.segmentIsComplete = 1;
    MapData_4.startCurvature = 0;
    MapData_4.branchDirection = 0; //right
    MapData_4.branchAngle = 90.0;
    MapData_4.segIsInTree = false;
    
    /*basic intersection and child segment is curve*/
    struct PsdMapData MapData_5, MapData_6;
    //MapData_5 as HV's child Segment, preSegmentId = 7, prevSegmentId = 5
    MapData_5.preSegmentId = 7;
    MapData_5.prevSegmentId = 5;
    MapData_5.preSegTotalLength = 71;
    MapData_5.psd04RoadClass = CountyRoad;
    MapData_5.endCurvature = 0.0;
    MapData_5.mpp = 1;
    MapData_5.sp = 1;
    MapData_5.segmentIsComplete = 1;
    MapData_5.startCurvature = 0.0;
    MapData_5.branchDirection = 0; //ahead
    MapData_5.branchAngle = 0.0;
    MapData_5.segIsInTree = false;

    //MapData_6 as HV's child Segment, preSegmentId = 8, prevSegmentId = 7
    MapData_6.preSegmentId = 8;
    MapData_6.prevSegmentId = 7;
    MapData_6.preSegTotalLength = 16;
    MapData_6.psd04RoadClass = CountyRoad;
    MapData_6.endCurvature =  -1.0 / 63.3396;  //left
    MapData_6.mpp = 1;
    MapData_6.sp = 0;
    MapData_6.segmentIsComplete = 1;
    MapData_6.startCurvature = -1.0 / 7.4293;  //left
    MapData_6.branchDirection = 1; //left
    MapData_6.branchAngle = -34.37;
    MapData_6.segIsInTree = false;
    //save to database: segment 3 4 5 6 7 8
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_4);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_5);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_6);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }

    //trigger mapCreate's internal function
    PsdMap::getInstance()->mapCreate();
    
    //HV's Coordinate: HV current coordinate(31.260682, 121.303785)
    double Threshold = 2.5e-5;
    tCoordinates startCoordinate_1 = {31.259779, 121.303785};  //expected coordinate: HV's south 100meter
    double startCoordLat_1_absValue = std::fabs(startCoordinate_1.latitude - MapData_1.startCoordinate.latitude);
    double startCoordLon_1_absValue = std::fabs(startCoordinate_1.longitude - MapData_1.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_1_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_1_absValue);
    printf("[%s] [%d]: startCoordLon_1_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_1_absValue);
    EXPECT_LT(startCoordLat_1_absValue, Threshold);
    EXPECT_LT(startCoordLon_1_absValue, Threshold);

    tCoordinates endCoordinate_1 = {31.261579, 121.303785};   //expected coordinate: HV's north 100meter
    double endCoordLat_1_absValue = std::fabs(endCoordinate_1.latitude - MapData_1.endCoordinate.latitude);
    double endCoordLon_1_absValue = std::fabs(endCoordinate_1.longitude - MapData_1.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_1_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_1_absValue);
    printf("[%s] [%d]: endCoordLon_1_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_1_absValue);
    EXPECT_LT(endCoordLat_1_absValue, Threshold);
    EXPECT_LT(endCoordLon_1_absValue, Threshold);

     //HV's child Coordinate: preSegmentId == 4
    tCoordinates startCoordinate_2 = {31.261579, 121.303785};   //expected coordinate
     double startCoordLat_2_absValue = std::fabs(startCoordinate_2.latitude - MapData_2.startCoordinate.latitude);
    double startCoordLon_2_absValue = std::fabs(startCoordinate_2.longitude - MapData_2.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_2_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_2_absValue);
    printf("[%s] [%d]: startCoordLon_2_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_2_absValue);    
    EXPECT_LT(startCoordLat_2_absValue, Threshold);
    EXPECT_LT(startCoordLon_2_absValue, Threshold);

    tCoordinates endCoordinate_2 = {31.261579, 121.301678};   //expected coordinate: startCoordinate's west 200meter
    double endCoordLat_2_absValue = std::fabs(endCoordinate_2.latitude - MapData_2.endCoordinate.latitude);
    double endCoordLon_2_absValue = std::fabs(endCoordinate_2.longitude - MapData_2.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_2_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_2_absValue);
    printf("[%s] [%d]: endCoordLon_2_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_2_absValue);    
    EXPECT_LT(endCoordLat_2_absValue, Threshold);
    EXPECT_LT(endCoordLon_2_absValue, Threshold);

    //HV's child Coordinate: preSegmentId == 5
    tCoordinates startCoordinate_3 = {31.261579, 121.303785};   //expected coordinate
    double startCoordLat_3_absValue = std::fabs(startCoordinate_3.latitude - MapData_3.startCoordinate.latitude);
    double startCoordLon_3_absValue = std::fabs(startCoordinate_3.longitude - MapData_3.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_3_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_3_absValue);
    printf("[%s] [%d]: startCoordLon_3_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_3_absValue);        
    EXPECT_LT(startCoordLat_3_absValue, Threshold);
    EXPECT_LT(startCoordLon_3_absValue, Threshold);

    tCoordinates endCoordinate_3 = {31.263393, 121.303785};   //expected coordinate: startCoordinate's north 200meter
    double endCoordLat_3_absValue = std::fabs(endCoordinate_3.latitude - MapData_3.endCoordinate.latitude);
    double endCoordLon_3_absValue = std::fabs(endCoordinate_3.longitude - MapData_3.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_3_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_3_absValue);
    printf("[%s] [%d]: endCoordLon_3_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_3_absValue);     
    EXPECT_LT(endCoordLat_3_absValue, Threshold);
    EXPECT_LT(endCoordLon_3_absValue, Threshold);

    //HV's child Coordinate: preSegmentId == 6
    tCoordinates startCoordinate_4 = {31.261579, 121.303785};   //expected coordinate
    double startCoordLat_4_absValue = std::fabs(startCoordinate_4.latitude - MapData_4.startCoordinate.latitude);
    double startCoordLon_4_absValue = std::fabs(startCoordinate_4.longitude - MapData_4.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_4_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_4_absValue);
    printf("[%s] [%d]: startCoordLon_4_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_4_absValue);   
    EXPECT_LT(startCoordLat_4_absValue, Threshold);
    EXPECT_LT(startCoordLon_4_absValue, Threshold);

    tCoordinates endCoordinate_4 = {31.261579, 121.305885};   //expected coordinate: startCoordinate's east 200meter
    double endCoordLat_4_absValue = std::fabs(endCoordinate_4.latitude - MapData_4.endCoordinate.latitude);
    double endCoordLon_4_absValue = std::fabs(endCoordinate_4.longitude - MapData_4.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_4_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_4_absValue);
    printf("[%s] [%d]: endCoordLon_4_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_4_absValue);   
    EXPECT_LT(endCoordLat_4_absValue, Threshold);
    EXPECT_LT(endCoordLon_4_absValue, Threshold);

    //HV's child's Coordinate: preSegmentId = 7
    tCoordinates startCoordinate_5 = {31.263393, 121.303785};   //expected coordinate
    double startCoordLat_5_absValue = std::fabs(startCoordinate_5.latitude - MapData_5.startCoordinate.latitude);
    double startCoordLon_5_absValue = std::fabs(startCoordinate_5.longitude - MapData_5.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_5_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_5_absValue);
    printf("[%s] [%d]: startCoordLon_5_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_5_absValue);   
    EXPECT_LT(startCoordLat_5_absValue, Threshold);
    EXPECT_LT(startCoordLon_5_absValue, Threshold);

    tCoordinates endCoordinate_5 = {31.264035,121.303784};   //expected coordinate
    double endCoordLat_5_absValue = std::fabs(endCoordinate_5.latitude - MapData_5.endCoordinate.latitude);
    double endCoordLon_5_absValue = std::fabs(endCoordinate_5.longitude - MapData_5.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_5_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_5_absValue);
    printf("[%s] [%d]: endCoordLon_5_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_5_absValue);   
    EXPECT_LT(endCoordLat_5_absValue, Threshold);
    EXPECT_LT(endCoordLon_5_absValue, Threshold);

    //Child Coordinate of the curve : preSegmentId = 8
    Threshold = 1.5e-4;
    tCoordinates startCoordinate_6 = {31.264035,121.303784};   //expected coordinate
    double startCoordLat_6_absValue = std::fabs(startCoordinate_6.latitude - MapData_6.startCoordinate.latitude);
    double startCoordLon_6_absValue = std::fabs(startCoordinate_6.longitude - MapData_6.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_6_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_6_absValue);
    printf("[%s] [%d]: startCoordLon_6_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_6_absValue);   
    EXPECT_LT(startCoordLat_6_absValue, Threshold);
    EXPECT_LT(startCoordLon_6_absValue, Threshold);

    tCoordinates endCoordinate_6 = {31.264093, 121.303642};   //expected coordinate
    double endCoordLat_6_absValue = std::fabs(endCoordinate_6.latitude - MapData_6.endCoordinate.latitude);
    double endCoordLon_6_absValue = std::fabs(endCoordinate_6.longitude - MapData_6.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_6_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_6_absValue);
    printf("[%s] [%d]: endCoordLon_6_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_6_absValue);   
    EXPECT_LT(endCoordLat_6_absValue, Threshold);
    EXPECT_LT(endCoordLon_6_absValue, Threshold);
}

/*basic intersection in straight path: heading = 45.0*/
TEST_F(PsdMapTest, mapCreateAndcalcCoordinateWithHeading)
{
    struct PsdMapData MapData_1, MapData_2, MapData_3, MapData_4;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 283; //southwest of intersection
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0;
    MapData_1.branchDirection = 0;
    MapData_1.branchAngle = 0.0;
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 141; //segTotalLength == 283.294860, drivedLength = 141.647761
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 45.0;
    curSegment.hvCoordinate = {31.260679, 121.302732};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's child Segment, preSegmentId == 4, prevSegmentId = 3
    MapData_2.preSegmentId = 4;
    MapData_2.prevSegmentId = 3;
    MapData_2.preSegTotalLength = 285;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 0;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -89.53;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's child Segment, preSegmentId == 5, prevSegmentId = 3
    MapData_3.preSegmentId = 5;
    MapData_3.prevSegmentId = 3;
    MapData_3.preSegTotalLength = 285;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 0.0;
    MapData_3.mpp = 1;
    MapData_3.sp = 1;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 0.0;
    MapData_3.branchDirection = 1; //left
    MapData_3.branchAngle = -0.5;
    MapData_3.segIsInTree = false;

    //MapData_4 as HV's child Segment, preSegmentId == 6, prevSegmentId = 3
    MapData_4.preSegmentId = 6;
    MapData_4.prevSegmentId = 3;
    MapData_4.preSegTotalLength = 283;
    MapData_4.psd04RoadClass = CountyRoad;
    MapData_4.endCurvature = 0.0;
    MapData_4.mpp = 0;
    MapData_4.sp = 1;
    MapData_4.segmentIsComplete = 1;
    MapData_4.startCurvature = 0;
    MapData_4.branchDirection = 0; //right
    MapData_4.branchAngle = 90.0;
    MapData_4.segIsInTree = false;
    
    //save to database: segment 3 4 5 6 
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_4);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }

    //trigger mapCreate's internal function
    PsdMap::getInstance()->mapCreate();
    double Threshold = 3e-5;
    #if 0
    121.305885350,31.263414716 northeastern
    121.305885350,31.259779272 southeast
    121.301678696,31.263414716 northwestern
    121.301678696,31.259779272 southwest
    121.302732156,31.260679527 HV
    121.303785616,31.261579782 intersection(not change)
    #endif
    //HV's Coordinate: HV current coordinate(31.260679, 121.302732)
    tCoordinates startCoordinate_1 = {31.259779, 121.301678};  //expected coordinate: HV's southwest 141.647761meter, HV's startCoordinate
    double startCoordLat_1_absValue = std::fabs(startCoordinate_1.latitude - MapData_1.startCoordinate.latitude);
    double startCoordLon_1_absValue = std::fabs(startCoordinate_1.longitude - MapData_1.startCoordinate.longitude); 
    printf("[%s] [%d]: startCoordLat_1_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_1_absValue);
    printf("[%s] [%d]: startCoordLon_1_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_1_absValue);
    EXPECT_LT(startCoordLat_1_absValue, Threshold);
    EXPECT_LT(startCoordLon_1_absValue, Threshold);

    tCoordinates endCoordinate_1 = {31.261579, 121.303785};   //expected coordinate: HV's northwest 141.647099meter
    double endCoordLat_1_absValue = std::fabs(endCoordinate_1.latitude - MapData_1.endCoordinate.latitude);
    double endCoordLon_1_absValue = std::fabs(endCoordinate_1.longitude - MapData_1.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_1_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_1_absValue);
    printf("[%s] [%d]: endCoordLon_1_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_1_absValue);
    EXPECT_LT(endCoordLat_1_absValue, Threshold);
    EXPECT_LT(endCoordLon_1_absValue, Threshold);

     //HV's child Coordinate: preSegmentId == 4
    tCoordinates startCoordinate_2 = {31.261579, 121.303785};   //expected coordinate
     double startCoordLat_2_absValue = std::fabs(startCoordinate_2.latitude - MapData_2.startCoordinate.latitude);
    double startCoordLon_2_absValue = std::fabs(startCoordinate_2.longitude - MapData_2.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_2_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_2_absValue);
    printf("[%s] [%d]: startCoordLon_2_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_2_absValue);    
    EXPECT_LT(startCoordLat_2_absValue, Threshold);
    EXPECT_LT(startCoordLon_2_absValue, Threshold);

    tCoordinates endCoordinate_2 = {31.263414, 121.301678};   //expected coordinate: startCoordinate's northwestern 285.227904meter
    double endCoordLat_2_absValue = std::fabs(endCoordinate_2.latitude - MapData_2.endCoordinate.latitude);
    double endCoordLon_2_absValue = std::fabs(endCoordinate_2.longitude - MapData_2.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_2_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_2_absValue);    //0.000029
    printf("[%s] [%d]: endCoordLon_2_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_2_absValue);  //0.000016  
    EXPECT_LT(endCoordLat_2_absValue, Threshold);
    EXPECT_LT(endCoordLon_2_absValue, Threshold);

    //HV's child Coordinate: preSegmentId == 5
    tCoordinates startCoordinate_3 = {31.261579, 121.303785};   //expected coordinate
    double startCoordLat_3_absValue = std::fabs(startCoordinate_3.latitude - MapData_3.startCoordinate.latitude);
    double startCoordLon_3_absValue = std::fabs(startCoordinate_3.longitude - MapData_3.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_3_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_3_absValue);
    printf("[%s] [%d]: startCoordLon_3_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_3_absValue);        
    EXPECT_LT(startCoordLat_3_absValue, Threshold);
    EXPECT_LT(startCoordLon_3_absValue, Threshold);

    tCoordinates endCoordinate_3 = {31.263414, 121.305885};   //expected coordinate: startCoordinate's northwest 284.843019meter
    double endCoordLat_3_absValue = std::fabs(endCoordinate_3.latitude - MapData_3.endCoordinate.latitude);
    double endCoordLon_3_absValue = std::fabs(endCoordinate_3.longitude - MapData_3.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_3_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_3_absValue);    //0.000035
    printf("[%s] [%d]: endCoordLon_3_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_3_absValue);     
    EXPECT_LT(endCoordLat_3_absValue, Threshold);
    EXPECT_LT(endCoordLon_3_absValue, Threshold);

    //HV's child Coordinate: preSegmentId == 6
    tCoordinates startCoordinate_4 = {31.261579, 121.303785};   //expected coordinate
    double startCoordLat_4_absValue = std::fabs(startCoordinate_4.latitude - MapData_4.startCoordinate.latitude);
    double startCoordLon_4_absValue = std::fabs(startCoordinate_4.longitude - MapData_4.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_4_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_4_absValue);
    printf("[%s] [%d]: startCoordLon_4_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_4_absValue);   
    EXPECT_LT(startCoordLat_4_absValue, Threshold);
    EXPECT_LT(startCoordLon_4_absValue, Threshold);

    tCoordinates endCoordinate_4 = {31.259779, 121.305885};   //expected coordinate: startCoordinate's southeast 283.294805meter
    double endCoordLat_4_absValue = std::fabs(endCoordinate_4.latitude - MapData_4.endCoordinate.latitude);
    double endCoordLon_4_absValue = std::fabs(endCoordinate_4.longitude - MapData_4.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_4_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_4_absValue);
    printf("[%s] [%d]: endCoordLon_4_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_4_absValue);   
    EXPECT_LT(endCoordLat_4_absValue, Threshold);
    EXPECT_LT(endCoordLon_4_absValue, Threshold);
}

/*HV's root, parent, childs in straight path*/
TEST_F(PsdMapTest, mapCreateAndcalcCoordinateWithMultiLayer)
{
    struct PsdMapData MapData_1, MapData_2, MapData_3, MapData_4, MapData_5, MapData_6, MapData_7, MapData_8;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; //segTotalLength = 254, drivedLength = 69
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's parent Segment, preSegmentId = 2, prevSegmentId = 10
    MapData_2.preSegmentId = 2;
    MapData_2.prevSegmentId = 10;
    MapData_2.preSegTotalLength = 176;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 0;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -0.01;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's root Segment, preSegmentId = 10, prevSegmentId = 11
    MapData_3.preSegmentId = 10;
    MapData_3.prevSegmentId = 10;
    MapData_3.preSegTotalLength = 200;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 0.0;
    MapData_3.mpp = 1;
    MapData_3.sp = 1;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 0.0;
    MapData_3.branchDirection = 0;
    MapData_3.branchAngle = 0.0;
    MapData_3.segIsInTree = false;

    //MapData_4 as HV's child Segment, preSegmentId = 4, prevSegmentId = 3
    MapData_4.preSegmentId = 4;
    MapData_4.prevSegmentId = 3;
    MapData_4.preSegTotalLength = 78;
    MapData_4.psd04RoadClass = CountyRoad;
    MapData_4.endCurvature = 0.0;
    MapData_4.mpp = 1;
    MapData_4.sp = 1;
    MapData_4.segmentIsComplete = 1;
    MapData_4.startCurvature = 0;
    MapData_4.branchDirection = 0; //right
    MapData_4.branchAngle = +0.01;
    MapData_4.segIsInTree = false;

    //MapData_5 as HV's child Segment, preSegmentId = 5, prevSegmentId = 4
    MapData_5.preSegmentId = 5;
    MapData_5.prevSegmentId = 4;
    MapData_5.preSegTotalLength = 254;
    MapData_5.psd04RoadClass = CountyRoad;
    MapData_5.endCurvature = 0.0;
    MapData_5.mpp = 0;
    MapData_5.sp = 1;
    MapData_5.segmentIsComplete = 1;
    MapData_5.startCurvature = 0;
    MapData_5.branchDirection = 0; //right
    MapData_5.branchAngle = +90.06;
    MapData_5.segIsInTree = false;
        
    //MapData_6 as HV's child Segment, preSegmentId = 6, prevSegmentId = 4
    MapData_6.preSegmentId = 6;
    MapData_6.prevSegmentId = 4;
    MapData_6.preSegTotalLength = 254;
    MapData_6.psd04RoadClass = CountyRoad;
    MapData_6.endCurvature = 0.0;
    MapData_6.mpp = 1;
    MapData_6.sp = 1;
    MapData_6.segmentIsComplete = 1;
    MapData_6.startCurvature = 0;
    MapData_6.branchDirection = 0; //right
    MapData_6.branchAngle = +0.02;
    MapData_6.segIsInTree = false;

    //MapData_7 as HV's child Segment, preSegmentId = 7, prevSegmentId = 4
    MapData_7.preSegmentId = 7;
    MapData_7.prevSegmentId = 4;
    MapData_7.preSegTotalLength = 254;
    MapData_7.psd04RoadClass = CountyRoad;
    MapData_7.endCurvature = 0.0;
    MapData_7.mpp = 0;
    MapData_7.sp = 1;
    MapData_7.segmentIsComplete = 1;
    MapData_7.startCurvature = 0;
    MapData_7.branchDirection = 1; //left
    MapData_7.branchAngle = -90.05;
    MapData_7.segIsInTree = false;

    //MapData_8 as HV's child Segment, preSegmentId = 8, prevSegmentId = 6
    MapData_8.preSegmentId = 8;
    MapData_8.prevSegmentId = 6;
    MapData_8.preSegTotalLength = 103;
    MapData_8.psd04RoadClass = CountyRoad;
    MapData_8.endCurvature = 0.0;
    MapData_8.mpp = 1;
    MapData_8.sp = 1;
    MapData_8.segmentIsComplete = 1;
    MapData_8.startCurvature = 0;
    MapData_8.branchDirection = 0; //right
    MapData_8.branchAngle = +0.01;
    MapData_8.segIsInTree = false;

    //save to database: segment 10, 2, 3, 4, 5, 6, 7, 8
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_4);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_5);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_6);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_7);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_8);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }

    //trigger mapCreate's internal function
    PsdMap::getInstance()->mapCreate();
    double Threshold = 5e-5;
    
    //HV's Coordinate: HV current coordinate(40.358150, 116.815109)
    tCoordinates startCoordinate_1 = {40.358768, 116.815100};  //expected coordinate: HV behind 69meter, HV's startCoordinate
    double startCoordLat_1_absValue = std::fabs(startCoordinate_1.latitude - MapData_1.startCoordinate.latitude);
    double startCoordLon_1_absValue = std::fabs(startCoordinate_1.longitude - MapData_1.startCoordinate.longitude); 
    printf("[%s] [%d]: startCoordLat_1_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_1_absValue);
    printf("[%s] [%d]: startCoordLon_1_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_1_absValue);
    EXPECT_LT(startCoordLat_1_absValue, Threshold);
    EXPECT_LT(startCoordLon_1_absValue, Threshold);

    tCoordinates endCoordinate_1 = {40.356480, 116.815134};   //expected coordinate: HV front 185meter, HV's endCoordinate
    double endCoordLat_1_absValue = std::fabs(endCoordinate_1.latitude - MapData_1.endCoordinate.latitude);
    double endCoordLon_1_absValue = std::fabs(endCoordinate_1.longitude - MapData_1.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_1_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_1_absValue);
    printf("[%s] [%d]: endCoordLon_1_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_1_absValue);
    EXPECT_LT(endCoordLat_1_absValue, Threshold);
    EXPECT_LT(endCoordLon_1_absValue, Threshold);

    //HV's parent Coordinate: preSegmentId == 2
    tCoordinates startCoordinate_2 = {40.360351, 116.815090};   //expected coordinate
    double startCoordLat_2_absValue = std::fabs(startCoordinate_2.latitude - MapData_2.startCoordinate.latitude);
    double startCoordLon_2_absValue = std::fabs(startCoordinate_2.longitude - MapData_2.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_2_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_2_absValue);
    printf("[%s] [%d]: startCoordLon_2_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_2_absValue);    
    EXPECT_LT(startCoordLat_2_absValue, Threshold);
    EXPECT_LT(startCoordLon_2_absValue, Threshold);

    tCoordinates endCoordinate_2 = {40.358768, 116.815100};   //expected coordinate
    double endCoordLat_2_absValue = std::fabs(endCoordinate_2.latitude - MapData_2.endCoordinate.latitude);
    double endCoordLon_2_absValue = std::fabs(endCoordinate_2.longitude - MapData_2.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_2_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_2_absValue);   
    printf("[%s] [%d]: endCoordLon_2_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_2_absValue); 
    EXPECT_LT(endCoordLat_2_absValue, Threshold);
    EXPECT_LT(endCoordLon_2_absValue, Threshold);

    //HV's root Coordinate: preSegmentId == prevSegmentId are 10
    tCoordinates startCoordinate_3 = {40.362152, 116.815078};   //expected coordinate
    double startCoordLat_3_absValue = std::fabs(startCoordinate_3.latitude - MapData_3.startCoordinate.latitude);
    double startCoordLon_3_absValue = std::fabs(startCoordinate_3.longitude - MapData_3.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_3_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_3_absValue);
    printf("[%s] [%d]: startCoordLon_3_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_3_absValue);        
    EXPECT_LT(startCoordLat_3_absValue, Threshold);
    EXPECT_LT(startCoordLon_3_absValue, Threshold);

    tCoordinates endCoordinate_3 = {40.360351, 116.815090};   //expected coordinate
    double endCoordLat_3_absValue = std::fabs(endCoordinate_3.latitude - MapData_3.endCoordinate.latitude);
    double endCoordLon_3_absValue = std::fabs(endCoordinate_3.longitude - MapData_3.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_3_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_3_absValue);
    printf("[%s] [%d]: endCoordLon_3_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_3_absValue);     
    EXPECT_LT(endCoordLat_3_absValue, Threshold);
    EXPECT_LT(endCoordLon_3_absValue, Threshold);

    //HV's child Coordinate: preSegmentId == 4
    tCoordinates startCoordinate_4 = {40.356480, 116.815134};   //expected coordinate
    double startCoordLat_4_absValue = std::fabs(startCoordinate_4.latitude - MapData_4.startCoordinate.latitude);
    double startCoordLon_4_absValue = std::fabs(startCoordinate_4.longitude - MapData_4.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_4_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_4_absValue);
    printf("[%s] [%d]: startCoordLon_4_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_4_absValue);   
    EXPECT_LT(startCoordLat_4_absValue, Threshold);
    EXPECT_LT(startCoordLon_4_absValue, Threshold);

    tCoordinates endCoordinate_4 = {40.355777, 116.815146};   //expected coordinate
    double endCoordLat_4_absValue = std::fabs(endCoordinate_4.latitude - MapData_4.endCoordinate.latitude);
    double endCoordLon_4_absValue = std::fabs(endCoordinate_4.longitude - MapData_4.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_4_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_4_absValue);
    printf("[%s] [%d]: endCoordLon_4_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_4_absValue);   
    EXPECT_LT(endCoordLat_4_absValue, Threshold);
    EXPECT_LT(endCoordLon_4_absValue, Threshold);

    //HV's child's child Coordinate: preSegmentId == 5
    tCoordinates startCoordinate_5 = {40.355777, 116.815146};   //expected coordinate
    double startCoordLat_5_absValue = std::fabs(startCoordinate_5.latitude - MapData_5.startCoordinate.latitude);
    double startCoordLon_5_absValue = std::fabs(startCoordinate_5.longitude - MapData_5.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_5_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_5_absValue);
    printf("[%s] [%d]: startCoordLon_5_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_5_absValue);   
    EXPECT_LT(startCoordLat_5_absValue, Threshold);
    EXPECT_LT(startCoordLon_5_absValue, Threshold);

    tCoordinates endCoordinate_5 = {40.355756, 116.812153};   //expected coordinate
    double endCoordLat_5_absValue = std::fabs(endCoordinate_5.latitude - MapData_5.endCoordinate.latitude);
    double endCoordLon_5_absValue = std::fabs(endCoordinate_5.longitude - MapData_5.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_5_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_5_absValue);
    printf("[%s] [%d]: endCoordLon_5_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_5_absValue);   
    EXPECT_LT(endCoordLat_5_absValue, Threshold);
    EXPECT_LT(endCoordLon_5_absValue, Threshold);

    //HV's child's child Coordinate: preSegmentId == 6
    tCoordinates startCoordinate_6 = {40.355777, 116.815146};   //expected coordinate
    double startCoordLat_6_absValue = std::fabs(startCoordinate_6.latitude - MapData_6.startCoordinate.latitude);
    double startCoordLon_6_absValue = std::fabs(startCoordinate_6.longitude - MapData_6.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_6_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_6_absValue);
    printf("[%s] [%d]: startCoordLon_6_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_6_absValue);   
    EXPECT_LT(startCoordLat_6_absValue, Threshold);
    EXPECT_LT(startCoordLon_6_absValue, Threshold);

    tCoordinates endCoordinate_6 = {40.353489, 116.815179};   //expected coordinate
    double endCoordLat_6_absValue = std::fabs(endCoordinate_6.latitude - MapData_6.endCoordinate.latitude);
    double endCoordLon_6_absValue = std::fabs(endCoordinate_6.longitude - MapData_6.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_6_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_6_absValue);
    printf("[%s] [%d]: endCoordLon_6_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_6_absValue);   
    EXPECT_LT(endCoordLat_6_absValue, Threshold);
    EXPECT_LT(endCoordLon_6_absValue, Threshold);

    //HV's child's child Coordinate: preSegmentId == 7
    tCoordinates startCoordinate_7 = {40.355777, 116.815146};   //expected coordinate
    double startCoordLat_7_absValue = std::fabs(startCoordinate_7.latitude - MapData_7.startCoordinate.latitude);
    double startCoordLon_7_absValue = std::fabs(startCoordinate_7.longitude - MapData_7.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_7_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_7_absValue);
    printf("[%s] [%d]: startCoordLon_7_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_7_absValue);   
    EXPECT_LT(startCoordLat_7_absValue, Threshold);
    EXPECT_LT(startCoordLon_7_absValue, Threshold);

    tCoordinates endCoordinate_7 = {40.355809, 116.818135};   //expected coordinate
    double endCoordLat_7_absValue = std::fabs(endCoordinate_7.latitude - MapData_7.endCoordinate.latitude);
    double endCoordLon_7_absValue = std::fabs(endCoordinate_7.longitude - MapData_7.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_7_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_7_absValue);
    printf("[%s] [%d]: endCoordLon_7_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_7_absValue);   
    EXPECT_LT(endCoordLat_7_absValue, Threshold);
    EXPECT_LT(endCoordLon_7_absValue, Threshold);

    //HV's child's child's child Coordinate: preSegmentId == 8
    tCoordinates startCoordinate_8 = {40.353489, 116.815179};   //expected coordinate
    double startCoordLat_8_absValue = std::fabs(startCoordinate_8.latitude - MapData_8.startCoordinate.latitude);
    double startCoordLon_8_absValue = std::fabs(startCoordinate_8.longitude - MapData_8.startCoordinate.longitude);
    printf("[%s] [%d]: startCoordLat_8_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_8_absValue);
    printf("[%s] [%d]: startCoordLon_8_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_8_absValue);   
    EXPECT_LT(startCoordLat_8_absValue, Threshold);
    EXPECT_LT(startCoordLon_8_absValue, Threshold);

    tCoordinates endCoordinate_8 = {40.352561, 116.815190};   //expected coordinate
    double endCoordLat_8_absValue = std::fabs(endCoordinate_8.latitude - MapData_8.endCoordinate.latitude);
    double endCoordLon_8_absValue = std::fabs(endCoordinate_8.longitude - MapData_8.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_8_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_8_absValue);
    printf("[%s] [%d]: endCoordLon_8_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_8_absValue);   
    EXPECT_LT(endCoordLat_8_absValue, Threshold);
    EXPECT_LT(endCoordLon_8_absValue, Threshold);
}

/*Only HV's current Segment in curve case*/
TEST_F(PsdMapTest, mapCreateAndcalcCoordinateWithCurve)
{
    struct PsdMapData MapData_1;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 200;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 1.0 / 46.6588;
    MapData_1.mpp = 1;
    MapData_1.sp = 0;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 1.0 / 47.3284;
    MapData_1.branchDirection = 0;
    MapData_1.branchAngle = 0.0; 
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 100; //segTotalLength == 200, drivedLength = 100
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 66.85;
    curSegment.hvCoordinate = {40.346799, 116.812289};  //located at Zuoti Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //save to database: segment 3 
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]MapData_1.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }

    //trigger mapCreate's internal function
    PsdMap::getInstance()->mapCreate();
    double Threshold = 2.5e-4;

    //HV's Coordinate: HV current coordinate(40.346799, 116.812289)
    tCoordinates startCoordinate_1 = {40.346293, 116.811317};  //expected coordinate: HV behind 100meter, HV's startCoordinate
    double startCoordLat_1_absValue = std::fabs(startCoordinate_1.latitude - MapData_1.startCoordinate.latitude);
    double startCoordLon_1_absValue = std::fabs(startCoordinate_1.longitude - MapData_1.startCoordinate.longitude); 
    printf("[%s] [%d]: startCoordLat_1_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLat_1_absValue);
    printf("[%s] [%d]: startCoordLon_1_absValue = %f\n", __FUNCTION__,  __LINE__, startCoordLon_1_absValue);
    EXPECT_LT(startCoordLat_1_absValue, Threshold);
    EXPECT_LT(startCoordLon_1_absValue, Threshold);

    tCoordinates endCoordinate_1 = {40.347039, 116.813418};   //expected coordinate: HV front 100meter, HV's endCoordinate
    double endCoordLat_1_absValue = std::fabs(endCoordinate_1.latitude - MapData_1.endCoordinate.latitude);
    double endCoordLon_1_absValue = std::fabs(endCoordinate_1.longitude - MapData_1.endCoordinate.longitude);
    printf("[%s] [%d]: endCoordLat_1_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLat_1_absValue);
    printf("[%s] [%d]: endCoordLon_1_absValue = %f\n", __FUNCTION__,  __LINE__, endCoordLon_1_absValue);
    EXPECT_LT(endCoordLat_1_absValue, Threshold);
    EXPECT_LT(endCoordLon_1_absValue, Threshold);
}

/*root Segment in curve case*/
TEST_F(PsdMapTest, rootWithCurve)
{
    struct PsdMapData MapData_1, MapData_2, MapData_3;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 4
    MapData_1.preSegmentId = 4;
    MapData_1.prevSegmentId = 3;
    MapData_1.preSegTotalLength = 115;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 0; //right
    MapData_1.branchAngle = +0.01; 
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 4;
    curSegment.curRemainLength = 0; //segTotalLength = 115, drivedLength = 115
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 231.49;
    curSegment.hvCoordinate = {40.344795, 116.808842};  //located at Zuoti Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's parent Segment, preSegmentId = 3, prevSegmentId = 2
    MapData_2.preSegmentId = 3;
    MapData_2.prevSegmentId = 2;
    MapData_2.preSegTotalLength = 153;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 1;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -1.84;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's root Segment, preSegmentId == prevSegmentId are 2
    MapData_3.preSegmentId = 2;
    MapData_3.prevSegmentId = 2;
    MapData_3.preSegTotalLength = 100;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 1.0 / 202.123;
    MapData_3.mpp = 1;
    MapData_3.sp = 0;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 1.0 / 238.086;
    MapData_3.branchDirection = 0;
    MapData_3.branchAngle = 0.0;
    MapData_3.segIsInTree = false;

    //save to database: segment 
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
    
    //trigger mapCreate's internal function
    PsdMap::getInstance()->mapCreate();
}

/*parent Segment in curve case*/
TEST_F(PsdMapTest, parentWithCurve)
{
    struct PsdMapData MapData_1, MapData_2;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 153;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -1.84; 
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 0; //segTotalLength = 153, drivedLength = 153
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 231.48;
    curSegment.hvCoordinate = {40.345438, 116.809901};  //located at Zuoti Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's parent Segment, preSegmentId = 2, prevSegmentId = 4
    MapData_2.preSegmentId = 2;
    MapData_2.prevSegmentId = 4;
    MapData_2.preSegTotalLength = 200;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 1.0 / 47.3284;
    MapData_2.mpp = 1;
    MapData_2.sp = 0;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 1.0 / 46.6588;
    MapData_2.branchDirection = 0;
    MapData_2.branchAngle = 0.0;
    MapData_2.segIsInTree = false;

    //save to database: segment 
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
    
    //trigger mapCreate's internal function
    PsdMap::getInstance()->mapCreate();
}

/*child Segment in curve case*/
TEST_F(PsdMapTest, childWithCurve)
{
    struct PsdMapData MapData_1, MapData_2;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 4;
    MapData_1.preSegTotalLength = 153;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 0; //right
    MapData_1.branchAngle = 0.0; 
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 153; //segTotalLength = 153, drivedLength = 0
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 52.15;
    curSegment.hvCoordinate = {40.345438, 116.809901};  //located at Zuoti Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's child Segment, preSegmentId = 2, prevSegmentId = 3
    MapData_2.preSegmentId = 2;
    MapData_2.prevSegmentId = 3;
    MapData_2.preSegTotalLength = 200;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 1.0 / 46.6588;
    MapData_2.mpp = 1;
    MapData_2.sp = 0;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 1.0 / 47.3284;
    MapData_2.branchDirection = 0; //right
    MapData_2.branchAngle = +1.84;
    MapData_2.segIsInTree = false;

    //save to database: segment 
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
    
    //trigger mapCreate's internal function
    PsdMap::getInstance()->mapCreate();
}

/*delete subtrees with depth greater than 1*/
TEST_F(PsdMapTest, deleteSubTreeWithDepthGreaterThan1)
{
    struct PsdMapData MapData_1, MapData_2, MapData_3, MapData_4, MapData_5, MapData_6, MapData_7;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 4
    MapData_1.preSegmentId = 4;
    MapData_1.prevSegmentId = 3;
    MapData_1.preSegTotalLength = 78;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 0; //right
    MapData_1.branchAngle = 0.01; 
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 4;
    curSegment.curRemainLength = 78; //segTotalLength = 78, drivedLength = 0
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.34;
    curSegment.hvCoordinate = {40.356480, 116.815134};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's parent Segment, preSegmentId = 3, prevSegmentId = 2
    MapData_2.preSegmentId = 3;
    MapData_2.prevSegmentId = 2;
    MapData_2.preSegTotalLength = 254;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 1;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -0.37;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's root Segment, preSegmentId = 2, prevSegmentId = 2
    MapData_3.preSegmentId = 2;
    MapData_3.prevSegmentId = 2;
    MapData_3.preSegTotalLength = 176;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 0.0;
    MapData_3.mpp = 1;
    MapData_3.sp = 1;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 0.0;
    MapData_3.branchDirection = 1; //left
    MapData_3.branchAngle = -0.01; 
    MapData_3.segIsInTree = false;

    //MapData_4 as HV's child Segment, preSegmentId = 5, prevSegmentId = 4
    MapData_4.preSegmentId = 5;
    MapData_4.prevSegmentId = 4;
    MapData_4.preSegTotalLength = 254;
    MapData_4.psd04RoadClass = CountyRoad;
    MapData_4.endCurvature = 0.0;
    MapData_4.mpp = 0;
    MapData_4.sp = 1;
    MapData_4.segmentIsComplete = 1;
    MapData_4.startCurvature = 0;
    MapData_4.branchDirection = 0; //right
    MapData_4.branchAngle = +90.06;
    MapData_4.segIsInTree = false;

    //MapData_5 as HV's child Segment, preSegmentId = 6, prevSegmentId = 4
    MapData_5.preSegmentId = 6;
    MapData_5.prevSegmentId = 4;
    MapData_5.preSegTotalLength = 254;
    MapData_5.psd04RoadClass = CountyRoad;
    MapData_5.endCurvature = 0.0;
    MapData_5.mpp = 1;
    MapData_5.sp = 1;
    MapData_5.segmentIsComplete = 1;
    MapData_5.startCurvature = 0;
    MapData_5.branchDirection = 0; //right
    MapData_5.branchAngle = +0.02;
    MapData_5.segIsInTree = false;
        
    //MapData_6 as HV's child Segment, preSegmentId = 7, prevSegmentId = 4
    MapData_6.preSegmentId = 7;
    MapData_6.prevSegmentId = 4;
    MapData_6.preSegTotalLength = 254;
    MapData_6.psd04RoadClass = CountyRoad;
    MapData_6.endCurvature = 0.0;
    MapData_6.mpp = 0;
    MapData_6.sp = 1;
    MapData_6.segmentIsComplete = 1;
    MapData_6.startCurvature = 0;
    MapData_6.branchDirection = 1; //left
    MapData_6.branchAngle = -90.05;
    MapData_6.segIsInTree = false;

    //MapData_7 as HV's child Segment, preSegmentId = 8, prevSegmentId = 6
    MapData_7.preSegmentId = 8;
    MapData_7.prevSegmentId = 6;
    MapData_7.preSegTotalLength = 103;
    MapData_7.psd04RoadClass = CountyRoad;
    MapData_7.endCurvature = 0.0;
    MapData_7.mpp = 1;
    MapData_7.sp = 1;
    MapData_7.segmentIsComplete = 1;
    MapData_7.startCurvature = 0;
    MapData_7.branchDirection = 0; //right
    MapData_7.branchAngle = +0.01;
    MapData_7.segIsInTree = false;

    //save to database: segment 4, 3, 2, 5, 6, 7, 8
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_4);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_5);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_6);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_7);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }

    //TODO1: trigger mapCreate to ensure that the tree is not NULL
    PsdMap::getInstance()->mapCreate();

    //TODO2: changing the curSegmentId of HV, and triggering mapUpdate
    tSelfSegment hvSegment =  PsdMessageDecoder::getInstance()->getSelfSegment();
    hvSegment.curSegmentId = 5;
    hvSegment.lastSegmentId = 4;
    hvSegment.curRemainLength = 254;
    hvSegment.posIsUnique = true;
    hvSegment.posLengthErr = Pos_2mTo5m;
    hvSegment.hvHeading = 269.40;                                            //HV switches to the heading on the new segmentId 
    hvSegment.hvCoordinate = {40.355777, 116.815146};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(hvSegment);
    if ( PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId !=  PsdMessageDecoder::getInstance()->getSelfSegment().lastSegmentId)
    {
        PsdMap::getInstance()->mapUpdate();   //SegmentId 2, 6, 7, 8 are deleted
    }
    
    //TODO3: check remain segmentId 4, 3, 5
    printf("[%s] [%d]: check remain segmentId\n", __FUNCTION__, __LINE__);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
}

/*mapUpdate: when curSegmentId changed; mapClear: when P_PSD_Usage_Active = false*/
TEST_F(PsdMapTest, mapCreateAndmapUpdateAndmapClear)
{
    struct PsdMapData MapData_1, MapData_2, MapData_3, MapData_4, MapData_5, MapData_6, MapData_7, MapData_8;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 4
    MapData_1.preSegmentId = 4;
    MapData_1.prevSegmentId = 3;
    MapData_1.preSegTotalLength = 78;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 0; //right
    MapData_1.branchAngle = 0.01; 
    MapData_1.segIsInTree = false;
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 4;
    curSegment.curRemainLength = 78; //segTotalLength = 78, drivedLength = 0
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.34;
    curSegment.hvCoordinate = {40.356480, 116.815134};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's parent Segment, preSegmentId = 3, prevSegmentId = 2
    MapData_2.preSegmentId = 3;
    MapData_2.prevSegmentId = 2;
    MapData_2.preSegTotalLength = 254;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 1;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -0.37;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's root Segment, preSegmentId = 2, prevSegmentId = 2
    MapData_3.preSegmentId = 2;
    MapData_3.prevSegmentId = 2;
    MapData_3.preSegTotalLength = 176;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 0.0;
    MapData_3.mpp = 1;
    MapData_3.sp = 1;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 0.0;
    MapData_3.branchDirection = 1; //left
    MapData_3.branchAngle = -0.01; 
    MapData_3.segIsInTree = false;

    //MapData_4 as HV's child Segment, preSegmentId = 5, prevSegmentId = 4
    MapData_4.preSegmentId = 5;
    MapData_4.prevSegmentId = 4;
    MapData_4.preSegTotalLength = 254;
    MapData_4.psd04RoadClass = CountyRoad;
    MapData_4.endCurvature = 0.0;
    MapData_4.mpp = 0;
    MapData_4.sp = 1;
    MapData_4.segmentIsComplete = 1;
    MapData_4.startCurvature = 0;
    MapData_4.branchDirection = 0; //right
    MapData_4.branchAngle = +90.06;
    MapData_4.segIsInTree = false;

    //MapData_5 as HV's child Segment, preSegmentId = 6, prevSegmentId = 4
    MapData_5.preSegmentId = 6;
    MapData_5.prevSegmentId = 4;
    MapData_5.preSegTotalLength = 254;
    MapData_5.psd04RoadClass = CountyRoad;
    MapData_5.endCurvature = 0.0;
    MapData_5.mpp = 1;
    MapData_5.sp = 1;
    MapData_5.segmentIsComplete = 1;
    MapData_5.startCurvature = 0;
    MapData_5.branchDirection = 0; //right
    MapData_5.branchAngle = +0.02;
    MapData_5.segIsInTree = false;
        
    //MapData_6 as HV's child Segment, preSegmentId = 7, prevSegmentId = 4
    MapData_6.preSegmentId = 7;
    MapData_6.prevSegmentId = 4;
    MapData_6.preSegTotalLength = 254;
    MapData_6.psd04RoadClass = CountyRoad;
    MapData_6.endCurvature = 0.0;
    MapData_6.mpp = 0;
    MapData_6.sp = 1;
    MapData_6.segmentIsComplete = 1;
    MapData_6.startCurvature = 0;
    MapData_6.branchDirection = 1; //left
    MapData_6.branchAngle = -90.05;
    MapData_6.segIsInTree = false;

    //MapData_7 as HV's child Segment, preSegmentId = 8, prevSegmentId = 6
    MapData_7.preSegmentId = 8;
    MapData_7.prevSegmentId = 6;
    MapData_7.preSegTotalLength = 103;
    MapData_7.psd04RoadClass = CountyRoad;
    MapData_7.endCurvature = 0.0;
    MapData_7.mpp = 1;
    MapData_7.sp = 1;
    MapData_7.segmentIsComplete = 1;
    MapData_7.startCurvature = 0;
    MapData_7.branchDirection = 0; //right
    MapData_7.branchAngle = +0.01;
    MapData_7.segIsInTree = false;

    //MapData_8 as any one of Segment, not in the mTree, preSegmentId = 20, prevSegmentId = 19
    MapData_8.preSegmentId = 20;
    MapData_8.prevSegmentId = 19;
    MapData_8.preSegTotalLength = 100;
    MapData_8.psd04RoadClass = CountyRoad;
    MapData_8.endCurvature = 0.0;
    MapData_8.mpp = 1;
    MapData_8.sp = 1;
    MapData_8.segmentIsComplete = 1;
    MapData_8.startCurvature = 0;
    MapData_8.branchDirection = 0; //right
    MapData_8.branchAngle = 0.0;
    MapData_8.segIsInTree = false;

    //save to database: segment  4, 3, 2, 5, 6, 7, 8, 20
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_4);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_5);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_6);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_7);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_8);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }

    //TODO1: trigger mapCreate to ensure that the tree is not NULL
    PsdMap::getInstance()->mapCreate();

    //TODO2: changing the curSegmentId of HV, and triggering mapUpdate
    tSelfSegment hvSegment =  PsdMessageDecoder::getInstance()->getSelfSegment();
    hvSegment.curSegmentId = 6;
    hvSegment.lastSegmentId = 4;
    hvSegment.curRemainLength = 254;
    hvSegment.posIsUnique = true;
    hvSegment.posLengthErr = Pos_2mTo5m;
    hvSegment.hvHeading = 179.36;
    hvSegment.hvCoordinate = {40.355777, 116.815146};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(hvSegment);
    if ( PsdMessageDecoder::getInstance()->getSelfSegment().curSegmentId !=  PsdMessageDecoder::getInstance()->getSelfSegment().lastSegmentId)
    {
        PsdMap::getInstance()->mapUpdate();   //SegmentId 2, 5, 7 are deleted
    }
    
    //TODO3: check remain segmentId
    printf("[%s] [%d]: check remain segmentId\n", __FUNCTION__, __LINE__);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }

   //TODO4: when P_PSD_Usage_Active = false, trigger mapClear and segmentManager
    bool P_PSD_Usage_Active = false;
    if (!P_PSD_Usage_Active)
    {
        printf("[%s] [%d]: tree = %p\n", __FUNCTION__, __LINE__, PsdMap::getInstance()->getTree());
        if (PsdMap::getInstance()->getTree() != NULL)
        {
            PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
        }
        PsdMessageDecoder::getInstance()->segmentManager(false);
    }
    struct TreeNode *nullPtr =  NULL;
    EXPECT_EQ(PsdMap::getInstance()->getTree(), nullPtr);
}

/*test curIdIsNotInList*/
TEST_F(PsdMapTest, curIdIsNotInList)
{
    struct PsdMapData MapData_1;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as any one segment
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    
    //set curSegment info, the curSegment is not in list now
    tSelfSegment curSegment;
    curSegment.curSegmentId = 5;
    curSegment.curRemainLength = 185; //segTotalLength = 254, drivedLength = 69
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    
    //save to database: segment  3
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);

    //find curSegment in list
    struct PsdMapData *nullPtr = NULL;
    struct PsdMapData *ptr = PsdMap::getInstance()->curIdIsInList();
    EXPECT_EQ(ptr, nullPtr);
}

/*test findNodeById, for the case where the mTree is NULL*/
TEST_F(PsdMapTest, findNodeById)
{
    struct TreeNode *mTree = NULL;
    struct TreeNode *nullPtr = NULL;
    struct TreeNode *node = PsdMap::getInstance()->findNodeById(mTree, 3);
    EXPECT_EQ(node, nullPtr);
}

/*test deleteOldRoot*/
TEST_F(PsdMapTest, deleteOldRoot)
{
    //for the case where the mTree is NULL
    struct TreeNode *node = NULL;
    PsdMap::getInstance()->setTree(node);
    PsdMap::getInstance()->deleteOldRoot();

    //for the case where the vPsdMap  is NULL
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    node = new struct TreeNode();    
    node->MapData = {0};
    node->ParentNode = NULL;
    node->vChilds.clear();
    struct TreeNode *node_2 = new struct TreeNode();
    node->vChilds.push_back(node_2);        //avoiding "vector _M_range_check" error
    PsdMap::getInstance()->setTree(node);
    PsdMap::getInstance()->deleteOldRoot();
    delete node, node_2;
}

/*test updateChildNode, for the case where the mTree is NULL*/
TEST_F(PsdMapTest, updateChildNode)
{
    struct TreeNode *node = NULL;
    PsdMap::getInstance()->setTree(node);
    PsdMap::getInstance()->updateChildNode();
}

/*test deleteSubTree*/
TEST_F(PsdMapTest, deleteSubTree)
{
    //for the case where the mTree is NULL
    struct TreeNode *node = NULL;
    PsdMap::getInstance()->deleteSubTree(node);

    //for the case where the vPsdMap  is NULL
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }

    node = new struct TreeNode();    
    node->MapData = {0};
    node->ParentNode = NULL;
    node->vChilds.clear();
    PsdMap::getInstance()->deleteSubTree(node);
    delete node;
}

/*test ~PsdMap()*/
TEST_F(PsdMapTest, destructor)
{
    PsdMap map;
}

/**
 * @brief PsdLocationTest
 */

class PsdLocationTest : public testing::Test
{
protected:
    PsdLocation *pInstance;
    PsdLocation *getInstance()
    {
        if (NULL == pInstance)
        {
            pInstance = new PsdLocation();
        }
        return pInstance;
    }

    void SetUp()
    {
        pInstance = NULL;
    }
    void TerDown()
    {
        delete pInstance;
    }
};

TEST_F(PsdLocationTest, getPsdRoLocation)
{   
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }

    struct PsdMapData MapData_1;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; //segTotalLength = 254, drivedLength = 69
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);   //save to database: segment 3 
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]MapData_1.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
    PsdMap::getInstance()->mapCreate();                                                        

    //case1: initial data of PsdLocation
    Data2Location data2Location;
    data2Location.HeadingDelta = 30.0;
    data2Location.RoPos = {40.345438, 116.809901, 62.4};
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);
    
    //case2: PsdAvailable == true
    PsdMap::getInstance()->setMapMutexStatus(false);
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case3: PsdAvailable == false
    PsdMap::getInstance()->setMapMutexStatus(true);
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);
    
    //clear the tree and vPsdMap for next case  
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
}

/*tree with multi layer*/
TEST_F(PsdLocationTest, treeWithMultiLayer)
{
    struct PsdMapData MapData_1, MapData_2, MapData_3, MapData_4, MapData_5, MapData_6, MapData_7, MapData_8;
    printf("[%s] [%d]: VPsdMap().empty() = %d\n", __FUNCTION__,  __LINE__, PsdMessageDecoder::getInstance()->getVPsdMap().empty());   
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = +90.0; //writing an assumed value for gtest 
    
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; //segTotalLength = 254, drivedLength = 69
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's parent Segment, preSegmentId = 2, prevSegmentId = 10
    MapData_2.preSegmentId = 2;
    MapData_2.prevSegmentId = 10;
    MapData_2.preSegTotalLength = 176;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 0;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -0.01;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's root Segment, preSegmentId = 10, prevSegmentId = 11
    MapData_3.preSegmentId = 10;
    MapData_3.prevSegmentId = 10;
    MapData_3.preSegTotalLength = 200;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 0.0;
    MapData_3.mpp = 1;
    MapData_3.sp = 1;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 0.0;
    MapData_3.branchDirection = 0;
    MapData_3.branchAngle = 0.0;
    MapData_3.segIsInTree = false;

    //MapData_4 as HV's child Segment, preSegmentId = 4, prevSegmentId = 3
    MapData_4.preSegmentId = 4;
    MapData_4.prevSegmentId = 3;
    MapData_4.preSegTotalLength = 78;
    MapData_4.psd04RoadClass = CountyRoad;
    MapData_4.endCurvature = 0.0;
    MapData_4.mpp = 1;
    MapData_4.sp = 1;
    MapData_4.segmentIsComplete = 1;
    MapData_4.startCurvature = 0;
    MapData_4.branchDirection = 0; //right
    MapData_4.branchAngle = +0.01;
    MapData_4.segIsInTree = false;

    //MapData_5 as HV's child Segment, preSegmentId = 5, prevSegmentId = 4
    MapData_5.preSegmentId = 5;
    MapData_5.prevSegmentId = 4;
    MapData_5.preSegTotalLength = 254;
    MapData_5.psd04RoadClass = CountyRoad;
    MapData_5.endCurvature = 0.0;
    MapData_5.mpp = 0;
    MapData_5.sp = 1;
    MapData_5.segmentIsComplete = 1;
    MapData_5.startCurvature = 0;
    MapData_5.branchDirection = 0; //right
    MapData_5.branchAngle = +90.06;
    MapData_5.segIsInTree = false;
        
    //MapData_6 as HV's child Segment, preSegmentId = 6, prevSegmentId = 4
    MapData_6.preSegmentId = 6;
    MapData_6.prevSegmentId = 4;
    MapData_6.preSegTotalLength = 254;
    MapData_6.psd04RoadClass = CountyRoad;
    MapData_6.endCurvature = 0.0;
    MapData_6.mpp = 1;
    MapData_6.sp = 1;
    MapData_6.segmentIsComplete = 1;
    MapData_6.startCurvature = 0;
    MapData_6.branchDirection = 0; //right
    MapData_6.branchAngle = +0.02;
    MapData_6.segIsInTree = false;

    //MapData_7 as HV's child Segment, preSegmentId = 7, prevSegmentId = 4
    MapData_7.preSegmentId = 7;
    MapData_7.prevSegmentId = 4;
    MapData_7.preSegTotalLength = 254;
    MapData_7.psd04RoadClass = CountyRoad;
    MapData_7.endCurvature = 0.0;
    MapData_7.mpp = 0;
    MapData_7.sp = 1;
    MapData_7.segmentIsComplete = 1;
    MapData_7.startCurvature = 0;
    MapData_7.branchDirection = 1; //left
    MapData_7.branchAngle = -90.05;
    MapData_7.segIsInTree = false;

    //MapData_8 as HV's child Segment, preSegmentId = 8, prevSegmentId = 6
    MapData_8.preSegmentId = 8;
    MapData_8.prevSegmentId = 6;
    MapData_8.preSegTotalLength = 103;
    MapData_8.psd04RoadClass = CountyRoad;
    MapData_8.endCurvature = 0.0;
    MapData_8.mpp = 1;
    MapData_8.sp = 1;
    MapData_8.segmentIsComplete = 1;
    MapData_8.startCurvature = 0;
    MapData_8.branchDirection = 0; //right
    MapData_8.branchAngle = +0.01;
    MapData_8.segIsInTree = false;
    //save to database: segment 10, 2, 3, 4, 5, 6, 7, 8
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_4);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_5);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_6);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_7);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_8);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
    PsdMap::getInstance()->mapCreate();

    //case8: RelativePos == Pos_Right, realativeDirection == Dir_ComingFromRight, accumulateBranchAngle == 90.0
    Data2Location data2Location;
    data2Location.HeadingDelta = 270.0;
    data2Location.RoPos = {40.357717, 116.815133, 0.0};                                   
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);    

    //case9: RelativePos == Pos_Left, realativeDirection == Dir_ComingFromLeft, accumulateBranchAngle == 270.0
    MapData_1.accumulateBranchAngle = +270.0; //writing an assumed value for gtest 
    data2Location.HeadingDelta = 90.0;
    data2Location.RoPos = {40.358516, 116.815116, 0.0};                                   
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);  

    //case10: RelativePos == Pos_Left, realativeDirection == Dir_ComingFromLeft, accumulateBranchAngle == 270.0, HeadingDelta = 90.0
    MapData_1.accumulateBranchAngle = +270.0; //writing an assumed value for gtest 
    data2Location.HeadingDelta = 90.0;
    data2Location.RoPos = {40.358516, 116.815116, 0.0};                                   
    data2Location.RvSpeed = 60.0;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);  

    //case11: RelativePos == Pos_Right, realativeDirection == Dir_ComingFromRight, accumulateBranchAngle == 90.0, HeadingDelta == 270.0
    MapData_1.accumulateBranchAngle = 90.0; 
    data2Location.HeadingDelta = 270.0;
    data2Location.RoPos = {40.357717, 116.815133, 0.0};                                   
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);  

    //case12: RelativePos == Pos_Behind, realativeDirection == Dir_ComingFromBehind, HeadingDelta == 30.0
    data2Location.HeadingDelta = 30.0;
    data2Location.RoPos = {40.358516, 116.815116, 0.0};                                   
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);  

    //case13: RvSpeed == 0.0, other values donot matter
    MapData_1.accumulateBranchAngle = +270.0;
    data2Location.HeadingDelta = 90.0;
    data2Location.RoPos = {40.358516, 116.815116, 0.0};                                   
    data2Location.RvSpeed = 0.0;
    data2Location.eventClassify = Static_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);  
}

/*test calcRelativePosition and calcRelativeDirection*/
TEST_F(PsdLocationTest, RelativePositionAndRelativeDirection)
{
    Data2Location data2Location;
    //case1: RelativePos = Pos_Behind
    data2Location.HeadingDelta = 0.0;
    data2Location.RoPos = {40.358516, 116.815116, 0.0};     //behind HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    struct PsdMapData MapData_1;
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +90.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; //segTotalLength = 254, drivedLength = 69
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    EXPECT_EQ(PsdLocation::getInstance()->calcRelativePosition(data2Location), Pos_Behind);

    //case2: RelativePos = Pos_Left, RoadSegClass = RoadClass_highway ⇒ realativeDirection = Dir_Unreachable
    data2Location.RoPos = {40.357717, 116.815133, 0.0}; 
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);
    
    //case3: RelativePos = Pos_Right, RoadSegClass = RoadClass_highway ⇒ realativeDirection = Dir_Unreachable
    data2Location.RoPos = {40.357715, 116.815083, 0.0}; 
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = +90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case4: RelativePos = Pos_Ahead, (0.0 <= accumulateBranchAngle <= +-45.0), (0.0 <= HeadingDelta <= 45.0 && 315.0 <= HeadingDelta <= 360.0)  ⇒ realativeDirection = Dir_Ahead
    //1
    data2Location.HeadingDelta = 30.0;
    data2Location.RoPos = {40.357890, 116.815114, 0.0}; 
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2
    data2Location.HeadingDelta = 330;
    data2Location.RoPos = {40.357715, 116.815083, 0.0};     //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; 
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = -30.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //3
    data2Location.HeadingDelta = 270.0 ;    //for realativeDirection = Dir_Ahead branch
    data2Location.RoPos = {40.357715, 116.815083, 0.0};     //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; 
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //4 
    data2Location.HeadingDelta = -10.0 ;    //for HeadingDelta >= 0.0 case not fulfill 
    data2Location.RoPos = {40.357715, 116.815083, 0.0};     //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; 
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //5 
    data2Location.HeadingDelta = 370.0 ;    //for HeadingDelta <= 360.0 case not fulfill 
    data2Location.RoPos = {40.357715, 116.815083, 0.0};     //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; 
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case5: RelativePos = Pos_Ahead, (0.0 <= accumulateBranchAngle <= +-45.0), (135.0 <= HeadingDelta <= 225.0 )  ⇒ realativeDirection = Dir_Oncoming
    //1
    data2Location.HeadingDelta = 180.0;
    data2Location.RoPos = {40.357890, 116.815114, 0.0}; //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2
    data2Location.HeadingDelta = 100.0; //for (data2Location.HeadingDelta >= (180.0 - pRelativeDirection) case not fulfill 
    data2Location.RoPos = {40.357890, 116.815114, 0.0}; //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case6: RelativePos = Pos_Behind, accumulateBranchAngle can be any value, (0.0 <= HeadingDelta <= 45.0 && 315.0 <= HeadingDelta <= 360.0)  ⇒ realativeDirection = Dir_ComingFromBehind
    //1: HeadingDelta = 30.0
    data2Location.HeadingDelta = 30.0;
    data2Location.RoPos = {40.358516, 116.815116, 0.0}; //behind HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    // MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2: HeadingDelta = 330.0
    data2Location.HeadingDelta = 330.0;
    data2Location.RoPos = {40.358516, 116.815116, 0.0}; //behind HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    // MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //3 
    data2Location.HeadingDelta = -10.0; //for HeadingDelta >= 0.0 case not fullfill
    data2Location.RoPos = {40.358516, 116.815116, 0.0}; //behind HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    // MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //4
    data2Location.HeadingDelta = 370.0; //for HeadingDelta <= 360.0 case not fullfill
    data2Location.RoPos = {40.358516, 116.815116, 0.0}; //behind HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    // MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case7: RelativePos = Pos_Behind, accumulateBranchAngle can be any value, (135.0 <= HeadingDelta <= 225.0)  ⇒ realativeDirection = Dir_AwayFromBehind
    //1
    data2Location.HeadingDelta = 180.0;
    data2Location.RoPos = {40.358516, 116.815116, 0.0}; //behind HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    // MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2 
    data2Location.HeadingDelta = 226.0; //for HeadingDelta <= (180.0 + pRelativeDirection) case not fullfill
    data2Location.RoPos = {40.358516, 116.815116, 0.0}; //behind HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    // MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case8: RelativePos = Pos_Left, psd04RoadClass != Expressway, (225.0 <= accumulateBranchAngle+360.0 <= 315.0) , (45.0 <= HeadingDelta <= 135.0)  ⇒ realativeDirection = Dir_ComingFromLeft
    //1
    data2Location.HeadingDelta = 90.0; 
    data2Location.RoPos = {40.357717, 116.815133, 0.0}; //left HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2
    data2Location.HeadingDelta = 44.0; //for 45.0 <= HeadingDelta <= 135.0 case not fullfill
    data2Location.RoPos = {40.357717, 116.815133, 0.0}; //left HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //3
    data2Location.HeadingDelta = 136.0; //for 45.0 <= HeadingDelta <= 135.0 case not fullfill
    data2Location.RoPos = {40.357717, 116.815133, 0.0}; //left HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case9: RelativePos = Pos_Left, psd04RoadClass != Expressway, (225.0 <= accumulateBranchAngle+360.0 <= 315.0) , (225.0 <= HeadingDelta <= 315.0)  ⇒ realativeDirection = Dir_AwayFromLeft
    //1
    data2Location.HeadingDelta = 270.0; 
    data2Location.RoPos = {40.357717, 116.815133, 0.0}; //left HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2
    data2Location.HeadingDelta = 224.0; //for 225.0 <= HeadingDelta <= 315.0 case not fullfill
    data2Location.RoPos = {40.357717, 116.815133, 0.0}; //left HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //3
    data2Location.HeadingDelta = 316.0; //for 225.0 <= HeadingDelta <= 315.0 case not fullfill
    data2Location.RoPos = {40.357717, 116.815133, 0.0}; //left HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case10: RelativePos = Pos_Right, psd04RoadClass != Expressway, (45.0 <= accumulateBranchAngle <= 135.0) , (45.0 <= HeadingDelta <= 135.0)  ⇒ realativeDirection = Dir_AwayFromRight
    //1
    data2Location.HeadingDelta = 90.0; 
    data2Location.RoPos = {40.357715, 116.815083, 0.0}; //right HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = 90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2
    data2Location.HeadingDelta = 44.0; //for 45.0 <= HeadingDelta <= 135.0 case not fullfill
    data2Location.RoPos = {40.357715, 116.815083, 0.0}; //right HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = 90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //3
    data2Location.HeadingDelta = 136.0; //for 45.0 <= HeadingDelta <= 135.0 case not fullfill
    data2Location.RoPos = {40.357715, 116.815083, 0.0}; //right HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = 90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case11: RelativePos = Pos_Right, psd04RoadClass != Expressway, (45.0 <= accumulateBranchAngle <= 135.0) , (225.0 <= HeadingDelta <= 315.0)  ⇒ realativeDirection = Dir_ComingFromRight
    //1
    data2Location.HeadingDelta = 316.0; //for 225.0 <= HeadingDelta <= 315.0 case not fullfill
    data2Location.RoPos = {40.357715, 116.815083, 0.0}; //right HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = 90.0;
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case12: deltaXY.x > 0.0, (315.0 < accumulateBranchAngle <= 360.0 || 0.0 <= accumulateBranchAngle < 45.0) ⇒ RelativePosition = Pos_Ahead;
    //1
    data2Location.RoPos = {40.357890, 116.815114, 0.0}; //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -30.0; //for 315.0 < accumulateBranchAngle <= 360.0 case to fullfill
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2
    data2Location.RoPos = {40.357890, 116.815114, 0.0}; //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = -370.0; //for 0.0 <= accumulateBranchAngle < 45.0 case not fullfill 
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //3
    data2Location.RoPos = {40.357890, 116.815114, 0.0}; //ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
        
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = Expressway;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1;
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = +46.0; //for 0.0 <= accumulateBranchAngle < 45.0 case not fullfill 
    MapData_1.structSeparate = NoInfo;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; 
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);
}

/*test calcRvRelevancy function*/
TEST_F(PsdLocationTest, calcRvRelevancy)
{
    //case1: RelativePos == Pos_Behind, eventClassify == Static_Event ⇒ RvRelevancy = irrelevant
    Data2Location data2Location;
    data2Location.RoPos = {40.358516, 116.815116, 0.0};     //behind HV
    data2Location.eventClassify = Static_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    struct PsdMapData MapData_1;
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +90.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case2: mpp == false, eventClassify == Static_Event ⇒ RvRelevancy = irrelevant
    data2Location.RoPos = {40.358516, 116.815116, 0.0};     //behind HV
    data2Location.eventClassify = Static_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 0;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +90.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case3: RelativePos != Pos_Behind, mpp == true, eventClassify == Static_Event ⇒ RvRelevancy = irrelevant
    //1
    data2Location.RoPos = {40.357890, 116.815114, 0.0};     //ahead HV
    data2Location.eventClassify = Static_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2
    data2Location.RoPos = {40.357890, 116.815114, 0.0};     //ahead HV
    data2Location.eventClassify = Static_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 0;  //for RelativePos != Pos_Behind, mpp == false case
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case4: RelativeDir == Dir_Oncoming, mRoMatchedSegId == curSegmentId, eventClassify == Dynamic_Event, structSeparate == 1||2 ⇒ RvRelevancy = irrelevant
    //1
    data2Location.HeadingDelta = 180.0;
    data2Location.RoPos = {40.357890, 116.815114, 0.0};     //ahead HV
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;  
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = StructuralSeperation;   //structSeparate == 1
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //2
    data2Location.HeadingDelta = 180.0;
    data2Location.RoPos = {40.357890, 116.815114, 0.0};     //ahead HV
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;  
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = SeperationButNoStructural;   //structSeparate == 2
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //3
    data2Location.HeadingDelta = 30.0; 
    data2Location.RoPos = {40.357890, 116.815114, 0.0};     //ahead HV
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;  
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = SeperationButNoStructural;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //4
    data2Location.HeadingDelta = 180.0;
    data2Location.RoPos = {40.357890, 116.815114, 0.0};     //ahead HV
    data2Location.eventClassify = Dynamic_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;  
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    MapData_1.structSeparate = NoInfo;   //structSeparate == 3
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case5: eventClassify = Instantanceous_Event 
    data2Location.RoPos = {40.357890, 116.815114, 0.0};     //ahead HV
    data2Location.eventClassify = Instantanceous_Event;
    
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    MapData_1.accumulateBranchAngle = +30.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    PsdMap::getInstance()->mapCreate();
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

}

/*test calcDistanceToEvent function*/
TEST_F(PsdLocationTest, calcDistanceToEvent)
{
    //case1: mRoMatchedNode->MapData.nodeAttribute == RootSegment
    struct PsdMapData MapData_1, MapData_2, MapData_3, MapData_4, MapData_5, MapData_6, MapData_7, MapData_8;
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = +90.0;
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's parent Segment, preSegmentId = 2, prevSegmentId = 10
    MapData_2.preSegmentId = 2;
    MapData_2.prevSegmentId = 10;
    MapData_2.preSegTotalLength = 176;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 0;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -0.01;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's root Segment, preSegmentId = 10, prevSegmentId = 11
    MapData_3.preSegmentId = 10;
    MapData_3.prevSegmentId = 10;
    MapData_3.preSegTotalLength = 200;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 0.0;
    MapData_3.mpp = 1;
    MapData_3.sp = 1;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 0.0;
    MapData_3.branchDirection = 0;
    MapData_3.branchAngle = 0.0;
    MapData_3.segIsInTree = false;

    //MapData_4 as HV's child Segment, preSegmentId = 4, prevSegmentId = 3
    MapData_4.preSegmentId = 4;
    MapData_4.prevSegmentId = 3;
    MapData_4.preSegTotalLength = 78;
    MapData_4.psd04RoadClass = CountyRoad;
    MapData_4.endCurvature = 0.0;
    MapData_4.mpp = 1;
    MapData_4.sp = 1;
    MapData_4.segmentIsComplete = 1;
    MapData_4.startCurvature = 0;
    MapData_4.branchDirection = 0; //right
    MapData_4.branchAngle = +0.01;
    MapData_4.segIsInTree = false;

    //MapData_5 as HV's child Segment, preSegmentId = 5, prevSegmentId = 4
    MapData_5.preSegmentId = 5;
    MapData_5.prevSegmentId = 4;
    MapData_5.preSegTotalLength = 254;
    MapData_5.psd04RoadClass = CountyRoad;
    MapData_5.endCurvature = 0.0;
    MapData_5.mpp = 0;
    MapData_5.sp = 1;
    MapData_5.segmentIsComplete = 1;
    MapData_5.startCurvature = 0;
    MapData_5.branchDirection = 0; //right
    MapData_5.branchAngle = +90.06;
    MapData_5.segIsInTree = false;
        
    //MapData_6 as HV's child Segment, preSegmentId = 6, prevSegmentId = 4
    MapData_6.preSegmentId = 6;
    MapData_6.prevSegmentId = 4;
    MapData_6.preSegTotalLength = 254;
    MapData_6.psd04RoadClass = CountyRoad;
    MapData_6.endCurvature = 0.0;
    MapData_6.mpp = 1;
    MapData_6.sp = 1;
    MapData_6.segmentIsComplete = 1;
    MapData_6.startCurvature = 0;
    MapData_6.branchDirection = 0; //right
    MapData_6.branchAngle = +0.02;
    MapData_6.segIsInTree = false;

    //MapData_7 as HV's child Segment, preSegmentId = 7, prevSegmentId = 4
    MapData_7.preSegmentId = 7;
    MapData_7.prevSegmentId = 4;
    MapData_7.preSegTotalLength = 254;
    MapData_7.psd04RoadClass = CountyRoad;
    MapData_7.endCurvature = 0.0;
    MapData_7.mpp = 0;
    MapData_7.sp = 1;
    MapData_7.segmentIsComplete = 1;
    MapData_7.startCurvature = 0;
    MapData_7.branchDirection = 1; //left
    MapData_7.branchAngle = -90.05;
    MapData_7.segIsInTree = false;

    //MapData_8 as HV's child Segment, preSegmentId = 8, prevSegmentId = 6
    MapData_8.preSegmentId = 8;
    MapData_8.prevSegmentId = 6;
    MapData_8.preSegTotalLength = 103;
    MapData_8.psd04RoadClass = CountyRoad;
    MapData_8.endCurvature = 0.0;
    MapData_8.mpp = 1;
    MapData_8.sp = 1;
    MapData_8.segmentIsComplete = 1;
    MapData_8.startCurvature = 0;
    MapData_8.branchDirection = 0; //right
    MapData_8.branchAngle = +0.01;
    MapData_8.segIsInTree = false;
    //save to database: segment 10, 2, 3, 4, 5, 6, 7, 8
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_4);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_5);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_6);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_7);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_8);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
    PsdMap::getInstance()->mapCreate();

    Data2Location data2Location;
    data2Location.HeadingDelta = 0.0;
    data2Location.RoPos = {40.361367, 116.815071, 0.0};     //matched root segment, behind HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case2: mRoMatchedNode->MapData.nodeAttribute == ParentSegment
    data2Location.RoPos = {40.359671, 116.815067, 0.0};     //matched parent segment, behind HV
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);

    //case3: mRoMatchedNode->MapData.nodeAttribute == ChildSegment
    data2Location.RoPos = {40.353726, 116.815168, 0.0};     //matched child segment, ahead HV
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);
}

/*test calcRoDis2Intersection*/
TEST_F(PsdLocationTest, calcRoDis2Intersection)
{
    //case: nodeAttribute == ChildSegment, (data2Location.RvSpeed != 0.0) && (RelativeDir == Dir_ComingFromLeft || RelativeDir == Dir_ComingFromRight) ⇒ calcRoDis2Intersection
    struct PsdMapData MapData_1, MapData_2, MapData_3, MapData_4, MapData_5, MapData_6, MapData_7, MapData_8;
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = +90.0;
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    //MapData_2 as HV's parent Segment, preSegmentId = 2, prevSegmentId = 10
    MapData_2.preSegmentId = 2;
    MapData_2.prevSegmentId = 10;
    MapData_2.preSegTotalLength = 176;
    MapData_2.psd04RoadClass = CountyRoad;
    MapData_2.endCurvature = 0.0;
    MapData_2.mpp = 0;
    MapData_2.sp = 1;
    MapData_2.segmentIsComplete = 1;
    MapData_2.startCurvature = 0.0;
    MapData_2.branchDirection = 1; //left
    MapData_2.branchAngle = -0.01;
    MapData_2.segIsInTree = false;

    //MapData_3 as HV's root Segment, preSegmentId = 10, prevSegmentId = 11
    MapData_3.preSegmentId = 10;
    MapData_3.prevSegmentId = 10;
    MapData_3.preSegTotalLength = 200;
    MapData_3.psd04RoadClass = CountyRoad;
    MapData_3.endCurvature = 0.0;
    MapData_3.mpp = 1;
    MapData_3.sp = 1;
    MapData_3.segmentIsComplete = 1;
    MapData_3.startCurvature = 0.0;
    MapData_3.branchDirection = 0;
    MapData_3.branchAngle = 0.0;
    MapData_3.segIsInTree = false;

    //MapData_4 as HV's child Segment, preSegmentId = 4, prevSegmentId = 3
    MapData_4.preSegmentId = 4;
    MapData_4.prevSegmentId = 3;
    MapData_4.preSegTotalLength = 78;
    MapData_4.psd04RoadClass = CountyRoad;
    MapData_4.endCurvature = 0.0;
    MapData_4.mpp = 1;
    MapData_4.sp = 1;
    MapData_4.segmentIsComplete = 1;
    MapData_4.startCurvature = 0;
    MapData_4.branchDirection = 0; //right
    MapData_4.branchAngle = +0.01;
    MapData_4.segIsInTree = false;
    MapData_4.accumulateBranchAngle = +0.01; 

    //MapData_5 as HV's child Segment, preSegmentId = 5, prevSegmentId = 4
    MapData_5.preSegmentId = 5;
    MapData_5.prevSegmentId = 4;
    MapData_5.preSegTotalLength = 254;
    MapData_5.psd04RoadClass = CountyRoad;
    MapData_5.endCurvature = 0.0;
    MapData_5.mpp = 0;
    MapData_5.sp = 1;
    MapData_5.segmentIsComplete = 1;
    MapData_5.startCurvature = 0;
    MapData_5.branchDirection = 0; //right
    MapData_5.branchAngle = +90.06;
    MapData_5.segIsInTree = false;
    MapData_5.accumulateBranchAngle = +90.07;
        
    //MapData_6 as HV's child Segment, preSegmentId = 6, prevSegmentId = 4
    MapData_6.preSegmentId = 6;
    MapData_6.prevSegmentId = 4;
    MapData_6.preSegTotalLength = 254;
    MapData_6.psd04RoadClass = CountyRoad;
    MapData_6.endCurvature = 0.0;
    MapData_6.mpp = 1;
    MapData_6.sp = 1;
    MapData_6.segmentIsComplete = 1;
    MapData_6.startCurvature = 0;
    MapData_6.branchDirection = 0; //right
    MapData_6.branchAngle = +0.02;
    MapData_6.segIsInTree = false;

    //MapData_7 as HV's child Segment, preSegmentId = 7, prevSegmentId = 4
    MapData_7.preSegmentId = 7;
    MapData_7.prevSegmentId = 4;
    MapData_7.preSegTotalLength = 254;
    MapData_7.psd04RoadClass = CountyRoad;
    MapData_7.endCurvature = 0.0;
    MapData_7.mpp = 0;
    MapData_7.sp = 1;
    MapData_7.segmentIsComplete = 1;
    MapData_7.startCurvature = 0;
    MapData_7.branchDirection = 1; //left
    MapData_7.branchAngle = -90.05;
    MapData_7.segIsInTree = false;

    //MapData_8 as HV's child Segment, preSegmentId = 8, prevSegmentId = 6
    MapData_8.preSegmentId = 8;
    MapData_8.prevSegmentId = 6;
    MapData_8.preSegTotalLength = 103;
    MapData_8.psd04RoadClass = CountyRoad;
    MapData_8.endCurvature = 0.0;
    MapData_8.mpp = 1;
    MapData_8.sp = 1;
    MapData_8.segmentIsComplete = 1;
    MapData_8.startCurvature = 0;
    MapData_8.branchDirection = 0; //right
    MapData_8.branchAngle = +0.01;
    MapData_8.segIsInTree = false;
    //save to database: segment 10, 2, 3, 4, 5, 6, 7, 8
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_2);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_3);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_4);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_5);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_6);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_7);
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_8);
    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
    PsdMap::getInstance()->mapCreate();

    Data2Location data2Location;
    data2Location.HeadingDelta = 270.0;                                     //RelativeDir == Dir_ComingFromRight
    data2Location.RoPos = {40.355748, 116.813700, 0.0};     //matched child segment, right HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);
}

/*test RoMatchSegment in curve case*/
TEST_F(PsdLocationTest, RoMatchSegment)
{
    struct PsdMapData MapData_1;
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3, circle with a radius of 60.5577 meters
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 110;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = +1.0 / 60.5577;
    MapData_1.mpp = 1;
    MapData_1.sp = 0;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = +1.0 / 60.5577;
    MapData_1.branchDirection = 0;
    MapData_1.branchAngle = 0.0; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = 0.0;
    PsdMessageDecoder::getInstance()->getVPsdMap().push_back(&MapData_1);
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 110;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 0.0; //north
    curSegment.hvCoordinate = {40.357607, 116.812605};
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);

    for (auto it = PsdMessageDecoder::getInstance()->getVPsdMap().begin(); it != PsdMessageDecoder::getInstance()->getVPsdMap().end(); it++)
    {
        printf("[%s] [%d]: MapData_X.preSegmentId = %u\n", __FUNCTION__, __LINE__, (*it)->preSegmentId);
    }
    PsdMap::getInstance()->mapCreate();

    Data2Location data2Location;
    data2Location.HeadingDelta = 10.24;                                     //RelativeDir == Dir_Ahead
    data2Location.RoPos = {40.357946, 116.812686, 0.0};     //matched current segment, ahead HV
    data2Location.RvSpeed = 60.0;
    data2Location.eventClassify = Dynamic_Event;
    PsdLocation::getInstance()->getPsdRoLocation(data2Location);
}

/*test accumulateChildsLength, when Node is NULL*/
TEST_F(PsdLocationTest, accumulateChildsLength)
{
    struct TreeNode *tempNode = NULL;
    EXPECT_EQ(PsdLocation::getInstance()->accumulateChildsLength(tempNode), 0);
}

/*test calcRoadSegmentClass function*/
TEST_F(PsdLocationTest, calcRoadSegmentClass)
{
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    struct PsdMapData MapData_1;
    //case1: RoadClass_Unkown
    //MapData_1 as HV's current Segment, curSegmentId == preSegmentId are 3
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 254;
    MapData_1.psd04RoadClass = PrivateRoad;
    MapData_1.endCurvature = 0.0;
    MapData_1.mpp = 1;
    MapData_1.sp = 1;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 0.0;
    MapData_1.branchDirection = 1; //left
    MapData_1.branchAngle = -0.37; 
    MapData_1.segIsInTree = true;
    struct TreeNode *tempNode_0 = new struct TreeNode();
    tempNode_0->MapData = MapData_1;
    tempNode_0->ParentNode = NULL;
    tempNode_0->vChilds.clear();
    PsdMap::getInstance()->setTree(tempNode_0);

    //set curSegment info
    tSelfSegment curSegment;
    curSegment.curSegmentId = 3;
    curSegment.curRemainLength = 185; //segTotalLength = 254, drivedLength = 69
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_2mTo5m;
    curSegment.hvHeading = 179.33;
    curSegment.hvCoordinate = {40.358150, 116.815109};  //located at Dongji Road, Miyun District, Beijing, China
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->calcRoadSegmentClass(), RoadClass_Unkown);

    //case2: RoadClass_highway
    //mapClear(make sure there are no memory leaks), change mTree, and then calcRoadSegmentClass
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    MapData_1.psd04RoadClass = Expressway;
    struct TreeNode *tempNode_1 = new struct TreeNode();
    tempNode_1->MapData = MapData_1;
    tempNode_1->ParentNode = NULL;
    tempNode_1->vChilds.clear();
    PsdMap::getInstance()->setTree(tempNode_1);
    EXPECT_EQ(PsdLocation::getInstance()->calcRoadSegmentClass(), RoadClass_highway);

    //case3: RoadClass_Non_urban
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    MapData_1.psd04RoadClass = NationalRoad;
    struct TreeNode *tempNode_2 = new struct TreeNode();
    tempNode_2->MapData = MapData_1;
    tempNode_2->ParentNode = NULL;
    tempNode_2->vChilds.clear();
    PsdMap::getInstance()->setTree(tempNode_2);
    EXPECT_EQ(PsdLocation::getInstance()->calcRoadSegmentClass(), RoadClass_Non_urban);

    //case4: RoadClass_Non_urban
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    MapData_1.psd04RoadClass = ProvincialRoad;
    struct TreeNode *tempNode_3 = new struct TreeNode();
    tempNode_3->MapData = MapData_1;
    tempNode_3->ParentNode = NULL;
    tempNode_3->vChilds.clear();
    PsdMap::getInstance()->setTree(tempNode_3);
    EXPECT_EQ(PsdLocation::getInstance()->calcRoadSegmentClass(), RoadClass_Non_urban);

    //case5: RoadClass_Urban
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    MapData_1.psd04RoadClass = LocalRoad;
    struct TreeNode *tempNode_4 = new struct TreeNode();
    tempNode_4->MapData = MapData_1;
    tempNode_4->ParentNode = NULL;
    tempNode_4->vChilds.clear();
    PsdMap::getInstance()->setTree(tempNode_4);
    EXPECT_EQ(PsdLocation::getInstance()->calcRoadSegmentClass(), RoadClass_Urban);

    //case6: RoadClass_Urban
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    MapData_1.psd04RoadClass = CountyRoad;
    struct TreeNode *tempNode_5 = new struct TreeNode();
    tempNode_5->MapData = MapData_1;
    tempNode_5->ParentNode = NULL;
    tempNode_5->vChilds.clear();
    PsdMap::getInstance()->setTree(tempNode_5);
    EXPECT_EQ(PsdLocation::getInstance()->calcRoadSegmentClass(), RoadClass_Urban);

    //case7: HV's segment is not matched mTree, RoadClass_Unkown
    curSegment.curSegmentId = 2;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->calcRoadSegmentClass(), RoadClass_Unkown);

    /**
     * @brief 
     * typedef enum eRoadSegmentClass{
     * RoadClass_Unkown = 0,
     * RoadClass_highway = 1,
     * RoadClass_Non_urban = 2,
     * RoadClass_Urban = 3
     * }RoadSegmentClass;
     * 
     * typedef enum ePsd04RoadClass{
     * PrivateRoad = 0,
     * LocalRoad = 1,
     * CountyRoad = 2,
     * NationalRoad = 3,
     * ProvincialRoad = 4,
     * Expressway = 5,
     * Init = 7
     * }Psd04RoadClass;
     */
    delete tempNode_0, tempNode_1, tempNode_2, tempNode_3, tempNode_4, tempNode_5;
}

/*test PsdAvailable function*/
TEST_F(PsdLocationTest, getPsdAvailable)
{
    //test initFunction: Psd initial data
    PsdLocation::getInstance()->initPsdData();

    //case1: mMapMutexIsLocked == true
    PsdMap::getInstance()->setMapMutexStatus(true);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case2: mMapMutexIsLocked == false
    PsdMap::getInstance()->setMapMutexStatus(false);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case3: curSegmentId == 0
    tSelfSegment curSegment;
    curSegment.curSegmentId = 0;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case4: curSegmentId == 1
    curSegment.curSegmentId = 1;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case5: curSegmentId == valid value
    curSegment.curSegmentId = 6;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case6: curSegment.posIsUnique == true
    curSegment.posIsUnique = true;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), true);

    //case7: curSegment.posIsUnique == false
    curSegment.posIsUnique = false;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);
    
    //case8: curSegment.posLengthErr == Pos_Init
    curSegment.posLengthErr = Pos_Init;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case9: curSegment.posLengthErr == Over50m
    curSegment.posLengthErr = Over50m;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case10: curSegment.posLengthErr == OffRoad
    curSegment.posLengthErr = OffRoad;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case11: curSegment.posLengthErr == Pos_0mTo2m
    curSegment.posLengthErr = Pos_0mTo2m;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case12: curSegment.posLengthErr == Pos_2mTo5m
    curSegment.posLengthErr = Pos_2mTo5m;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case13: curSegment.posLengthErr == Pos_5mTo10m
    curSegment.posLengthErr = Pos_5mTo10m;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case14: curSegment.posLengthErr == Pos_10mTo20m
    curSegment.posLengthErr = Pos_10mTo20m;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case15: curSegment.posLengthErr == Pos_20mTo50m
    curSegment.posLengthErr = Pos_20mTo50m;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), false);

    //case16: all conditions of if are not statisfied, go to else branch
    PsdMap::getInstance()->setMapMutexStatus(false);
    curSegment.curSegmentId = 6;
    curSegment.posIsUnique = true;
    curSegment.posLengthErr = Pos_10mTo20m;
    PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
    EXPECT_EQ(PsdLocation::getInstance()->getPsdAvailable(), true);
}

//test threadFunction
TEST_F(PsdLocationTest, threadFunction)
{
    PsdLocation::getInstance()->createDecoderThread();
    PsdLocation::getInstance()->createMapThread();
}

//test reserved function
TEST_F(PsdLocationTest, reservedFunction)
{
    PsdLocation::getInstance()->getEventDistance();
    PsdLocation::getInstance()->getDiagnoticsParameter();
}

/*test ~PsdLocation()*/
TEST_F(PsdLocationTest, destructor)
{
    PsdLocation psdLocation;
}

/**
 * @brief HaversineTest
 */
TEST_F(PsdLocationTest, HaversineTest)
{
    Haversine haversine;
}
#endif

/**
 * @brief PsdMessageDecoderTest
 */

class PsdMessageDecoderTest : public testing::Test
{
protected:
    PsdMessageDecoder *pInstance;
    PsdMessageDecoder *getInstance()
    {
        if (NULL == pInstance)
        {
            pInstance = new PsdMessageDecoder();
        }
        return pInstance;
    }

    void SetUp()
    {
        pInstance = NULL;
    }
    void TerDown()
    {
        delete pInstance;
    }
};

#if 0
TEST_F(PsdMessageDecoderTest, segmentManager)
{
    //case1
    struct PsdMapData MapData_1;
    if (PsdMap::getInstance()->getTree() != NULL)
    {
        PsdMap::getInstance()->mapClear(PsdMap::getInstance()->getTree());
    }
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 110;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 1.0 / 60.5577;
    MapData_1.signEndCurvature = 0;
    MapData_1.mpp = 1;
    MapData_1.sp = 0;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 1.0 / 60.5577;
    MapData_1.signStartCurvature = 0;
    MapData_1.branchDirection = 0;
    MapData_1.branchAngle = 0.0; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = 0.0;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_1);
    PsdMessageDecoder::getInstance()->calcPsd04Data();
    PsdMessageDecoder::getInstance()->segmentManager(true);

    //case2: signStartCurvature == 1, signEndCurvature == 1, branchDirection == 1
    MapData_1.signEndCurvature = 1;
    MapData_1.signStartCurvature = 1;
    MapData_1.branchDirection = 1;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_1);
    PsdMessageDecoder::getInstance()->calcPsd04Data();

    //case3: vPsdMap already have this preSegmentId
    PsdMessageDecoder::getInstance()->segmentManager(true);

    //case4: segmentIsComplete == false
    struct PsdMapData MapData_2;
    MapData_2.preSegmentId = 4;
    MapData_2.segmentIsComplete = 0;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_2);
    PsdMessageDecoder::getInstance()->segmentManager(true);

    //case5: PsdUsageActive == false
    PsdMessageDecoder::getInstance()->segmentManager(false);    //after this execute, vPsdMap is already empty

    //case6: vPsdMap.empty() == true
    PsdMessageDecoder::getInstance()->segmentManager(false);
}

TEST_F(PsdMessageDecoderTest, saveAttributToList)
{
    //case1: psdAttribut1ID == 4
    struct PsdMapData MapData_1;
    if (!PsdMessageDecoder::getInstance()->getVPsdMap().empty())
    {
        PsdMessageDecoder::getInstance()->getVPsdMap().clear();
    }
    MapData_1.preSegmentId = 3;
    MapData_1.prevSegmentId = 2;
    MapData_1.preSegTotalLength = 110;
    MapData_1.psd04RoadClass = CountyRoad;
    MapData_1.endCurvature = 1.0 / 60.5577;
    MapData_1.signEndCurvature = 0;
    MapData_1.mpp = 1;
    MapData_1.sp = 0;
    MapData_1.segmentIsComplete = 1;
    MapData_1.startCurvature = 1.0 / 60.5577;
    MapData_1.signStartCurvature = 0;
    MapData_1.branchDirection = 0;
    MapData_1.branchAngle = 0.0; 
    MapData_1.segIsInTree = false;
    MapData_1.accumulateBranchAngle = 0.0;
    MapData_1.psdAttribut1ID = 4;
    MapData_1.psdAttribut1Wert = 0; //NoSeperation
    MapData_1.psdAttributSegmentID = 3;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_1);
    PsdMessageDecoder::getInstance()->calcPsd04Data();
    PsdMessageDecoder::getInstance()->segmentManager(true);
    PsdMessageDecoder::getInstance()->saveAttributToList();

    //case2: psdAttribut2ID == 4
    PsdMessageDecoder::getInstance()->segmentManager(false);
    MapData_1.psdAttribut1ID = 0;
    MapData_1.psdAttribut2ID = 4;
    MapData_1.psdAttribut2Wert = 0;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_1);
    PsdMessageDecoder::getInstance()->segmentManager(true);
    PsdMessageDecoder::getInstance()->saveAttributToList();

    //case3: psdAttribut3ID == 4
    PsdMessageDecoder::getInstance()->segmentManager(false);
    MapData_1.psdAttribut2ID = 0;
    MapData_1.psdAttribut3ID = 4;
    MapData_1.psdAttribut3Wert = 0;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_1);
    PsdMessageDecoder::getInstance()->segmentManager(true);
    PsdMessageDecoder::getInstance()->saveAttributToList();

    //case4: psdAttribut4ID == 4
    PsdMessageDecoder::getInstance()->segmentManager(false);
    MapData_1.psdAttribut3ID = 0;
    MapData_1.psdAttribut4ID = 4;
    MapData_1.psdAttribut4Wert = 0;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_1);
    PsdMessageDecoder::getInstance()->segmentManager(true);
    PsdMessageDecoder::getInstance()->saveAttributToList();

    //case5: psdAttribut5ID == 4
    PsdMessageDecoder::getInstance()->segmentManager(false);
    MapData_1.psdAttribut4ID = 0;
    MapData_1.psdAttribut5ID = 4;
    MapData_1.psdAttribut5Wert = 0;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_1);
    PsdMessageDecoder::getInstance()->segmentManager(true);
    PsdMessageDecoder::getInstance()->saveAttributToList();

    //case6: psdAttributXID == invalid value
    PsdMessageDecoder::getInstance()->segmentManager(false);
    MapData_1.psdAttribut5ID = 0; //invalid value
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_1);
    PsdMessageDecoder::getInstance()->segmentManager(true);
    PsdMessageDecoder::getInstance()->saveAttributToList();

    //case7: (*it)->preSegmentId != PsdMapData.psdAttributSegmentID
    struct PsdMapData MapData_2;
    MapData_2.psdAttributSegmentID = 0;
    PsdMessageDecoder::getInstance()->setPsdMapData(MapData_2);
    PsdMessageDecoder::getInstance()->saveAttributToList();

    //case8: vPsdMap is empty
    PsdMessageDecoder::getInstance()->segmentManager(false);
    PsdMessageDecoder::getInstance()->saveAttributToList();
}

TEST_F(PsdMessageDecoderTest, destructor)
{
    PsdMessageDecoder psdMessageDecoder;
}
#endif

bool isNumber(const std::string& str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

#if 0
TEST_F(PsdMapTest, useRealRecordPsdWithSP)
{
    std::string filename = "/home/zhao/Documents/Psd/gtest/src/parsed_data_copy.txt";
    std::ifstream file(filename);
    std::string line;
    bool psd04Valid = false;
    bool psd05Valid = false;
    double headingAccuracy = 9.15;
    double lastHeadingAccuracy = 9.15;
    tSelfSegment curSegment;
    if (file.is_open())
    {
        std::cout << "open successfully" << std::endl;
        while (std::getline(file, line))
        {
            std::string keyValuePair = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1);
            std::map<std::string, std::string> keyValueMap;
            std::istringstream tokenStream(keyValuePair);
            std::string token;
            // 解析每个键值对，并存入keyValueMap中
            while (std::getline(tokenStream, token, ','))
            {
                std::istringstream keyValue(token);  // 一个键值对，'PSD_Pos_Segment_ID': 14
                std::string key;
                std::string value;
                std::getline(keyValue, key, ':');                        
                key.erase(0, key.find_first_not_of(" '"));
                key.erase(key.find_last_not_of(" '") + 1); 
                std::getline(keyValue, value);
                value.erase(0, value.find_first_not_of(" '"));
                value.erase(value.find_last_not_of(" '") + 1);
                if (!value.empty() && value.front() == '\'') 
                {
                    value.erase(0, 1);
                }
                if (!value.empty() && value.back() == '\'')
                {
                    value.pop_back();
                }
                keyValueMap[key] = value;
            }
            /*文本中当前行的键值对都已存入keyValueMap*/
            tPsdMapData *pPsdMapData = new(tPsdMapData);
            // PSD_Segment_ID
            std::string keyPsdSegmentID = "PSD_Segment_ID";
            std::map<std::string, std::string>::iterator iterPsd04 = keyValueMap.find(keyPsdSegmentID);
            // PSD_Pos_Segment_ID
            std::string keyPsdPosSegmentID = "PSD_Pos_Segment_ID";
            std::map<std::string, std::string>::iterator iterPsd05 = keyValueMap.find(keyPsdPosSegmentID);
            // GNSS_Nachrichtenpaket_ID1
            std::string keyGnss_01 = "GNSS_Nachrichtenpaket_ID1";
            std::map<std::string, std::string>::iterator iterGnss_01 = keyValueMap.find(keyGnss_01);
            // GNSS_Nachrichtenpaket_ID2
            std::string keyGnss_02 = "GNSS_Nachrichtenpaket_ID2";
            std::map<std::string, std::string>::iterator iterGnss_02 = keyValueMap.find(keyGnss_02);
            // GNSS_Ortung_Guete_Ausrichtung
            std::string keyGnss_03 = "GNSS_Ortung_Guete_Ausrichtung";
            std::map<std::string, std::string>::iterator iterGnss_03 = keyValueMap.find(keyGnss_03);

            if (iterPsd04 != keyValueMap.end())
            {
                /*PSD_Segment_ID*/
                std::map<std::string, std::string>::iterator iter = keyValueMap.find("PSD_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Segmentinformationen vorhanden"))
                {
                    psd04Valid = true;
                    pPsdMapData->preSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: preSegmentId = %u\n", __FUNCTION__, __LINE__, pPsdMapData->preSegmentId);
                }
                else
                {
                    psd04Valid = false;
                }
                /*PSD_Vorgaenger_Segment_ID*/
                iter = keyValueMap.find("PSD_Vorgaenger_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Segmentinformation vorhanden"))
                {
                    if (isNumber(iter->second))
                    {
                        psd04Valid = true;
                        pPsdMapData->prevSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                        printf("[%s] [%d]: prevSegmentId = %u\n", __FUNCTION__, __LINE__, pPsdMapData->prevSegmentId);
                    }
                }
                else
                {
                    psd04Valid = false;
                }
                
                if (psd04Valid == true)
                {
                    /*PSD_Segmentlaenge*/
                    iter = keyValueMap.find("PSD_Segmentlaenge");
                    pPsdMapData->preSegTotalLength = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: preSegTotalLength = %u\n", __FUNCTION__, __LINE__, pPsdMapData->preSegTotalLength);
                    /*PSD_Strassenkategorie*/
                    iter = keyValueMap.find("PSD_Strassenkategorie");
                    if (iter->second == "Rest_Feldweg_Schotterweg_Privatweg")
                    {
                        pPsdMapData->psd04RoadClass = PrivateRoad;
                    }
                    else if (iter->second == "Ortsstraße")
                    {
                        pPsdMapData->psd04RoadClass = LocalRoad;
                    }
                    else if (iter->second == "Kreisstraße")
                    {
                        pPsdMapData->psd04RoadClass = CountyRoad;
                    }
                    else if (iter->second == "Landstraße")
                    {
                        pPsdMapData->psd04RoadClass = NationalRoad;
                    }
                    else if (iter->second == "Bundesstraße")
                    {
                        pPsdMapData->psd04RoadClass = ProvincialRoad;
                    }
                    else if (iter->second == "Autobahn")
                    {
                        pPsdMapData->psd04RoadClass = Expressway;
                    }
                    else if (iter->second == "Init")
                    {
                        pPsdMapData->psd04RoadClass = Init;
                    }
                    /*PSD_Endkruemmung && PSD_Endkruemmung_Vorz*/
                    iter = keyValueMap.find("PSD_Endkruemmung");
                    if ((iter->second == "Gerade") || (iter->second == "0"))
                    {
                        pPsdMapData->endCurvature = 0.0;
                        pPsdMapData->sp = 1; 
                    }
                    else
                    {
                        pPsdMapData->endCurvature = static_cast<double> (std::stod(iter->second));
                        iter = keyValueMap.find("PSD_Endkruemmung_Vorz");
                        if (iter->second == "Kruemmung_positiv")
                        {
                            pPsdMapData->signEndCurvature = 0;
                        }
                        else 
                        if (iter->second == "Kruemmung_negativ")
                        {
                            pPsdMapData->signEndCurvature = 1;
                        }
                        pPsdMapData->endCurvature = (1.0f / (1 + 0.155 * pow(pPsdMapData->endCurvature, 2))) * (pPsdMapData->signEndCurvature ? -1 : 1);
                    }
                    /*PSD_wahrscheinlichster_Pfad*/
                    iter = keyValueMap.find("PSD_wahrscheinlichster_Pfad");
                    if (iter->second == "keine_Segment_Informationen_vorhanden")
                    {
                        pPsdMapData->mpp = 0;
                    }
                    else 
                    if (iter->second  == "wahrscheinlichster_Pfad")
                    {
                        pPsdMapData->mpp =1;
                    }
                    /*PSD_Geradester_Pfad*/
                    iter = keyValueMap.find("PSD_Geradester_Pfad");
                    if (iter->second == "nicht_geradester_PFad")
                    {
                        pPsdMapData->sp = 0;
                    }
                    else 
                    if (iter->second == "geradester_Pfad")
                    {
                        pPsdMapData->sp = 1;
                    }
                    /*PSD_Segment_Komplett*/
                    iter = keyValueMap.find("PSD_Segment_Komplett");
                    if (iter->second == "Segment_Attribute_nicht_komplett")
                    {
                        pPsdMapData->segmentIsComplete = 0;
                    }
                    else if (iter->second == "Segment_Attribute_komplett")
                    {
                        pPsdMapData->segmentIsComplete = 1;
                    }
                    /*PSD_Anfangskruemmung && PSD_Anfangskruemmung_Vorz*/
                    iter = keyValueMap.find("PSD_Anfangskruemmung");
                    if ((iter->second == "Gerade") || (iter->second == "0"))
                    {
                        pPsdMapData->endCurvature = 0.0;
                        pPsdMapData->sp = 1; 
                    }
                    else
                    {
                        pPsdMapData->startCurvature = static_cast<double> (std::stod(iter->second));
                        iter = keyValueMap.find("PSD_Anfangskruemmung_Vorz");
                        if (iter->second == "positiv")
                        {
                            pPsdMapData->signStartCurvature = 0;
                        }
                        else 
                        if (iter->second == "negativ")
                        {
                            pPsdMapData->signStartCurvature = 1;
                        }
                        pPsdMapData->startCurvature = (1.0f / (1 + 0.155 * pow(pPsdMapData->startCurvature, 2))) * (pPsdMapData->signStartCurvature ? -1 : 1);
                    }
                    /*PSD_Abzweigerichtung && PSD_Abzweigewinkel*/
                    iter = keyValueMap.find("PSD_Abzweigerichtung");
                    if (iter->second == "rects_abzweigende_Strasse")
                    {
                        pPsdMapData->branchDirection = 0;
                    }
                    else if (iter->second == "links_abzweigende_Strasse")
                    {
                        pPsdMapData->branchDirection = 1;
                    }
                    iter = keyValueMap.find("PSD_Abzweigewinkel");
                    pPsdMapData->branchAngle = static_cast<double> (std::stod(iter->second));
                    pPsdMapData->branchAngle = pPsdMapData->branchAngle * (pPsdMapData->branchDirection ? -1 : 1);
                    PsdMessageDecoder::getInstance()->getVPsdMap().emplace_back(pPsdMapData);
                }
            }
            else 
            if (iterPsd05 != keyValueMap.end())
            {
                /*PSD_Pos_Segment_ID*/
                std::map<std::string, std::string>::iterator iter = keyValueMap.find("PSD_Pos_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Position gegeben"))
                {
                    psd05Valid = true;
                    curSegment.curSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: curSegmentId = %u\n", __FUNCTION__, __LINE__, curSegment.curSegmentId);
                }
                else
                {
                    psd05Valid = false;
                }

                if (psd05Valid == true)
                {
                    /*PSD_Pos_Segmentlaenge*/
                    iter = keyValueMap.find("PSD_Pos_Segmentlaenge");
                    curSegment.curRemainLength = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: curRemainLength = %u\n", __FUNCTION__, __LINE__, curSegment.curRemainLength);

                    /*PSD_Pos_Standort_Eindeutig*/
                    iter = keyValueMap.find("PSD_Pos_Standort_Eindeutig");
                    if ("mehrdeutiger_Standort")
                    {
                        curSegment.posIsUnique = 0;
                    }   
                    else if ("eindeutiger_Standort")
                    {
                        curSegment.posIsUnique = 1;
                    }
                    /*PSD_Pos_Fehler_Laengsrichtung*/
                    iter = keyValueMap.find("PSD_Pos_Fehler_Laengsrichtung");             
                    if (iter->second == "Init")
                    {
                        curSegment.posLengthErr = Pos_Init;
                    }
                    else if (iter->second == "< 2m")
                    {
                        curSegment.posLengthErr = Pos_0mTo2m;
                    }
                    else if (iter->second == "< 5m")
                    {
                        curSegment.posLengthErr = Pos_2mTo5m;
                    }
                    else if (iter->second == "< 10m")
                    {
                        curSegment.posLengthErr = Pos_5mTo10m;
                    }
                    else if (iter->second == "< 20m")
                    {
                        curSegment.posLengthErr = Pos_10mTo20m;
                    }
                    else if (iter->second == "< 50m")
                    {
                        curSegment.posLengthErr =  Pos_20mTo50m;
                    }
                    else if (iter->second == "> 50m")
                    {
                        curSegment.posLengthErr =  Over50m;
                    }
                    else if (iter->second == "Off-Road")
                    {
                        curSegment.posLengthErr =  OffRoad;
                    }
                }
            }
            else 
            if (iterGnss_01 != keyValueMap.end())
            {
                /*GNSS_Breite_Ortung && GNSS_Richtung_Breite_Ortung*/
                iterGnss_01 = keyValueMap.find("GNSS_Breite_Ortung");
                std::map<std::string, std::string>::iterator iterGnss_01Sign = keyValueMap.find("GNSS_Richtung_Breite_Ortung");
                if ((iterGnss_01->second != "Init") && (iterGnss_01->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        if (iterGnss_01Sign->second == "Nord")
                        {
                            curSegment.hvCoordinate.latitude = static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        else
                        {
                            curSegment.hvCoordinate.latitude = (-1) * static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        printf("[%s] [%d]: curSegment's latitude = %lf\n", __FUNCTION__, __LINE__, curSegment.hvCoordinate.latitude);
                    }
                }
                /*GNSS_Laenge_Ortung && GNSS_Richtung_Laenge_Ortung*/
                iterGnss_01 = keyValueMap.find("GNSS_Laenge_Ortung");
                iterGnss_01Sign = keyValueMap.find("GNSS_Richtung_Laenge_Ortung");
                if ((iterGnss_01->second != "Init") && (iterGnss_01->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        if (iterGnss_01Sign->second == "Ost")
                        {
                            curSegment.hvCoordinate.longitude = static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        else
                        {
                            curSegment.hvCoordinate.longitude = (-1) * static_cast<double>(std::stod(iterGnss_01->second)); 
                        }
                        printf("[%s] [%d]: curSegment's longitude = %lf\n", __FUNCTION__, __LINE__, curSegment.hvCoordinate.longitude);
                    }        
                }
            }
            else 
            if (iterGnss_02 != keyValueMap.end())
            {
                /*GNSS_Ortung_Ausrichtung*/
                iterGnss_02 = keyValueMap.find("GNSS_Ortung_Ausrichtung");
                if ((iterGnss_02->second != "Init") && (iterGnss_02->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        curSegment.hvHeading = static_cast<double>(std::stod(iterGnss_02->second));
                    }
                }
                printf("[%s] [%d]: hvHeading = %lf\n", __FUNCTION__, __LINE__, curSegment.hvHeading);
            }
            else 
            if (iterGnss_03 != keyValueMap.end())
            {
                /* GNSS_Ortung_Guete_Ausrichtung */
                if ((iterGnss_03->second != "Init") && (iterGnss_03->second != "Fehler"))
                {
                    headingAccuracy =  static_cast<double> (std::stod(iterGnss_03->second));
                    lastHeadingAccuracy = headingAccuracy; 
                }
                printf("[%s] [%d]: headingAccuracy = %lf\n", __FUNCTION__, __LINE__, headingAccuracy);
            }
            else
            {
                // 没有找到键
                std::cout << "键为 " << keyPsdSegmentID << " " << keyPsdPosSegmentID << " " <<   keyGnss_01 <<  " "  <<  keyGnss_02 <<  " " << " 的不存在" << std::endl;
            }
        }    
        PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
        PsdMap::getInstance()->mapCreate();
    }   
    else    
    {   
        std::cout << "cannot open" << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
    }   
}

TEST_F(PsdMapTest, useRealRecordPsdWithCurve_phase1)
{
    std::string filename = "/home/zhao/Documents/Psd/gtest/src/parsed_data_转盘(第一阶段).txt";
    std::ifstream file(filename);
    std::string line;
    bool psd04Valid = false;
    bool psd05Valid = false;
    double headingAccuracy = 9.15;
    double lastHeadingAccuracy = 9.15;
    tSelfSegment curSegment;
    if (file.is_open())
    {
        std::cout << "open successfully" << std::endl;
        while (std::getline(file, line))
        {
            std::string keyValuePair = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1);
            std::map<std::string, std::string> keyValueMap;
            std::istringstream tokenStream(keyValuePair);
            std::string token;
            while (std::getline(tokenStream, token, ','))
            {
                std::istringstream keyValue(token);  // 一个键值对，'PSD_Pos_Segment_ID': 14
                std::string key;
                std::string value;
                std::getline(keyValue, key, ':');                        
                key.erase(0, key.find_first_not_of(" '"));
                key.erase(key.find_last_not_of(" '") + 1); 
                std::getline(keyValue, value);
                value.erase(0, value.find_first_not_of(" '"));
                value.erase(value.find_last_not_of(" '") + 1);
                if (!value.empty() && value.front() == '\'') 
                {
                    value.erase(0, 1);
                }
                if (!value.empty() && value.back() == '\'')
                {
                    value.pop_back();
                }
                keyValueMap[key] = value;
            }
            tPsdMapData *pPsdMapData = new(tPsdMapData);
            // PSD_Segment_ID
            std::string keyPsdSegmentID = "PSD_Segment_ID";
            std::map<std::string, std::string>::iterator iterPsd04 = keyValueMap.find(keyPsdSegmentID);
            // PSD_Pos_Segment_ID
            std::string keyPsdPosSegmentID = "PSD_Pos_Segment_ID";
            std::map<std::string, std::string>::iterator iterPsd05 = keyValueMap.find(keyPsdPosSegmentID);
            // GNSS_Nachrichtenpaket_ID1
            std::string keyGnss_01 = "GNSS_Nachrichtenpaket_ID1";
            std::map<std::string, std::string>::iterator iterGnss_01 = keyValueMap.find(keyGnss_01);
            // GNSS_Nachrichtenpaket_ID2
            std::string keyGnss_02 = "GNSS_Nachrichtenpaket_ID2";
            std::map<std::string, std::string>::iterator iterGnss_02 = keyValueMap.find(keyGnss_02);
            // GNSS_Ortung_Guete_Ausrichtung
            std::string keyGnss_03 = "GNSS_Ortung_Guete_Ausrichtung";
            std::map<std::string, std::string>::iterator iterGnss_03 = keyValueMap.find(keyGnss_03);

            if (iterPsd04 != keyValueMap.end())
            {
                /*PSD_Segment_ID*/
                std::map<std::string, std::string>::iterator iter = keyValueMap.find("PSD_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Segmentinformationen vorhanden"))
                {
                    psd04Valid = true;
                    pPsdMapData->preSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: preSegmentId = %u\n", __FUNCTION__, __LINE__, pPsdMapData->preSegmentId);
                }
                else
                {
                    psd04Valid = false;
                }
                /*PSD_Vorgaenger_Segment_ID*/
                iter = keyValueMap.find("PSD_Vorgaenger_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Segmentinformation vorhanden"))
                {
                    if (isNumber(iter->second))
                    {
                        psd04Valid = true;
                        pPsdMapData->prevSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                        printf("[%s] [%d]: prevSegmentId = %u\n", __FUNCTION__, __LINE__, pPsdMapData->prevSegmentId);
                    }
                }
                else
                {
                    psd04Valid = false;
                }
                
                if (psd04Valid == true)
                {
                    /*PSD_Segmentlaenge*/
                    iter = keyValueMap.find("PSD_Segmentlaenge");
                    pPsdMapData->preSegTotalLength = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: preSegTotalLength = %u\n", __FUNCTION__, __LINE__, pPsdMapData->preSegTotalLength);
                    /*PSD_Strassenkategorie*/
                    iter = keyValueMap.find("PSD_Strassenkategorie");
                    if (iter->second == "Rest_Feldweg_Schotterweg_Privatweg")
                    {
                        pPsdMapData->psd04RoadClass = PrivateRoad;
                    }
                    else if (iter->second == "Ortsstraße")
                    {
                        pPsdMapData->psd04RoadClass = LocalRoad;
                    }
                    else if (iter->second == "Kreisstraße")
                    {
                        pPsdMapData->psd04RoadClass = CountyRoad;
                    }
                    else if (iter->second == "Landstraße")
                    {
                        pPsdMapData->psd04RoadClass = NationalRoad;
                    }
                    else if (iter->second == "Bundesstraße")
                    {
                        pPsdMapData->psd04RoadClass = ProvincialRoad;
                    }
                    else if (iter->second == "Autobahn")
                    {
                        pPsdMapData->psd04RoadClass = Expressway;
                    }
                    else if (iter->second == "Init")
                    {
                        pPsdMapData->psd04RoadClass = Init;
                    }
                    /*PSD_Endkruemmung && PSD_Endkruemmung_Vorz*/
                    iter = keyValueMap.find("PSD_Endkruemmung");
                    if ((iter->second == "Gerade") || (iter->second == "0"))
                    {
                        pPsdMapData->endCurvature = 0.0;
                        pPsdMapData->sp = 1; 
                    }
                    else
                    {
                        pPsdMapData->endCurvature = static_cast<double> (std::stod(iter->second));
                        iter = keyValueMap.find("PSD_Endkruemmung_Vorz");
                        if (iter->second == "Kruemmung_positiv")
                        {
                            pPsdMapData->signEndCurvature = 0;
                        }
                        else 
                        if (iter->second == "Kruemmung_negativ")
                        {
                            pPsdMapData->signEndCurvature = 1;
                        }
                        pPsdMapData->endCurvature = (1.0f / (1 + 0.155 * pow(pPsdMapData->endCurvature, 2))) * (pPsdMapData->signEndCurvature ? -1 : 1);
                    }
                    /*PSD_wahrscheinlichster_Pfad*/
                    iter = keyValueMap.find("PSD_wahrscheinlichster_Pfad");
                    if (iter->second == "keine_Segment_Informationen_vorhanden")
                    {
                        pPsdMapData->mpp = 0;
                    }
                    else 
                    if (iter->second  == "wahrscheinlichster_Pfad")
                    {
                        pPsdMapData->mpp =1;
                    }
                    /*PSD_Geradester_Pfad*/
                    iter = keyValueMap.find("PSD_Geradester_Pfad");
                    if (iter->second == "nicht_geradester_PFad")
                    {
                        pPsdMapData->sp = 0;
                    }
                    else 
                    if (iter->second == "geradester_Pfad")
                    {
                        pPsdMapData->sp = 1;
                    }
                    /*PSD_Segment_Komplett*/
                    iter = keyValueMap.find("PSD_Segment_Komplett");
                    if (iter->second == "Segment_Attribute_nicht_komplett")
                    {
                        pPsdMapData->segmentIsComplete = 0;
                    }
                    else if (iter->second == "Segment_Attribute_komplett")
                    {
                        pPsdMapData->segmentIsComplete = 1;
                    }
                    /*PSD_Anfangskruemmung && PSD_Anfangskruemmung_Vorz*/
                    iter = keyValueMap.find("PSD_Anfangskruemmung");
                    if ((iter->second == "Gerade") || (iter->second == "0"))
                    {
                        pPsdMapData->endCurvature = 0.0;
                        pPsdMapData->sp = 1; 
                    }
                    else
                    {
                        pPsdMapData->startCurvature = static_cast<double> (std::stod(iter->second));
                        iter = keyValueMap.find("PSD_Anfangskruemmung_Vorz");
                        if (iter->second == "positiv")
                        {
                            pPsdMapData->signStartCurvature = 0;
                        }
                        else 
                        if (iter->second == "negativ")
                        {
                            pPsdMapData->signStartCurvature = 1;
                        }
                        pPsdMapData->startCurvature = (1.0f / (1 + 0.155 * pow(pPsdMapData->startCurvature, 2))) * (pPsdMapData->signStartCurvature ? -1 : 1);
                    }
                    /*PSD_Abzweigerichtung && PSD_Abzweigewinkel*/
                    iter = keyValueMap.find("PSD_Abzweigerichtung");
                    if (iter->second == "rects_abzweigende_Strasse")
                    {
                        pPsdMapData->branchDirection = 0;
                    }
                    else if (iter->second == "links_abzweigende_Strasse")
                    {
                        pPsdMapData->branchDirection = 1;
                    }
                    iter = keyValueMap.find("PSD_Abzweigewinkel");
                    pPsdMapData->branchAngle = static_cast<double> (std::stod(iter->second));
                    pPsdMapData->branchAngle = pPsdMapData->branchAngle * (pPsdMapData->branchDirection ? -1 : 1);
                    PsdMessageDecoder::getInstance()->getVPsdMap().emplace_back(pPsdMapData);
                }
            }
            else 
            if (iterPsd05 != keyValueMap.end())
            {
                /*PSD_Pos_Segment_ID*/
                std::map<std::string, std::string>::iterator iter = keyValueMap.find("PSD_Pos_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Position gegeben"))
                {
                    psd05Valid = true;
                    curSegment.curSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: curSegmentId = %u\n", __FUNCTION__, __LINE__, curSegment.curSegmentId);
                }
                else
                {
                    psd05Valid = false;
                }

                if (psd05Valid == true)
                {
                    /*PSD_Pos_Segmentlaenge*/
                    iter = keyValueMap.find("PSD_Pos_Segmentlaenge");
                    curSegment.curRemainLength = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: curRemainLength = %u\n", __FUNCTION__, __LINE__, curSegment.curRemainLength);

                    /*PSD_Pos_Standort_Eindeutig*/
                    iter = keyValueMap.find("PSD_Pos_Standort_Eindeutig");
                    if ("mehrdeutiger_Standort")
                    {
                        curSegment.posIsUnique = 0;
                    }   
                    else if ("eindeutiger_Standort")
                    {
                        curSegment.posIsUnique = 1;
                    }
                    /*PSD_Pos_Fehler_Laengsrichtung*/
                    iter = keyValueMap.find("PSD_Pos_Fehler_Laengsrichtung");             
                    if (iter->second == "Init")
                    {
                        curSegment.posLengthErr = Pos_Init;
                    }
                    else if (iter->second == "< 2m")
                    {
                        curSegment.posLengthErr = Pos_0mTo2m;
                    }
                    else if (iter->second == "< 5m")
                    {
                        curSegment.posLengthErr = Pos_2mTo5m;
                    }
                    else if (iter->second == "< 10m")
                    {
                        curSegment.posLengthErr = Pos_5mTo10m;
                    }
                    else if (iter->second == "< 20m")
                    {
                        curSegment.posLengthErr = Pos_10mTo20m;
                    }
                    else if (iter->second == "< 50m")
                    {
                        curSegment.posLengthErr =  Pos_20mTo50m;
                    }
                    else if (iter->second == "> 50m")
                    {
                        curSegment.posLengthErr =  Over50m;
                    }
                    else if (iter->second == "Off-Road")
                    {
                        curSegment.posLengthErr =  OffRoad;
                    }
                }
            }
            else 
            if (iterGnss_01 != keyValueMap.end())
            {
                /*GNSS_Breite_Ortung && GNSS_Richtung_Breite_Ortung*/
                iterGnss_01 = keyValueMap.find("GNSS_Breite_Ortung");
                std::map<std::string, std::string>::iterator iterGnss_01Sign = keyValueMap.find("GNSS_Richtung_Breite_Ortung");
                if ((iterGnss_01->second != "Init") && (iterGnss_01->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        if (iterGnss_01Sign->second == "Nord")
                        {
                            curSegment.hvCoordinate.latitude = static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        else
                        {
                            curSegment.hvCoordinate.latitude = (-1) * static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        printf("[%s] [%d]: curSegment's latitude = %lf\n", __FUNCTION__, __LINE__, curSegment.hvCoordinate.latitude);
                    }
                }
                /*GNSS_Laenge_Ortung && GNSS_Richtung_Laenge_Ortung*/
                iterGnss_01 = keyValueMap.find("GNSS_Laenge_Ortung");
                iterGnss_01Sign = keyValueMap.find("GNSS_Richtung_Laenge_Ortung");
                if ((iterGnss_01->second != "Init") && (iterGnss_01->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        if (iterGnss_01Sign->second == "Ost")
                        {
                            curSegment.hvCoordinate.longitude = static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        else
                        {
                            curSegment.hvCoordinate.longitude = (-1) * static_cast<double>(std::stod(iterGnss_01->second)); 
                        }
                        printf("[%s] [%d]: curSegment's longitude = %lf\n", __FUNCTION__, __LINE__, curSegment.hvCoordinate.longitude);
                    }        
                }
            }
            else 
            if (iterGnss_02 != keyValueMap.end())
            {
                /*GNSS_Ortung_Ausrichtung*/
                iterGnss_02 = keyValueMap.find("GNSS_Ortung_Ausrichtung");
                if ((iterGnss_02->second != "Init") && (iterGnss_02->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        curSegment.hvHeading = static_cast<double>(std::stod(iterGnss_02->second));
                    }
                }
                printf("[%s] [%d]: hvHeading = %lf\n", __FUNCTION__, __LINE__, curSegment.hvHeading);
            }
            else 
            if (iterGnss_03 != keyValueMap.end())
            {
                /* GNSS_Ortung_Guete_Ausrichtung */
                if ((iterGnss_03->second != "Init") && (iterGnss_03->second != "Fehler"))
                {
                    headingAccuracy =  static_cast<double> (std::stod(iterGnss_03->second));
                    lastHeadingAccuracy = headingAccuracy; 
                }
                printf("[%s] [%d]: headingAccuracy = %lf\n", __FUNCTION__, __LINE__, headingAccuracy);
            }
            else
            {
                std::cout << "键为 " << keyPsdSegmentID << " " << keyPsdPosSegmentID << " " <<   keyGnss_01 <<  " "  <<  keyGnss_02 <<  " " << " 的不存在" << std::endl;
            }
        }    
        PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
        PsdMap::getInstance()->mapCreate();
    }   
    else    
    {   
        std::cout << "cannot open" << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
    }
}
#endif

TEST_F(PsdMapTest, useRealRecordPsdWithCurve_phase2)
{
    std::string filename = "/home/zhao/Documents/Psd/gtest/src/parsed_data_转盘(第二阶段).txt";
    std::ifstream file(filename);
    std::string line;
    bool psd04Valid = false;
    bool psd05Valid = false;
    double headingAccuracy = 9.15;
    double lastHeadingAccuracy = 9.15;
    tSelfSegment curSegment;
    if (file.is_open())
    {
        std::cout << "open successfully" << std::endl;
        while (std::getline(file, line))
        {
            std::string keyValuePair = line.substr(line.find("{") + 1, line.find("}") - line.find("{") - 1);
            std::map<std::string, std::string> keyValueMap;
            std::istringstream tokenStream(keyValuePair);
            std::string token;
            while (std::getline(tokenStream, token, ','))
            {
                std::istringstream keyValue(token);  // 一个键值对，'PSD_Pos_Segment_ID': 14
                std::string key;
                std::string value;
                std::getline(keyValue, key, ':');                        
                key.erase(0, key.find_first_not_of(" '"));
                key.erase(key.find_last_not_of(" '") + 1); 
                std::getline(keyValue, value);
                value.erase(0, value.find_first_not_of(" '"));
                value.erase(value.find_last_not_of(" '") + 1);
                if (!value.empty() && value.front() == '\'') 
                {
                    value.erase(0, 1);
                }
                if (!value.empty() && value.back() == '\'')
                {
                    value.pop_back();
                }
                keyValueMap[key] = value;
            }
            tPsdMapData *pPsdMapData = new(tPsdMapData);
            // PSD_Segment_ID
            std::string keyPsdSegmentID = "PSD_Segment_ID";
            std::map<std::string, std::string>::iterator iterPsd04 = keyValueMap.find(keyPsdSegmentID);
            // PSD_Pos_Segment_ID
            std::string keyPsdPosSegmentID = "PSD_Pos_Segment_ID";
            std::map<std::string, std::string>::iterator iterPsd05 = keyValueMap.find(keyPsdPosSegmentID);
            // GNSS_Nachrichtenpaket_ID1
            std::string keyGnss_01 = "GNSS_Nachrichtenpaket_ID1";
            std::map<std::string, std::string>::iterator iterGnss_01 = keyValueMap.find(keyGnss_01);
            // GNSS_Nachrichtenpaket_ID2
            std::string keyGnss_02 = "GNSS_Nachrichtenpaket_ID2";
            std::map<std::string, std::string>::iterator iterGnss_02 = keyValueMap.find(keyGnss_02);
            // GNSS_Ortung_Guete_Ausrichtung
            std::string keyGnss_03 = "GNSS_Ortung_Guete_Ausrichtung";
            std::map<std::string, std::string>::iterator iterGnss_03 = keyValueMap.find(keyGnss_03);

            if (iterPsd04 != keyValueMap.end())
            {
                /*PSD_Segment_ID*/
                std::map<std::string, std::string>::iterator iter = keyValueMap.find("PSD_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Segmentinformationen vorhanden"))
                {
                    psd04Valid = true;
                    pPsdMapData->preSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: preSegmentId = %u\n", __FUNCTION__, __LINE__, pPsdMapData->preSegmentId);
                }
                else
                {
                    psd04Valid = false;
                }
                /*PSD_Vorgaenger_Segment_ID*/
                iter = keyValueMap.find("PSD_Vorgaenger_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Segmentinformation vorhanden"))
                {
                    if (isNumber(iter->second))
                    {
                        psd04Valid = true;
                        pPsdMapData->prevSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                        printf("[%s] [%d]: prevSegmentId = %u\n", __FUNCTION__, __LINE__, pPsdMapData->prevSegmentId);
                    }
                }
                else
                {
                    psd04Valid = false;
                }
                
                if (psd04Valid == true)
                {
                    /*PSD_Segmentlaenge*/
                    iter = keyValueMap.find("PSD_Segmentlaenge");
                    pPsdMapData->preSegTotalLength = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: preSegTotalLength = %u\n", __FUNCTION__, __LINE__, pPsdMapData->preSegTotalLength);
                    /*PSD_Strassenkategorie*/
                    iter = keyValueMap.find("PSD_Strassenkategorie");
                    if (iter->second == "Rest_Feldweg_Schotterweg_Privatweg")
                    {
                        pPsdMapData->psd04RoadClass = PrivateRoad;
                    }
                    else if (iter->second == "Ortsstraße")
                    {
                        pPsdMapData->psd04RoadClass = LocalRoad;
                    }
                    else if (iter->second == "Kreisstraße")
                    {
                        pPsdMapData->psd04RoadClass = CountyRoad;
                    }
                    else if (iter->second == "Landstraße")
                    {
                        pPsdMapData->psd04RoadClass = NationalRoad;
                    }
                    else if (iter->second == "Bundesstraße")
                    {
                        pPsdMapData->psd04RoadClass = ProvincialRoad;
                    }
                    else if (iter->second == "Autobahn")
                    {
                        pPsdMapData->psd04RoadClass = Expressway;
                    }
                    else if (iter->second == "Init")
                    {
                        pPsdMapData->psd04RoadClass = Init;
                    }
                    /*PSD_Endkruemmung && PSD_Endkruemmung_Vorz*/
                    iter = keyValueMap.find("PSD_Endkruemmung");
                    if ((iter->second == "Gerade") || (iter->second == "0"))
                    {
                        pPsdMapData->endCurvature = 0.0;
                        pPsdMapData->sp = 1; 
                    }
                    else
                    {
                        pPsdMapData->endCurvature = static_cast<double> (std::stod(iter->second));
                        iter = keyValueMap.find("PSD_Endkruemmung_Vorz");
                        if (iter->second == "Kruemmung_positiv")
                        {
                            pPsdMapData->signEndCurvature = 0;
                        }
                        else 
                        if (iter->second == "Kruemmung_negativ")
                        {
                            pPsdMapData->signEndCurvature = 1;
                        }
                        pPsdMapData->endCurvature = (1.0f / (1 + 0.155 * pow(pPsdMapData->endCurvature, 2))) * (pPsdMapData->signEndCurvature ? -1 : 1);
                        pPsdMapData->sp = 0; 
                    }
                    /*PSD_wahrscheinlichster_Pfad*/
                    iter = keyValueMap.find("PSD_wahrscheinlichster_Pfad");
                    if (iter->second == "keine_Segment_Informationen_vorhanden")
                    {
                        pPsdMapData->mpp = 0;
                    }
                    else 
                    if (iter->second  == "wahrscheinlichster_Pfad")
                    {
                        pPsdMapData->mpp =1;
                    }
                    // /*PSD_Geradester_Pfad*/
                    // iter = keyValueMap.find("PSD_Geradester_Pfad");
                    // if (iter->second == "nicht_geradester_PFad")
                    // {
                    //     pPsdMapData->sp = 0;
                    // }
                    // else 
                    // if (iter->second == "geradester_Pfad")
                    // {
                    //     pPsdMapData->sp = 1;
                    // }
                    /*PSD_Segment_Komplett*/
                    iter = keyValueMap.find("PSD_Segment_Komplett");
                    if (iter->second == "Segment_Attribute_nicht_komplett")
                    {
                        pPsdMapData->segmentIsComplete = 0;
                    }
                    else if (iter->second == "Segment_Attribute_komplett")
                    {
                        pPsdMapData->segmentIsComplete = 1;
                    }
                    /*PSD_Anfangskruemmung && PSD_Anfangskruemmung_Vorz*/
                    iter = keyValueMap.find("PSD_Anfangskruemmung");
                    if ((iter->second == "Gerade") || (iter->second == "0"))
                    {
                        pPsdMapData->endCurvature = 0.0;
                        pPsdMapData->sp = 1; 
                    }
                    else
                    {
                        pPsdMapData->startCurvature = static_cast<double> (std::stod(iter->second));
                        iter = keyValueMap.find("PSD_Anfangskruemmung_Vorz");
                        if (iter->second == "positiv")
                        {
                            pPsdMapData->signStartCurvature = 0;
                        }
                        else 
                        if (iter->second == "negativ")
                        {
                            pPsdMapData->signStartCurvature = 1;
                        }
                        pPsdMapData->startCurvature = (1.0f / (1 + 0.155 * pow(pPsdMapData->startCurvature, 2))) * (pPsdMapData->signStartCurvature ? -1 : 1);
                        pPsdMapData->sp = 0; 
                    }
                    /*PSD_Abzweigerichtung && PSD_Abzweigewinkel*/
                    iter = keyValueMap.find("PSD_Abzweigerichtung");
                    if (iter->second == "rects_abzweigende_Strasse")
                    {
                        pPsdMapData->branchDirection = 0;
                    }
                    else if (iter->second == "links_abzweigende_Strasse")
                    {
                        pPsdMapData->branchDirection = 1;
                    }
                    iter = keyValueMap.find("PSD_Abzweigewinkel");
                    pPsdMapData->branchAngle = static_cast<double> (std::stod(iter->second));
                    pPsdMapData->branchAngle = pPsdMapData->branchAngle * (pPsdMapData->branchDirection ? -1 : 1);
                    PsdMessageDecoder::getInstance()->getVPsdMap().emplace_back(pPsdMapData);
                }
            }
            else 
            if (iterPsd05 != keyValueMap.end())
            {
                /*PSD_Pos_Segment_ID*/
                std::map<std::string, std::string>::iterator iter = keyValueMap.find("PSD_Pos_Segment_ID");
                if ((iter->second != "Fehlerwert") && (iter->second != "keine Position gegeben"))
                {
                    psd05Valid = true;
                    curSegment.curSegmentId = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: curSegmentId = %u\n", __FUNCTION__, __LINE__, curSegment.curSegmentId);
                }
                else
                {
                    psd05Valid = false;
                }

                if (psd05Valid == true)
                {
                    /*PSD_Pos_Segmentlaenge*/
                    iter = keyValueMap.find("PSD_Pos_Segmentlaenge");
                    curSegment.curRemainLength = static_cast<uint8_t> (std::stoi(iter->second));
                    printf("[%s] [%d]: curRemainLength = %u\n", __FUNCTION__, __LINE__, curSegment.curRemainLength);

                    /*PSD_Pos_Standort_Eindeutig*/
                    iter = keyValueMap.find("PSD_Pos_Standort_Eindeutig");
                    if ("mehrdeutiger_Standort")
                    {
                        curSegment.posIsUnique = 0;
                    }   
                    else if ("eindeutiger_Standort")
                    {
                        curSegment.posIsUnique = 1;
                    }
                    /*PSD_Pos_Fehler_Laengsrichtung*/
                    iter = keyValueMap.find("PSD_Pos_Fehler_Laengsrichtung");             
                    if (iter->second == "Init")
                    {
                        curSegment.posLengthErr = Pos_Init;
                    }
                    else if (iter->second == "< 2m")
                    {
                        curSegment.posLengthErr = Pos_0mTo2m;
                    }
                    else if (iter->second == "< 5m")
                    {
                        curSegment.posLengthErr = Pos_2mTo5m;
                    }
                    else if (iter->second == "< 10m")
                    {
                        curSegment.posLengthErr = Pos_5mTo10m;
                    }
                    else if (iter->second == "< 20m")
                    {
                        curSegment.posLengthErr = Pos_10mTo20m;
                    }
                    else if (iter->second == "< 50m")
                    {
                        curSegment.posLengthErr =  Pos_20mTo50m;
                    }
                    else if (iter->second == "> 50m")
                    {
                        curSegment.posLengthErr =  Over50m;
                    }
                    else if (iter->second == "Off-Road")
                    {
                        curSegment.posLengthErr =  OffRoad;
                    }
                }
            }
            else 
            if (iterGnss_01 != keyValueMap.end())
            {
                /*GNSS_Breite_Ortung && GNSS_Richtung_Breite_Ortung*/
                iterGnss_01 = keyValueMap.find("GNSS_Breite_Ortung");
                std::map<std::string, std::string>::iterator iterGnss_01Sign = keyValueMap.find("GNSS_Richtung_Breite_Ortung");
                if ((iterGnss_01->second != "Init") && (iterGnss_01->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        if (iterGnss_01Sign->second == "Nord")
                        {
                            curSegment.hvCoordinate.latitude = static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        else
                        {
                            curSegment.hvCoordinate.latitude = (-1) * static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        printf("[%s] [%d]: curSegment's latitude = %lf\n", __FUNCTION__, __LINE__, curSegment.hvCoordinate.latitude);
                    }
                }
                /*GNSS_Laenge_Ortung && GNSS_Richtung_Laenge_Ortung*/
                iterGnss_01 = keyValueMap.find("GNSS_Laenge_Ortung");
                iterGnss_01Sign = keyValueMap.find("GNSS_Richtung_Laenge_Ortung");
                if ((iterGnss_01->second != "Init") && (iterGnss_01->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        if (iterGnss_01Sign->second == "Ost")
                        {
                            curSegment.hvCoordinate.longitude = static_cast<double>(std::stod(iterGnss_01->second));
                        }
                        else
                        {
                            curSegment.hvCoordinate.longitude = (-1) * static_cast<double>(std::stod(iterGnss_01->second)); 
                        }
                        printf("[%s] [%d]: curSegment's longitude = %lf\n", __FUNCTION__, __LINE__, curSegment.hvCoordinate.longitude);
                    }        
                }
            }
            else 
            if (iterGnss_02 != keyValueMap.end())
            {
                /*GNSS_Ortung_Ausrichtung*/
                iterGnss_02 = keyValueMap.find("GNSS_Ortung_Ausrichtung");
                if ((iterGnss_02->second != "Init") && (iterGnss_02->second != "Fehler"))
                {
                    //TODO: filter GNSS_Ortung_Guete_Ausrichtung > 4.5
                    if (lastHeadingAccuracy <= 4.5)
                    {
                        curSegment.hvHeading = static_cast<double>(std::stod(iterGnss_02->second));
                    }
                }
                printf("[%s] [%d]: hvHeading = %lf\n", __FUNCTION__, __LINE__, curSegment.hvHeading);
            }
            else 
            if (iterGnss_03 != keyValueMap.end())
            {
                /* GNSS_Ortung_Guete_Ausrichtung */
                if ((iterGnss_03->second != "Init") && (iterGnss_03->second != "Fehler"))
                {
                    headingAccuracy =  static_cast<double> (std::stod(iterGnss_03->second));
                    lastHeadingAccuracy = headingAccuracy; 
                }
                printf("[%s] [%d]: headingAccuracy = %lf\n", __FUNCTION__, __LINE__, headingAccuracy);
            }
            else
            {
                std::cout << "键为 " << keyPsdSegmentID << " " << keyPsdPosSegmentID << " " <<   keyGnss_01 <<  " "  <<  keyGnss_02 <<  " " << " 的不存在" << std::endl;
            }
        }    
        PsdMessageDecoder::getInstance()->setSelfSegment(curSegment);
        PsdMap::getInstance()->mapCreate();
        
        /*TODO: Ro locates the predicted segment of HV*/
        //Ro_1
        // Position3D RoPoint                                    
        // RoPoint.lat = ;
        // RoPoint.lon = ;
        // RoPoint.elevation = 0.0;     
        // PsdLocation::getInstance()->RoMatchSegment(RoPoint);
    }   
    else    
    {   
        std::cout << "cannot open" << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
    }
}


int main(int argc, char **argv)
{
    testing::AddGlobalTestEnvironment;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

