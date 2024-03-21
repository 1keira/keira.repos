/*********************************************************************************
 * Copyright(C),Shanghai Nesinext Software Co., Ltd.
 * FileName:	 Haversine.h
 * Author: 	     zhaozijia
 * Version :	 Ver0.1
 * Date:		 2023-10-13
 * Description: Haversine algorithm about calculating latitude and longitude.
 *
 *********************************************************************************/

#ifndef _HAVERSINE_H_
#define _HAVERSINE_H_

/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include "PsdMessageDecoder.h"

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS: global
 *---------------------------------------------------------------------------*/
typedef struct Angle{
    double Alpha;
    double Beta;
}tAngle;
/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: extern
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
class Haversine{
public:
    /**
     * @brief Calculate destination coordinate
     * @param startCoordinate 
     * @param distanceX (offset of horizontal corresponding to longitude)
     * @param distanceY (offset of vertical position corresponding to latitude)
     * @return tCoordinates (destination coordinate)
     */
    static tCoordinates calcDestination(tCoordinates startCoordinate, double distanceX, double distanceY);

    /**
     * @brief Calculate Air Distance, the distance between coordinate1 and coordinate2
     * @param lat1 
     * @param lon1 
     * @param lat2 
     * @param lon2 
     * @return double (Air Distance)
     */
    static double haversineAirDistance(double lat1, double lon1, double lat2, double lon2);
    
    //private:
    /**
     * @brief Convert degrees to radians
     * @param Degrees 
     * @return double (radians)
     */
    static double toRadians(double Degrees);

    /**
     * @brief Convert radians to degrees
     * @param Radians 
     * @return double (degrees)
     */
    static double toDegrees(double Radians);

    /**
     * @brief Construct a new Haversine object
     */
    Haversine(/* args */);

    /**
     * @brief Destroy the Haversine object
     */
    ~Haversine();
};
#endif /*_HAVERSINE_H_*/