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
#include "MeasurementPoint.h"

/* Imports Library */
#include <string>
#include <iostream>

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

MeasurementPoint::MeasurementPoint(int XDesiredInit, int YDesiredInit, int Teamside):
    XDesired(XDesiredInit),
    YDesired(YDesiredInit),
    Teamside(Teamside)
{

}

