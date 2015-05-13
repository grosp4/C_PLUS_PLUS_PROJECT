/** \file       TextFileClass.hpp
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
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef TEXTFILE_CLASS_H
#define TEXTFILE_CLASS_H

/* Imports Header Files*/
#include "MeasurementPointClass.h"

/* Imports Library */
#include <string>
#include <QFile>
#include <QObject>

/* Class Constant Declaration--------------------------------------------------*/
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
class TextFileClass : public QObject
{
    Q_OBJECT
public:
    TextFileClass();
    void write(MeasurementPointClass *NextPoint);

    QFile *FileLeft;
    QFile *FileRight;
};

#endif /* TEXTFILE_CLASS_H */
