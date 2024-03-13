/*********************************************************************************
 * Copyright(C),Shanghai Nesinext Software Co., Ltd.
 * FileName:	 GeometricCalc.h
 * Author: 	     xiechao
 * Version :	 Ver0.1
 * Date:		 2023-10-13
 * Description: geometric algorithm
 *
 *********************************************************************************/

#ifndef _GEOETRICCALC_H_
#define _GEOETRICCALC_H_

/*-----------------------------------------------------------------------------
 * INCLUDES
 *---------------------------------------------------------------------------*/
// #include "commDataCal.h"
/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS: #define
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS: global
 *---------------------------------------------------------------------------*/
//sPosition3D
typedef struct sPosition3D {
    double lat;
    double Long;
    double elevation;
}Position3D_D;

//Point xy
typedef struct tPoint
{
    double x;
    double y;
}Point;

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES: extern
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
class GeometricCalc{
public:
    /**
     * @brief convert (latitude, longitude) to (x, y)
     * @param refPos (reference Position)
     * @param heading 
     * @param tarPos (target Postion)
     * @return Point 
     */
    static Point coordinateTransform(const Position3D_D refPos, const double heading, const Position3D_D tarPos);
};
#endif /*_GEOETRICCALC_H_*/