/** \file       CalibrationMeasurement.cpp
 *  \brief
 *
 *******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 *  \authors    bartj2
 *
 *  \date
 *
 *  \remark     Last Modification
 *               \li
 *
 ******************************************************************************/

/* Imports Header Files*/

/* Imports Library */
#include <string>
#include <iostream>






#include "CalibrationMeasurement.h"

/*******************************************************************************
 *  Constructor :
 ******************************************************************************/
/** \brief        Constructor of the Class
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
CalibrationMeasurement::CalibrationMeasurement()
{
    MeasurementPoints[0].XDesired = 100;
    MeasurementPoints[0].YDesired = 100;

}

/*******************************************************************************
 *  Destructor :
 ******************************************************************************/
/** \brief        Destructor of the Class
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
CalibrationMeasurement::~CalibrationMeasurement()
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
