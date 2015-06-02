/** \file       CalibrationMeasurementClass.cpp
 *  \brief      This Class contain all Data of the measured Points
 *******************************************************************************
 *
 *  \class      CalibrationMeasurementClass
 *
 *  \brief      This Class contain all Data of the measured Points
 *
 *  \authors    bartj2
 *
 *  \date       24.04.2015
 *
 *  \remark     Last Modification
 *               \li bartj2, 24.04.2015, Created
 *
 ******************************************************************************/
/* Imports Header Files*/
#include "mainwindow.h"
#include "UltrasonicTagClass.hpp"
#include "CalibrationMeasurementClass.h"

/* Imports Library */
#include <string>
#include <iostream>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*******************************************************************************
 *  Constructor : CalibrationMeasurementClass()
 ******************************************************************************/
/** \brief        Constructor of the Class Calibration Measurement
 *
 *  \author       bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
CalibrationMeasurementClass::CalibrationMeasurementClass()
{

   /* MeasurePoints for a Measure */
#ifdef  MEASUREMENT
    /* TeamLeft */
    MeasurementPoints[0] = new MeasurementPointClass(350,350, TeamLeft);
    MeasurementPoints[1] = new MeasurementPointClass(350,1650, TeamLeft);
    MeasurementPoints[2] = new MeasurementPointClass(1000, 1000, TeamLeft);
    MeasurementPoints[3] = new MeasurementPointClass(2000, 1000, TeamLeft);
    MeasurementPoints[4] = new MeasurementPointClass(2650, 350, TeamLeft);
    MeasurementPoints[5] = new MeasurementPointClass(2650, 1650, TeamLeft);

    /* TeamRight */
    MeasurementPoints[6] = new MeasurementPointClass(350,350, TeamRight);
    MeasurementPoints[7] = new MeasurementPointClass(350,1650, TeamRight);
    MeasurementPoints[8] = new MeasurementPointClass(1000, 1000, TeamRight);
    MeasurementPoints[9] = new MeasurementPointClass(2000, 1000, TeamRight);
    MeasurementPoints[10] = new MeasurementPointClass(2650, 350, TeamRight);
    MeasurementPoints[11] = new MeasurementPointClass(2650, 1650, TeamRight);
#endif
 /* MeasurePoints for a Calibration */
#ifdef  CALIBRATION
    /* TeamLeft */
    MeasurementPoints[0] = new MeasurementPointClass(250,1750, TeamLeft);
    MeasurementPoints[1] = new MeasurementPointClass(870,1355, TeamLeft);
    MeasurementPoints[2] = new MeasurementPointClass(910, 830, TeamLeft);
    MeasurementPoints[3] = new MeasurementPointClass(850, 200, TeamLeft);
    MeasurementPoints[4] = new MeasurementPointClass(1500, 1650, TeamLeft);
    MeasurementPoints[5] = new MeasurementPointClass(2130, 1355, TeamLeft);
    MeasurementPoints[6] = new MeasurementPointClass(2090, 830, TeamLeft);
    MeasurementPoints[7] = new MeasurementPointClass(2150,200, TeamLeft);
    MeasurementPoints[8] = new MeasurementPointClass(2750, 1750, TeamLeft);

    /* TeamRight */
    MeasurementPoints[9] = new MeasurementPointClass(250,1750, TeamRight);
    MeasurementPoints[10] = new MeasurementPointClass(870,1355, TeamRight);
    MeasurementPoints[11] = new MeasurementPointClass(910, 830, TeamRight);
    MeasurementPoints[12] = new MeasurementPointClass(850, 200, TeamRight);
    MeasurementPoints[13] = new MeasurementPointClass(1500, 1650, TeamRight);
    MeasurementPoints[14] = new MeasurementPointClass(2130, 1355,TeamRight);
    MeasurementPoints[15] = new MeasurementPointClass(2090, 830, TeamRight);
    MeasurementPoints[16] = new MeasurementPointClass(2150,200, TeamRight);
    MeasurementPoints[17] = new MeasurementPointClass(2750, 1750, TeamRight);
#endif


}

/*******************************************************************************
 *  Destructor :  ~CalibrationMeasurementClass()
 ******************************************************************************/
/** \brief        Destructor of the Class Calibration Measurement
 *
 *  \author       bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
CalibrationMeasurementClass::~CalibrationMeasurementClass()
{
    for( int iCounter = 0; iCounter < MAX_MEASUREMENT_POINTS; iCounter++ )
    {
        delete MeasurementPoints[iCounter];
    }
}

/*******************************************************************************
 *  Method :    generateOutputFile
 ******************************************************************************/
/** \brief      generates/creates a .txt file to save all measured values and
 *              points for further matlab processing.
 *
 *  \author     bartj2
 *
 *  \return     None
 *
 ******************************************************************************/
void CalibrationMeasurementClass::generateOutputFile()
{
    CalibrationOutputFile = new TextFileClass;

    for( int iCounter = 0; iCounter < MAX_MEASUREMENT_POINTS; iCounter++ )
    {
        CalibrationOutputFile->write( MeasurementPoints[iCounter] );
    }
}
