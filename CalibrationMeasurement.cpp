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
#include "UltrasonicTagClass.hpp"





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
    MeasurementPoints[0].YDesired = 200;
    // init all Points....

    for( int idx = 0; idx < 20; idx++)
    {
        if( idx < 10 )
        {
            MeasurementPoints[idx].TeamSite = TeamLeft;
        }
        else
        {
            MeasurementPoints[idx].TeamSite = TeamRight;
        }
    }

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
 *  Method :    generateOutputFile
 ******************************************************************************/
/** \brief      generates/creates a .txt file to save all measured values and
 *              points for further matlab processing.
 *
 *  \author     bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
void CalibrationMeasurement::generateOutputFile()
{
    CalibrationOutputFile = new TextFile;

    for( int iCounter = 0; iCounter < 20; iCounter++ )
    {
        CalibrationOutputFile->write( MeasurementPoints[iCounter] );
    }
}
