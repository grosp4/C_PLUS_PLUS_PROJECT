/** \file       MsgQueue.hpp
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
#ifndef MSGQUEUE_HPP
#define MSGQUEUE_HPP
/* Imports Header Files*/
/* Imports Library */
#include <string>
#include <QMutex>
#include <QObject>

/* Class Constant Declaration--------------------------------------------------*/

/* Define Coordinate System for Left Team */

/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/


class MsgQueue : public QObject
{
    Q_OBJECT

public:
    MsgQueue();
    ~MsgQueue();

private:
    QMutex MsgQueueMutex;
    int XRealValue;
    int YRealValue;

public:
    void send(int X, int Y);
    void receive(int *X, int *Y);

};

#endif // MSGQUEUE_HPP
