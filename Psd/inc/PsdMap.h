/*********************************************************************************
 * Copyright (c) 202x Cariad China. All rights reserved.
 * FileName:	 PsdMap.h
 * Author: 	     ZhaoZijia
 * Version :	 Ver0.1
 * Date:		 2023-11-03
 * Description: create and update PsdMap, calculate latitude and logitude coordinates
 *
 *********************************************************************************/

#ifndef _PSDMAP_H_
#define _PSDMAP_H_

/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include "PsdMessageDecoder.h"
#include "Haversine.h"

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/
 const double MaxRoadError = 7.0;
 
/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/
//TreeNode
typedef struct TreeNode{
    tPsdMapData MapData;                                     //Each data filed of segment is tPsdMapData's type
    struct TreeNode *ParentNode;                       //point the parent segment of HV
    std::vector< struct TreeNode *> vChilds;   //point the child segment of HV
}tTreeNode;

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: extern
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/
//pthread_t mapThread;
/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
class PsdMap{
public:
    /**
     * @brief Get the Instance object
     * @return PsdMap* (PsdMap)
     */
    static PsdMap* getInstance();
    
    struct TreeNode *mTree;                                    /** <  Root node of segment, representing the root node of the tree*/

    pthread_mutex_t mapThreadMutex;            /** <  Mutex for PsdMap thread*/

    bool mMapMutexIsLocked;                               /** <  the status of Mutex whether is locked or not*/

    // tOffset disHv2EndBeforeRotatingCoord;    /** <  distance from the HV to the end point before the rotation coordinate system*/

    // tOffset disHv2StartBeforeRotatingCoord;  /** <  distance from the HV to the start point before the rotation coordinate system*/

    tOffset disHv2EndAfterRotatingCoord;    /** <  distance from the HV to the end point after the rotation coordinate system*/

    tOffset disHv2StartAfterRotatingCoord;  /** <  distance from the HV to the start point after the rotation coordinate system*/

    double accumulateBranchAngleHv2End;   /** <  the accumulate branchAngle of HV position to endpoint*/
    
    double accumulateBranchAngleHv2Start; /** <  the accumulate branchAngle of HV position to startpoint*/

    double parentRelativeCurrentAngle;            /** <  the branchAngle of current segment relative parent segment */

    double rootRelativeParentAngle;                   /** <  the branchAngle of root segment relative parent segment */  

    /**
     * @brief Find CurSegmentId whether in list or not
     * @return struct PsdMapData* (the location of the list where HV is located, otherwise return NULL)
     */
    struct PsdMapData * curIdIsInList();

    /**
     * @brief Start triggering create map action
     */
    void mapCreate();

    /**
     * @brief Start triggering update map(the tree) action
     */
    void mapUpdate();

   /**
    * @brief  Start triggering clear map action
    * @param Node (start clearing from mTree)
    */
    void mapClear(struct TreeNode *Node);

    /**
     * @brief Insert vPsdMap's data element in mTree
     */
    void insertNodeInTree();

    /**
     * @brief Insert recursively HV's parent, root, childs or child's childs  node
     * @param Node (can represent any node)
     */
    void insertNode(struct TreeNode *Node, std::vector<struct PsdMapData *>::iterator it);

    /**
     * @brief Insert root node in mTree 
     * @param Node 
     * @param it (indicate the root segment of container)
     * @return struct TreeNode* (return rootNode)
     */
    struct TreeNode *insertRootNode(struct TreeNode *Node, std::vector<struct PsdMapData *>::iterator it);
    
    /**
     * @brief Insert parent node in mTree
     * @param Node 
     * @param it (indicate the parent segment of container)
     * @return struct TreeNode* (return parentNode)
     */
    struct TreeNode *insertParentNode(struct TreeNode *Node, std::vector<struct PsdMapData *>::iterator it);
    
    /**
     * @brief insert child nodes in mTree
     * @param tempNode (Indicates the previous segment of any segment in the container)
     * @param it (indicate the each segments of container)
     * @return struct TreeNode* (return childNode)
     */
    struct TreeNode *insertChildNode(struct TreeNode *tempNode, std::vector<struct PsdMapData *>::iterator it);

    /**
     * @brief Create a Node object
     * @return struct TreeNode* 
     */
    struct TreeNode *createNode();

    /**
     * @brief Start triggering update root(mTree) action
     */
    void updateRootNode();

    /**
     * @brief Delete subTree (update newParent, newCurrent, newChilds)
     */
    void updateOtherNode();

    /**
     * @brief for mapUpdate, just update child nodes
     * @param it (each segment elements in vPsdMap)
     */
    void updateChildNode(std::vector<struct PsdMapData *>::iterator it);

    /**
     * @brief DFS the tree, calculate all child nodes's end (latitude, longitude)
     * @param Node (start with current segment)
     */
    void dfsCalcChildCoord(struct TreeNode *Node);

    /**
     * @brief Clearing all nodes of mTree actually
     * @param Node (can represent any node) 
     */
    void clearNodeOutTree(struct TreeNode *Node);

    /**
     * @brief Delete old root
     * @return struct TreeNode* (returns new root if mTree is not NULL, otherwise returns NULL)
     */
    struct TreeNode *deleteOldRoot();

    /**
     * @brief Delete sub tree
     * @param Node (can represent any node) 
     */
    void deleteSubTree(struct TreeNode *Node);

    /**
     * @brief delete vChilds except current, travers peer vChilds of current segment 
     * @param Node (delete this node's child nodes)
     */
    void deleteNodeExceptCurrent(struct TreeNode *Node);

    /**
     * @brief Find in mTree by the known id 
     * @param Node (can represent any node)
     * @param KnownId 
     * @return struct TreeNode* (returns the corresponding node in the mTree if found, otherwise returns NULL)
     */
    struct TreeNode *findNodeById(struct TreeNode *Node, uint8_t KnownId);

    /**
     * @brief Calculate coordinate distinguish between straight path and curved line
     * @param Node (can represent any node)
     * @return struct PsdMapData (data fields for each node)
     */
    struct PsdMapData calcCoordinate(struct TreeNode *Node);

    /**
     * @brief Calculate start and end coordinate of the segment of HV 
     * @param curNode 
     * @return struct PsdMapData 
     */
    struct PsdMapData calcCurSegmentCoordinate(struct TreeNode *curNode);

    /**
     * @brief Calculate the segment of root and parent end coordinate
     * @param rootOrParentNode 
     * @return struct PsdMapData 
     */
    struct PsdMapData calcRootOrParentSegmentCoordinate(struct TreeNode *rootOrParentNode);

    /**
     * @brief Calculate the segment of HV kids end coordinate
     * @param childNode 
     * @return struct PsdMapData 
     */
    struct PsdMapData calcChildSegmentCoordinate(struct TreeNode *childNode);

    /**
     * @brief The function is to calculate the offset corresponding to the angle of rotation of the arc from the beginning position to the end position of this segment
     * @param arcR (radius of the arc)
     * @param arcRotationAngle (the angle of rotation of the arc)
     * @param signCurvature (the positive and negative effects of curvature determine the positive and negative effects of dy)
     * @return tOffset (dx and dy with rotating angle)
     */
    tOffset calcCurveXYOffset(double arcR, double arcRotationAngle, bool signCurvature);

    #if 0
    /**
     * @brief Calculate X Y offsset in curve case
     * @param S (actual arc length, the length of a curve segment)
     * @param A0 (clothoide parameter, starting value for each sampling point)
     * @param A1 (clothoide parameter, sample the value of the next sampling point)
     * @param accumulateBranchAngle (branching angle relative to the first position)
     * @return tOffset (vertical offset x and horizontal offset y after rotating BranchAngle)
     */
    tOffset calcCurveXYOffset(double S, double A0, double A1, double accumulateBranchAngle);
    #endif

    /**
     * @brief Calculate X Y offsset in straight path case
     * @param Length (actual length)
     * @param accumulateBranchAngle (accumulate branch angle relative to the first position)
     * @return tOffset (vertical offset x and horizontal offset y after rotating accumulateBranchAngle)
     */
    tOffset calcStraightXYOffset(double Length, double accumulateBranchAngle);

    /**
     * @brief The function is to calculate the rotation of the coordinate system relative to true north direction, the XY input is the offset from the start position of the segment to the end position
     * @param accumulateBranchAngle (the BranchAngle at which the start position of the every segment is accumulated relative to true north)
     * @param distanceX (x-axis before rotation)
     * @param distanceY (y-axis before rotation)
     * @return tOffset (vertical offset x and horizontal offset y after rotation)
     */
    tOffset coordinateSystemRotates(double accumulateBranchAngle, double distanceX, double distanceY);

    /**
     * @brief Calculate horizontal and orthogonal distance
     * @param Heading (from HV)
     * @param distanceX (x-axis before rotation)
     * @param distanceY (y-axis before rotation)
     * @return tOffset (vertical offset x and horizontal offset y after rotation)
     */
    tOffset calcHeadingXY(double Heading, double distanceX, double distanceY);

    /**
     * @brief Get the Tree object
     * @return struct TreeNode* 
     */
    struct TreeNode *getTree();

    /**
     * @brief Set the Tree object
     * @param Node (set the Node to mTree)
     */
    void setTree(struct TreeNode *Node);
    
    /**
     * @brief Get the Map Mutex Status object
     * @return true (mapThreadMutex is locked)
     * @return false (mapThreadMutex is unlocked)
     */
    bool getMapMutexStatus();

    /**
     * @brief Set the Map Mutex Status object (for gtest branch coverage)
     * @param MutexStatus 
     */
    void setMapMutexStatus(bool MutexStatus);

    /**
     * @brief Set the input accumulateBranchAngle value range to: [-2π, 0]∪(0, +2π]
     * @param accumulateBranchAngle 
     */
    void fixedAccumulateBranchAngle(double &accumulateBranchAngle);

    /**
     * @brief Just the function of printing every segment's coordinate
     * @param Node 
     */
    void displayNodeCoordinate(struct TreeNode *Node);

    /**
     * @brief clear all coordinates in tree
     * @param Node 
     */
    void clearCoordinates(struct TreeNode *Node);

    //private:
    static PsdMap* pInstance;   /**<A pointer used to return the object of  the class of PsdMap*/
    
    /**
     * @brief Construct a new PsdMap object
     */
    PsdMap(/* args */);

    /**
     * @brief Destroy the PsdMap object
     */
    ~PsdMap();
};

void *PsdMapRun(void *arg);

#endif /*_PSDMAP_H_*/

