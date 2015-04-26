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


/* Imports Library */
#include <string>
#include <QObject>

/* Class Constant Declaration--------------------------------------------------*/


/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
class MeasurementPoint : public QObject
{
    Q_OBJECT
public:
    MeasurementPoint(int XDesiredinit, int YDesiredInit);
    MeasurementPoint();
    ~MeasurementPoint();

public:
    int XDesired;
    int YDesired;

    int XRealTop;
    int YRealTop;

    int XRealBottom;
    int YRealBottom;

    //int iPointNumber;
    int TeamSite;

public:
    void getValues();

};

#endif // MEASUREMENTPOINT_H
