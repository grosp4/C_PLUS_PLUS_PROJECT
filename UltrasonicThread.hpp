/******************************************************************************/
/** \file       UltrasonicThread.hpp
 *  \brief      This Task handle the whole communication with the Ultrasonic
 *              System.
 *
 *******************************************************************************
 *
 *  \class      UltrasonicThread
 *
 *  \brief      This Task handle the whole communication with the Ultrasonic
 *              System.
 *
 *  \authors    jeggy1, sches24, bartj2
 *
 *  \date       14.04.2015
 *
 *  \remark     Last Modification
 *               \li Created 14.04.2015, jeggy1, sches24, bartj2
 *
 ******************************************************************************/
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef ULTRASONICTHREAD_HPP
#define ULTRASONICTHREAD_HPP

/* Imports Header Files*/
#include <string>
#include <QThread>
#include <QString>

/* Imports Header Files*/
#include "HexamiteRS232PortClass.h"
#include "MsgQueueClass.hpp"

/* Class Constant Declaration--------------------------------------------------*/
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/

class UltrasonicThread : public QThread
{
    Q_OBJECT

public:
    UltrasonicThread( MsgQueueClass *QueueRealValues);
    ~UltrasonicThread();

public:
    virtual void run();

signals:
    void printSerialMsg(QString NewSerialMsg);
    void printRealValues(int X, int Y );

public:
    MsgQueueClass *MyQueueRealValues;
    HexamiteRS232Port *MySerialPort;

};

#endif // ULTRASONICTHREAD_HPP
