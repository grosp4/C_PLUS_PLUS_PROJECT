/** \file       MsgQueue.cpp
 *  \brief
 *
 *******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 *  \authors    bartj2
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
#include "MsgQueue.hpp"


/*******************************************************************************
 *  Constructor :
 ******************************************************************************/
/** \brief      Constructor of the Class
 *
 *  \author     bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
MsgQueue::MsgQueue()
{

}

/*******************************************************************************
 *  Destructor :
 ******************************************************************************/
/** \brief        Destructor of the Class
 *
 *  \author      bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
MsgQueue::~MsgQueue()
{


}

/*******************************************************************************
 *  Method : send()
 ******************************************************************************/
/** \brief      Saves the X and Y params into the MsgQueue
 *
 *  \author     bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
void MsgQueue::send(int X, int Y)
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
 *  \return       None
 *
 ******************************************************************************/
void MsgQueue::receive(int *X, int *Y)
{
    this->MsgQueueMutex.lock();

    *X = this->XRealValue;
    *Y = this->YRealValue;

    this->MsgQueueMutex.unlock();
}