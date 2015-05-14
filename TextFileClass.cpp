/** \file       TextFileClass.cpp
 *  \brief      Includes all Data and Methods to save the meassured Data in
 *              a *.txt-File
 *
 *******************************************************************************
 *
 *  \class      TextFileClass
 *
 *  \brief      Includes all Data and Methods to save the meassured Data in
 *              a *.txt-File
 *
 *  \authors    bartj2
 *
 *  \date       13.04.2015
 *
 *  \remark     Last Modification
 *               \li bartj2, 30.04.2015, Created
 *
 ******************************************************************************/
/* Imports Header Files*/
#include "MeasurementPointClass.h"
#include "TextFileClass.h"
#include "UltrasonicTagClass.hpp"

/* Imports Library */
#include <string>
#include <iostream>
#include <QString>
#include <QFile>
#include <QTextStream>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*******************************************************************************
 *  Constructor : TextFileClass()
 ******************************************************************************/
/** \brief        Constructor of the TextFileClass
 *
 *  \author       Joel Baertschi
 *
 *  \return       None
 *
 ******************************************************************************/
TextFileClass::TextFileClass()
{

    QString FileNameLeft = "Measurement_StartPositionLeft.txt";
    FileLeft = new QFile( FileNameLeft );
    if ( FileLeft->open(QIODevice::ReadWrite) == true )
    {
        QTextStream stream( FileLeft );
        stream << "x_soll   y_soll   x_ist_R1   y_ist_R1   x_ist_R2   y_ist_R2\r\n";
        FileLeft->close();
    }
    else
    {
        std::cout << "Could not open file 'left'." << std::endl;
    }

    QString FileNameRight = "Measurement_StartPositionRight.txt";
    FileRight = new QFile( FileNameRight );
    if( FileRight->open(QIODevice::ReadWrite) == true)
    {
        QTextStream stream( FileRight );
        stream << "x_soll   y_soll   x_ist_R1   y_ist_R1   x_ist_R2   y_ist_R2\r\n";
        FileRight->close();
    }
    else
    {
        std::cout << "Could not open file 'right'." << std::endl;
    }
}

/*******************************************************************************
 *  Method : write ()
 ******************************************************************************/
/** \brief        Write the given MeasurementPoint in a *.txt-File
 *
 *  \author       Joel Baertschi
 *
 *  \param        NextPoint Pointer to the Measurment Data
 *
 *  \return       None
 *
 ******************************************************************************/
void TextFileClass::write( MeasurementPointClass *NextPoint )
{
    if( NextPoint->Teamside == TeamLeft )
    {
        // write to Left File (UPS-Calculation should be informed too!!!
        if( FileLeft->open( QIODevice::Append ) == true )
        {
            QTextStream stream( FileLeft );
            stream << NextPoint->XDesired <<";"
                   << NextPoint->YDesired << ";"
                   << NextPoint->XRealTop << ";"
                   << NextPoint->YRealTop << ";"
                   << NextPoint->XRealBottom << ";"
                   << NextPoint->YRealBottom << ";"
                   << "\r\n";
            FileLeft->close();
        }
    }
    else
    {
        // write to Right File
        if( FileRight->open( QIODevice::Append ) == true )
        {
            QTextStream stream( FileRight );
            stream << NextPoint->XDesired <<";"
                   << NextPoint->YDesired << ";"
                   << NextPoint->XRealTop << ";"
                   << NextPoint->YRealTop << ";"
                   << NextPoint->XRealBottom << ";"
                   << NextPoint->YRealBottom << ";"
                   << "\r\n";
            FileRight->close();
        }
    }
}
