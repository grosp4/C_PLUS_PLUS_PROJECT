/** \file       MsgQueueClass.hpp
 *  \brief      This Class include all Functions for the communication between
 *              different Tasks.
 *
 *******************************************************************************
 *
 *  \class      MsgQueueClass
 *
 *  \brief      This Class include all Functions for the communication between
 *              different Tasks.
 *
 *  \authors    bartj2
 *
 *  \date       14.04.2015
 *
 *  \remark     Last Modification
 *               \li grosp4, bartj2, 14.04.2015, Created
 *
 ******************************************************************************/
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef MSGQUEUE_HPP
#define MSGQUEUE_HPP
/* Imports Header Files*/
/* Imports Library */
#include <string>
#include <QMutex>
#include <QObject>

/* Class Constant Declaration--------------------------------------------------*/
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/


class MsgQueueClass : public QObject
{
    Q_OBJECT

public:
    MsgQueueClass();

private:
    QMutex MsgQueueMutex;
    int XRealValue;
    int YRealValue;

public:
    void send(int X, int Y);
    void receive(int *X, int *Y);

};

#endif // MSGQUEUE_HPP
