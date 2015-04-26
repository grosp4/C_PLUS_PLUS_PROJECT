/** \file       TextFile.cpp
 *  \brief
 *
 *******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 *  \authors
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
#include "MeasurementPoint.h"
#include "TextFile.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include "UltrasonicTagClass.hpp"
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
TextFile::TextFile()
{

    QString FileNameLeft = "Messung_Tisch_links.txt";
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

    QString FileNameRight = "Messung_Tisch_rechts.txt";
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


TextFile::~TextFile()
{

}

/*******************************************************************************
 *  Method : write
 ******************************************************************************/
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
void TextFile::write( MeasurementPoint &NextPoint )
{
    if( NextPoint.TeamSite == TeamLeft )
    {
        // write to Left File (UPS-Calculation should be informed too!!!
        if( FileLeft->open( QIODevice::Append ) == true )
        {
            QTextStream stream( FileLeft );
            stream << NextPoint.XDesired <<";" << NextPoint.YDesired << ";" << "\r\n";
            FileLeft->close();
        }
    }
    else
    {
        // write to Right File
        if( FileRight->open( QIODevice::Append ) == true )
        {
            QTextStream stream( FileRight );
            stream << "NextStream" << endl;
            FileRight->close();
        }
    }
}
