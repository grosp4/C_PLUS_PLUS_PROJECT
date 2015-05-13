/******************************************************************************/
/** \file       MeasurementPointClass.cpp
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
/* Imports Header Files*/
#include "MeasurementPointClass.h"

/* Imports Library */
#include <string>
#include <iostream>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*******************************************************************************
 *  Constructor : MeasurementPointClass
 ******************************************************************************/
/** \brief        Constructor of the Class MeasurementPointClass
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/

MeasurementPointClass::MeasurementPointClass(int XDesiredInit, int YDesiredInit, int Teamside):
    XDesired(XDesiredInit),
    YDesired(YDesiredInit),
    Teamside(Teamside)
{

}

