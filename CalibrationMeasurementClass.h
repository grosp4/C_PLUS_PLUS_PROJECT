/** \file       CalibrationMeasurementClass.hpp
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
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef CALIBRATIONMEASUREMENT_CLASS_H
#define CALIBRATIONMEASUREMENT_CLASS_H
/* Imports Header Files*/
#include "MeasurementPointClass.h"
#include "TextFileClass.h"

/* Imports Library */
#include <string>
#include <iostream>
#include <QObject>

/* Class Constant Declaration--------------------------------------------------*/
#define MAX_MEASUREMENT_POINTS_PER_SITE     ( 10 )
#define MAX_MEASUREMENT_POINTS              ( MAX_MEASUREMENT_POINTS_PER_SITE*2 )
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
class CalibrationMeasurementClass : public QObject
{
    Q_OBJECT

public:
    CalibrationMeasurementClass();
    ~CalibrationMeasurementClass();

public:
    MeasurementPointClass* MeasurementPoints[MAX_MEASUREMENT_POINTS] = {0};
    TextFileClass *CalibrationOutputFile;

public slots:
    void generateOutputFile();

};

#endif // CALIBRATIONMEASUREMENT_CLASS_H
