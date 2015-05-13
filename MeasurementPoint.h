/** \file       MeasurementPoint.hpp
 *  \brief
 *******************************************************************************
 *
 *  \class      MeasurementPoint
 *
 *  \brief
 *
 *  \authors    grosp4
 *
 *  \date
 *
 *  \remark     Last Modification
 *               \li
 *
 ******************************************************************************/
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef MEASUREMENTPOINT_H
#define MEASUREMENTPOINT_H
/* Imports Header Files*/
/* Imports Library */
#include <QObject>

/* Class Constant Declaration--------------------------------------------------*/
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
class MeasurementPoint : public QObject
{
    Q_OBJECT
public:
    MeasurementPoint(int XDesiredinit, int YDesiredInit, int Teamside);

public:
    int XDesired = 0;
    int YDesired = 0;

    int XRealTop = 0;
    int YRealTop = 0;

    int XRealBottom = 0;
    int YRealBottom = 0;

    int Teamside = 0;

public:
    void getValues();

};

#endif // MEASUREMENTPOINT_H
