/*********************************************************************************
 * Copyright(C),Shanghai Nesinext Software Co., Ltd.
 * FileName:	 Haversine.cpp
 * Author: 	     ZhaoZijia
 * Version :	 Ver0.1
 * Date:		 2023-10-13
 * Description: Haversine algorithm about calculating latitude and longitude.
 *
 *********************************************************************************/
/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
#include "../inc/Haversine.h"
#include <cstdio>
#include <cmath>
/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/
#define PI acos(-1)
#define EARTH_RADIUS 6378.137
/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: static statement
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * LOCAL AND GLOBAL VARIABLES
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * FUNCTION DEFINITIONS: static definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
Haversine::Haversine(/* args */)
{
}

Haversine::~Haversine()
{
}

double Haversine::toRadians(double Degrees)
{
    return Degrees * PI / 180.0;
}

double Haversine::toDegrees(double Radians)
{
    return Radians * 180.0 / PI;
}

tCoordinates Haversine::calcDestination(tCoordinates startCoordinate, double distanceX, double distanceY)
{
    //init destinationCoord
    tCoordinates destinationCoord = {0.0, 0.0};

    //convert start Coordinate to radians
    double startLatRad = toRadians(startCoordinate.latitude);
    double startLonRad = toRadians(startCoordinate.longitude);

    double deltaX = distanceX / 1000.0;
    double deltaY = distanceY / 1000.0;

    //calculate destination latitude with radians
    double deltaLatRad = deltaY / EARTH_RADIUS;
    double destLatRad = startLatRad + deltaLatRad;

    //calculate destination longitude with radians
    double deltaLonRad = deltaX / (EARTH_RADIUS * cos(startLatRad));
    double destLonRad = startLonRad + deltaLonRad;

    //convert destination Coordinate to radians and save
    destinationCoord.latitude = toDegrees(destLatRad);
    destinationCoord.longitude = toDegrees(destLonRad);

    printf("[%s] [%d]: destinationCoord latitude = %f  destinationCoord longitude = %f\n", __FUNCTION__, __LINE__, destinationCoord.latitude, destinationCoord.longitude);
    return destinationCoord;
}

double Haversine::haversineAirDistance(double lat1, double lon1, double lat2, double lon2)
{
    double airDistance = 0.0;

    double lat1Rad = toRadians(lat1);
    double lat2Rad = toRadians(lat2);
    double deltaLatRad = lat2Rad - lat1Rad;

    double lon1Rad = toRadians(lon1);
    double lon2Rad = toRadians(lon2);
    double deltaLonRad = lon2Rad - lon1Rad;

    double A = sin(deltaLatRad / 2) * sin(deltaLatRad / 2) + cos(lat1Rad) * cos(lat2Rad) * sin(deltaLonRad / 2) * sin(deltaLonRad / 2);
    double C = 2 * atan2(sqrt(A), sqrt(1 - A));
    airDistance = EARTH_RADIUS * 1000 * C;

    return airDistance;
}
