/******************************************************************************/
/** \file       MeasurementPoint.cpp
 *  \brief
 *
 *******************************************************************************
 *
 *  \class      MeasurementPoint
 *
 *  \brief
 *
 *  \authors    grosp4, bartj2
 *
 *  \date       24.04.2015
 *
 *  \remark     Last Modification
 *               \li
 *
 ******************************************************************************/

/* Imports Header Files*/

/* Imports Library */
#include <string>
#include <iostream>
#include "MeasurementPoint.h"

/*******************************************************************************
 *  Constructor : MeasurementPoint
 ******************************************************************************/
/** \brief        Constructor of the Class
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/

MeasurementPoint::MeasurementPoint(int XDesiredInit, int YDesiredInit):
    XDesired(XDesiredInit),
    YDesired(YDesiredInit)
{

}

MeasurementPoint::MeasurementPoint()
{
    // sometimes the gui crashes if the following code is uncommented.
//    XDesired = 0;
//    YDesired = 0;
//    XRealTop = 0;
//    YRealTop = 0;
//    XRealBottom = 0;
//    YRealBottom = 0;
}
/*******************************************************************************
 *  Deconstrunctor :
 ******************************************************************************/
/** \brief        Deconstrunctor of the Class
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/

MeasurementPoint::~MeasurementPoint()
{

}

/*******************************************************************************
 *  Method :
 ******************************************************************************/
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/

