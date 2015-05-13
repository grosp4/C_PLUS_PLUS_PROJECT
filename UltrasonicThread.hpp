/** \file       UltrasonicThread.hpp
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
#ifndef ULTRASONICTHREAD_HPP
#define ULTRASONICTHREAD_HPP

/* Imports Library */
#include <string>
#include <QThread>
#include <QString>
#include "HexamiteRS232PortClass.h"
#include "MsgQueue.hpp"

/* Class Constant Declaration--------------------------------------------------*/
/* Define Coordinate System for Left Team */
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/

class UltrasonicThread : public QThread
{
    Q_OBJECT

public:
    UltrasonicThread( MsgQueue *QueueRealValuesTop, MsgQueue *QueueRealValuesBottom );
    ~UltrasonicThread();

public:
    virtual void run();

signals:
    void printSerialMsg(QString NewSerialMsg);
    void printRealValueTop(int X, int Y );
    void printRealValueBottom( int X, int Y);

public:
    MsgQueue *MyQueueRealValuesTop;
    MsgQueue *MyQueueRealValuesBottom;
    HexamiteRS232Port *MySerialPort;
    UltrasonicThread *MyUltrasonicThread;

};

#endif // ULTRASONICTHREAD_HPP
