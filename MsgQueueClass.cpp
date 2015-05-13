/** \file       MsgQueueClass.cpp
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

/* Imports Header Files*/
#include "MsgQueueClass.hpp"

/* Imports Library */
#include <string>
#include <iostream>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/*******************************************************************************
 *  Constructor :   MsgQueueClass()
 ******************************************************************************/
/** \brief      Constructor of the MsgQueueClass
 *
 *  \author     bartj2
 *
 *  \return     None
 *
 ******************************************************************************/
MsgQueueClass::MsgQueueClass()
{
    XRealValue = 0;
    YRealValue = 0;
}


/*******************************************************************************
 *  Method : send()
 ******************************************************************************/
/** \brief      Saves the X and Y params into the MsgQueue
 *
 *  \author     bartj2
 *
 *  \return     None
 *
 ******************************************************************************/
void MsgQueueClass::send(int X, int Y)
{
    this->MsgQueueMutex.lock();

    this->XRealValue = X;
    this->YRealValue = Y;

    this->MsgQueueMutex.unlock();
}

/*******************************************************************************
 *  Method : receive()
 ******************************************************************************/
/** \brief      Returns MsgQueue-Values.
 *
 *  \author     bartj2
 *
 *  \return     None
 *
 ******************************************************************************/
void MsgQueueClass::receive(int *X, int *Y)
{
    this->MsgQueueMutex.lock();

    *X = this->XRealValue;
    *Y = this->YRealValue;

    this->MsgQueueMutex.unlock();
}
