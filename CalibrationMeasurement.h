/** \file       CalibrationMeasurement.hpp
 *  \brief
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
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef CALIBRATIONMEASUREMENT_H
#define CALIBRATIONMEASUREMENT_H

/* Imports Library */
#include <string>
//#include "mainwindow.h"
#include <iostream>
#include "MeasurementPoint.h"
#include "TextFile.h"
#include <QObject>
#include "globaldefines.h"

/* Class Constant Declaration--------------------------------------------------*/

/* Define Coordinate System for Left Team */

/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/

class CalibrationMeasurement : public QObject
{
    Q_OBJECT

public:
    CalibrationMeasurement();
    ~CalibrationMeasurement();

public:
    MeasurementPoint* MeasurementPoints[MAX_MEASUREMENT_POINTS] = {0};
    TextFile *CalibrationOutputFile;


public slots:
    void generateOutputFile();

};

#endif // CALIBRATIONMEASUREMENT_H
