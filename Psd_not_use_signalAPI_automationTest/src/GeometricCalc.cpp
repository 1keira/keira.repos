/*********************************************************************************
 * Copyright(C),Shanghai Nesinext Software Co., Ltd.
 * FileName:	 GeometricCalc.cpp
 * Author: 	     xiechao
 * Version :	 Ver0.1
 * Date:		 2023-10-13
 * Description: geometric algorithm
 *
 *********************************************************************************/

#include "../inc/GeometricCalc.h"
#include <cstdio>
#include <cmath>


Point GeometricCalc::coordinateTransform(const Position3D_D refPos, const double heading, const Position3D_D tarPos)
{
    double R0 = 6378137.0;               //radius of the earth
    double e  = 0.0818191908425;  //eccentricity of the earth

    double RE0 = R0 / (sqrt(1 - e * e * sin(refPos.lat * M_PI / 180) * sin(refPos.lat * M_PI / 180)));

    double x0 = (RE0 + refPos.elevation) * cos(refPos.lat * M_PI / 180) * cos(refPos.Long * M_PI / 180);
    double y0 = (RE0 + refPos.elevation) * cos(refPos.lat * M_PI / 180) * sin(refPos.Long * M_PI / 180);
    double z0 = ((1 - e * e) * RE0 + refPos.elevation) * sin(refPos.lat * M_PI / 180);

    double RE = R0 / (sqrt(1 - e * e * sin(tarPos.lat * M_PI / 180) * sin(tarPos.lat * M_PI / 180)));

    double x1 = (RE + tarPos.elevation) * cos(tarPos.lat * M_PI / 180) * cos(tarPos.Long * M_PI / 180);
    double y1 = (RE + tarPos.elevation) * cos(tarPos.lat * M_PI / 180) * sin(tarPos.Long * M_PI / 180);
    double z1 = ((1 - e * e) * RE + tarPos.elevation) * sin(tarPos.lat * M_PI / 180);

    double dx = x1 - x0;
    double dy = y1 - y0;
    double dz = z1 - z0;

    double dn = -sin(tarPos.lat * M_PI / 180) * cos(tarPos.Long * M_PI / 180) * dx - sin(tarPos.lat * M_PI / 180) * sin(tarPos.Long * M_PI / 180) * dy + cos(tarPos.lat * M_PI / 180) * dz; //standard X
    double de = -sin(tarPos.Long * M_PI / 180) * dx + cos(tarPos.Long * M_PI / 180) * dy;                                                                                                                                                                                           //standard Y
    double dd = -cos(tarPos.lat * M_PI / 180) * cos(tarPos.Long * M_PI / 180) * dx - cos(tarPos.lat * M_PI / 180) * sin(tarPos.Long * M_PI / 180) * dy - sin(tarPos.lat * M_PI / 180) * dz;

    double x;  //X of target
    double y;  //Y of target
    double z;  //Z of target
    x = dn;       //rotate 90° counterclockwise: x' = x*cosθ + y*sinθ
    y = de;       //rotate 90° counterclockwise, then flip to the right for positive orientation: y' = y*cosθ - x*sinθ
    z = dd;
    // printf("[%s] [%d]: dn = %lf\n", __FUNCTION__, __LINE__, dn);
    // printf("[%s] [%d]: de = %lf\n",  __FUNCTION__, __LINE__, de);


    /*Coordinate system rotation*/
    //X-axis positive direction: The heading direction of HV
    //Positive Y-axis: Perpendicular to the X-axis, along the right side of the vehicle
    double x_;  //the X coordinate of the target after rotating the coordinate system
    double y_;  //the Y coordinate of the target after rotating the coordinate system
    y_ = x*sin(heading*M_PI/180)+y*cos(heading*M_PI/180);
    x_ = x*cos(heading*M_PI/180)-y*sin(heading*M_PI/180);
    // printf("[%s] [%d]: y_ = %lf\n", __FUNCTION__, __LINE__, y_);
    // printf("[%s] [%d]: x_ = %lf\n", __FUNCTION__, __LINE__, x_);

    Point XY_coordinate;
    XY_coordinate.x = x_;
    XY_coordinate.y = y_;

    return XY_coordinate;
}