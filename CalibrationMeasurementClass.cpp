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
    /* MeasurePoints for a Calibration */

    /* MeasurePoints for a Measure */
 #ifdef  MEASUREMENT_POINTS
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

  #elif defined (MEASUREMENT_RASTER)
     /* TeamLeft */
     MeasurementPoints[0] = new MeasurementPointClass(250,250, TeamLeft);
     MeasurementPoints[1] = new MeasurementPointClass(500,250, TeamLeft);
     MeasurementPoints[2] = new MeasurementPointClass(750,250, TeamLeft);
     MeasurementPoints[3] = new MeasurementPointClass(1000,250, TeamLeft);
     MeasurementPoints[4] = new MeasurementPointClass(1250,250, TeamLeft);
     MeasurementPoints[5] = new MeasurementPointClass(1500,250, TeamLeft);
     MeasurementPoints[6] = new MeasurementPointClass(1750,250, TeamLeft);
     MeasurementPoints[7] = new MeasurementPointClass(2000,250, TeamLeft);
     MeasurementPoints[8] = new MeasurementPointClass(2250,250, TeamLeft);
     MeasurementPoints[9] = new MeasurementPointClass(2500,250, TeamLeft);
     MeasurementPoints[10] = new MeasurementPointClass(2750,250, TeamLeft);

     MeasurementPoints[11] = new MeasurementPointClass(250,500, TeamLeft);
     MeasurementPoints[12] = new MeasurementPointClass(500,500, TeamLeft);
     MeasurementPoints[13] = new MeasurementPointClass(750,500, TeamLeft);
     MeasurementPoints[14] = new MeasurementPointClass(1000,500, TeamLeft);
     MeasurementPoints[15] = new MeasurementPointClass(1250,500, TeamLeft);
     MeasurementPoints[16] = new MeasurementPointClass(1500,500, TeamLeft);
     MeasurementPoints[17] = new MeasurementPointClass(1750,500, TeamLeft);
     MeasurementPoints[18] = new MeasurementPointClass(2000,500, TeamLeft);
     MeasurementPoints[19] = new MeasurementPointClass(2250,500, TeamLeft);
     MeasurementPoints[20] = new MeasurementPointClass(2500,500, TeamLeft);
     MeasurementPoints[21] = new MeasurementPointClass(2750,500, TeamLeft);

     MeasurementPoints[22] = new MeasurementPointClass(250,750, TeamLeft);
     MeasurementPoints[23] = new MeasurementPointClass(500,750, TeamLeft);
     MeasurementPoints[24] = new MeasurementPointClass(750,750, TeamLeft);
     MeasurementPoints[25] = new MeasurementPointClass(1000,750, TeamLeft);
     MeasurementPoints[26] = new MeasurementPointClass(1250,750, TeamLeft);
     MeasurementPoints[27] = new MeasurementPointClass(1500,750, TeamLeft);
     MeasurementPoints[28] = new MeasurementPointClass(1750,750, TeamLeft);
     MeasurementPoints[29] = new MeasurementPointClass(2000,750, TeamLeft);
     MeasurementPoints[30] = new MeasurementPointClass(2250,750, TeamLeft);
     MeasurementPoints[31] = new MeasurementPointClass(2500,750, TeamLeft);
     MeasurementPoints[32] = new MeasurementPointClass(2750,750, TeamLeft);

     MeasurementPoints[33] = new MeasurementPointClass(250,1000, TeamLeft);
     MeasurementPoints[34] = new MeasurementPointClass(500,1000, TeamLeft);
     MeasurementPoints[35] = new MeasurementPointClass(750,1000, TeamLeft);
     MeasurementPoints[36] = new MeasurementPointClass(1000,1000, TeamLeft);
     MeasurementPoints[37] = new MeasurementPointClass(1250,1000, TeamLeft);
     MeasurementPoints[38] = new MeasurementPointClass(1500,1000, TeamLeft);
     MeasurementPoints[39] = new MeasurementPointClass(1750,1000, TeamLeft);
     MeasurementPoints[40] = new MeasurementPointClass(2000,1000, TeamLeft);
     MeasurementPoints[41] = new MeasurementPointClass(2250,1000, TeamLeft);
     MeasurementPoints[42] = new MeasurementPointClass(2500,1000, TeamLeft);
     MeasurementPoints[43] = new MeasurementPointClass(2750,1000, TeamLeft);

     MeasurementPoints[44] = new MeasurementPointClass(250,1250, TeamLeft);
     MeasurementPoints[45] = new MeasurementPointClass(500,1250, TeamLeft);
     MeasurementPoints[46] = new MeasurementPointClass(750,1250, TeamLeft);
     MeasurementPoints[47] = new MeasurementPointClass(1000,1250, TeamLeft);
     MeasurementPoints[48] = new MeasurementPointClass(1250,1250, TeamLeft);
     MeasurementPoints[49] = new MeasurementPointClass(1500,1250, TeamLeft);
     MeasurementPoints[50] = new MeasurementPointClass(1750,1250, TeamLeft);
     MeasurementPoints[51] = new MeasurementPointClass(2000,1250, TeamLeft);
     MeasurementPoints[52] = new MeasurementPointClass(2250,1250, TeamLeft);
     MeasurementPoints[53] = new MeasurementPointClass(2500,1250, TeamLeft);
     MeasurementPoints[54] = new MeasurementPointClass(2750,1250, TeamLeft);

     MeasurementPoints[55] = new MeasurementPointClass(250,1500, TeamLeft);
     MeasurementPoints[56] = new MeasurementPointClass(500,1500, TeamLeft);
     MeasurementPoints[57] = new MeasurementPointClass(750,1500, TeamLeft);
     MeasurementPoints[58] = new MeasurementPointClass(1000,1500, TeamLeft);
     MeasurementPoints[59] = new MeasurementPointClass(1250,1500, TeamLeft);
     MeasurementPoints[60] = new MeasurementPointClass(1500,1500, TeamLeft);
     MeasurementPoints[61] = new MeasurementPointClass(1750,1500, TeamLeft);
     MeasurementPoints[62] = new MeasurementPointClass(2000,1500, TeamLeft);
     MeasurementPoints[63] = new MeasurementPointClass(2250,1500, TeamLeft);
     MeasurementPoints[64] = new MeasurementPointClass(2500,1500, TeamLeft);
     MeasurementPoints[65] = new MeasurementPointClass(2750,1500, TeamLeft);

     MeasurementPoints[66] = new MeasurementPointClass(250,1750, TeamLeft);
     MeasurementPoints[67] = new MeasurementPointClass(500,1750, TeamLeft);
     MeasurementPoints[68] = new MeasurementPointClass(750,1750, TeamLeft);
     MeasurementPoints[69] = new MeasurementPointClass(1000,1750, TeamLeft);
     MeasurementPoints[70] = new MeasurementPointClass(1250,1750, TeamLeft);
     MeasurementPoints[71] = new MeasurementPointClass(1500,1750, TeamLeft);
     MeasurementPoints[72] = new MeasurementPointClass(1750,1750, TeamLeft);
     MeasurementPoints[73] = new MeasurementPointClass(2000,1750, TeamLeft);
     MeasurementPoints[74] = new MeasurementPointClass(2250,1750, TeamLeft);
     MeasurementPoints[75] = new MeasurementPointClass(2500,1750, TeamLeft);
     MeasurementPoints[76] = new MeasurementPointClass(2750,1750, TeamLeft);



     /* TeamRight */
     MeasurementPoints[77] = new MeasurementPointClass(250,250, TeamRight);
     MeasurementPoints[78] = new MeasurementPointClass(500,250, TeamRight);
     MeasurementPoints[79] = new MeasurementPointClass(750,250, TeamRight);
     MeasurementPoints[80] = new MeasurementPointClass(1000,250, TeamRight);
     MeasurementPoints[81] = new MeasurementPointClass(1250,250, TeamRight);
     MeasurementPoints[82] = new MeasurementPointClass(1500,250, TeamRight);
     MeasurementPoints[83] = new MeasurementPointClass(1750,250, TeamRight);
     MeasurementPoints[84] = new MeasurementPointClass(2000,250, TeamRight);
     MeasurementPoints[85] = new MeasurementPointClass(2250,250, TeamRight);
     MeasurementPoints[86] = new MeasurementPointClass(2500,250, TeamRight);
     MeasurementPoints[87] = new MeasurementPointClass(2750,250, TeamRight);

     MeasurementPoints[88] = new MeasurementPointClass(250,500, TeamRight);
     MeasurementPoints[89] = new MeasurementPointClass(500,500, TeamRight);
     MeasurementPoints[90] = new MeasurementPointClass(750,500, TeamRight);
     MeasurementPoints[91] = new MeasurementPointClass(1000,500, TeamRight);
     MeasurementPoints[92] = new MeasurementPointClass(1250,500, TeamRight);
     MeasurementPoints[93] = new MeasurementPointClass(1500,500, TeamRight);
     MeasurementPoints[94] = new MeasurementPointClass(1750,500, TeamRight);
     MeasurementPoints[95] = new MeasurementPointClass(2000,500, TeamRight);
     MeasurementPoints[96] = new MeasurementPointClass(2250,500, TeamRight);
     MeasurementPoints[97] = new MeasurementPointClass(2500,500, TeamRight);
     MeasurementPoints[98] = new MeasurementPointClass(2750,500, TeamRight);

     MeasurementPoints[99] = new MeasurementPointClass(250,750, TeamRight);
     MeasurementPoints[100] = new MeasurementPointClass(500,750, TeamRight);
     MeasurementPoints[101] = new MeasurementPointClass(750,750, TeamRight);
     MeasurementPoints[102] = new MeasurementPointClass(1000,750, TeamRight);
     MeasurementPoints[103] = new MeasurementPointClass(1250,750, TeamRight);
     MeasurementPoints[104] = new MeasurementPointClass(1500,750, TeamRight);
     MeasurementPoints[105] = new MeasurementPointClass(1750,750, TeamRight);
     MeasurementPoints[106] = new MeasurementPointClass(2000,750, TeamRight);
     MeasurementPoints[107] = new MeasurementPointClass(2250,750, TeamRight);
     MeasurementPoints[108] = new MeasurementPointClass(2500,750, TeamRight);
     MeasurementPoints[109] = new MeasurementPointClass(2750,750, TeamRight);

     MeasurementPoints[110] = new MeasurementPointClass(250,1000, TeamRight);
     MeasurementPoints[111] = new MeasurementPointClass(500,1000, TeamRight);
     MeasurementPoints[112] = new MeasurementPointClass(750,1000, TeamRight);
     MeasurementPoints[113] = new MeasurementPointClass(1000,1000, TeamRight);
     MeasurementPoints[114] = new MeasurementPointClass(1250,1000, TeamRight);
     MeasurementPoints[115] = new MeasurementPointClass(1500,1000, TeamRight);
     MeasurementPoints[116] = new MeasurementPointClass(1750,1000, TeamRight);
     MeasurementPoints[117] = new MeasurementPointClass(2000,1000, TeamRight);
     MeasurementPoints[118] = new MeasurementPointClass(2250,1000, TeamRight);
     MeasurementPoints[119] = new MeasurementPointClass(2500,1000, TeamRight);
     MeasurementPoints[120] = new MeasurementPointClass(2750,1000, TeamRight);

     MeasurementPoints[121] = new MeasurementPointClass(250,1250, TeamRight);
     MeasurementPoints[122] = new MeasurementPointClass(500,1250, TeamRight);
     MeasurementPoints[123] = new MeasurementPointClass(750,1250, TeamRight);
     MeasurementPoints[124] = new MeasurementPointClass(1000,1250, TeamRight);
     MeasurementPoints[125] = new MeasurementPointClass(1250,1250, TeamRight);
     MeasurementPoints[126] = new MeasurementPointClass(1500,1250, TeamRight);
     MeasurementPoints[127] = new MeasurementPointClass(1750,1250, TeamRight);
     MeasurementPoints[128] = new MeasurementPointClass(2000,1250, TeamRight);
     MeasurementPoints[129] = new MeasurementPointClass(2250,1250, TeamRight);
     MeasurementPoints[130] = new MeasurementPointClass(2500,1250, TeamRight);
     MeasurementPoints[131] = new MeasurementPointClass(2750,1250, TeamRight);

     MeasurementPoints[132] = new MeasurementPointClass(250,1500, TeamRight);
     MeasurementPoints[133] = new MeasurementPointClass(500,1500, TeamRight);
     MeasurementPoints[134] = new MeasurementPointClass(750,1500, TeamRight);
     MeasurementPoints[135] = new MeasurementPointClass(1000,1500, TeamRight);
     MeasurementPoints[136] = new MeasurementPointClass(1250,1500, TeamRight);
     MeasurementPoints[137] = new MeasurementPointClass(1500,1500, TeamRight);
     MeasurementPoints[138] = new MeasurementPointClass(1750,1500, TeamRight);
     MeasurementPoints[139] = new MeasurementPointClass(2000,1500, TeamRight);
     MeasurementPoints[140] = new MeasurementPointClass(2250,1500, TeamRight);
     MeasurementPoints[141] = new MeasurementPointClass(2500,1500, TeamRight);
     MeasurementPoints[142] = new MeasurementPointClass(2750,1500, TeamRight);

     MeasurementPoints[143] = new MeasurementPointClass(250,1750, TeamRight);
     MeasurementPoints[144] = new MeasurementPointClass(500,1750, TeamRight);
     MeasurementPoints[145] = new MeasurementPointClass(750,1750, TeamRight);
     MeasurementPoints[146] = new MeasurementPointClass(1000,1750, TeamRight);
     MeasurementPoints[147] = new MeasurementPointClass(1250,1750, TeamRight);
     MeasurementPoints[148] = new MeasurementPointClass(1500,1750, TeamRight);
     MeasurementPoints[149] = new MeasurementPointClass(1750,1750, TeamRight);
     MeasurementPoints[150] = new MeasurementPointClass(2000,1750, TeamRight);
     MeasurementPoints[151] = new MeasurementPointClass(2250,1750, TeamRight);
     MeasurementPoints[152] = new MeasurementPointClass(2500,1750, TeamRight);
     MeasurementPoints[153] = new MeasurementPointClass(2750,1750, TeamRight);

 /* MeasurePoints for a Calibration */
#elif defined   (CALIBRATION)
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
