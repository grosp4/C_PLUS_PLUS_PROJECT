/** \file       Template.hpp
 *  \brief
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
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef TEXTFILE_H
#define TEXTFILE_H

/* Imports Library */
#include <string>
#include <QFile>
#include "MeasurementPoint.h"
#include <QObject>

/* Class Constant Declaration--------------------------------------------------*/

/* Define Coordinate System for Left Team */

/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
class TextFile : public QObject
{
    Q_OBJECT
public:
    TextFile();
    ~TextFile();
    void write(MeasurementPoint *NextPoint);

    QFile *FileLeft;
    QFile *FileRight;
};

#endif // TEXTFILE_H
