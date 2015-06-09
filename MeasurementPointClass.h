/******************************************************************************/
/** \file       MeasurementPointClass.hpp
 *  \brief      This Class save all Data from one measured Points
 *
 *******************************************************************************
 *
 *  \class      MeasurementPoint
 *
 *  \brief      This Class save all Data from one measured Points
 *
 *  \authors    grosp4, bartj2
 *
 *  \date       24.04.2015
 *
 *  \remark     Last Modification
 *               \li grosp4, bartj2, 24.04.2015, Created
 *
 ******************************************************************************/
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef MEASUREMENTPOINT_CLASS_H
#define MEASUREMENTPOINT_CLASS_H
/* Imports Header Files*/
/* Imports Library */
#include <QObject>

/* Class Constant Declaration--------------------------------------------------*/
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
class MeasurementPointClass : public QObject
{
    Q_OBJECT
public:
    MeasurementPointClass(int XDesiredinit, int YDesiredInit, int Teamside);

public:
    int XDesired = 0;
    int YDesired = 0;

    int XReal = 0;
    int YReal = 0;

    int Teamside = 0;

public:
    void getValues();

};

#endif /* MEASUREMENTPOINT_CLASS_H */
