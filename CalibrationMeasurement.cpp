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
#include "mainwindow.h"
#include "CalibrationMeasurement.h"
#include "globaldefines.h"


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
    /* TeamLeft */
    MeasurementPoints[0] = new MeasurementPoint(0,0, TeamLeft);
    MeasurementPoints[1] = new MeasurementPoint(250,1000, TeamLeft);
    MeasurementPoints[2] = new MeasurementPoint(870, 1355, TeamLeft);
    MeasurementPoints[3] = new MeasurementPoint(90, 1750, TeamLeft);
    MeasurementPoints[4] = new MeasurementPoint(450, 300, TeamLeft);
    MeasurementPoints[5] = new MeasurementPoint(1250, 830, TeamLeft);
    MeasurementPoints[6] = new MeasurementPoint(1250, 200, TeamLeft);
    MeasurementPoints[7] = new MeasurementPoint(0,0, TeamLeft);
    MeasurementPoints[8] = new MeasurementPoint(0,0, TeamLeft);
    MeasurementPoints[9] = new MeasurementPoint(0,0, TeamLeft);
    MeasurementPoints[10] = new MeasurementPoint(0,0, TeamLeft);
    /* TeamRight */
    MeasurementPoints[11] = new MeasurementPoint(2750,1000, TeamRight);
    MeasurementPoints[12] = new MeasurementPoint(2130,1355, TeamRight);
    MeasurementPoints[13] = new MeasurementPoint(2910,1750, TeamRight);
    MeasurementPoints[14] = new MeasurementPoint(2550,300, TeamRight);
    MeasurementPoints[15] = new MeasurementPoint(1750,830, TeamRight);
    MeasurementPoints[16] = new MeasurementPoint(1750,200, TeamRight);
    MeasurementPoints[17] = new MeasurementPoint(0,0, TeamRight);
    MeasurementPoints[18] = new MeasurementPoint(0,0, TeamRight);
    MeasurementPoints[19] = new MeasurementPoint(0,0, TeamRight);
    MeasurementPoints[20] = new MeasurementPoint(0,0, TeamRight);
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
    // delete[] MeasurementPoints;
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

    for( int iCounter = 0; iCounter < MAX_MEASUREMENT_POINTS; iCounter++ )
    {
        CalibrationOutputFile->write( MeasurementPoints[iCounter] );
    }
}
