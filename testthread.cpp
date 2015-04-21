/******************************************************************************/
/** \file       testthread.cpp
 *  \brief
 *******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 *  \authors
 *
 *  \date       21.04.2015
 *
 *  \remark     Last Modification
 *               \li
 *
 ******************************************************************************/

/* Imports Header Files*/
#include "testthread.hpp"

/* Imports Library */
#include <string>
#include <iostream>
#include <QMutex>

/*******************************************************************************
 *  Constructor :    testthread()
 ******************************************************************************/
/** \brief        Constructor of the Class testthread
 *
 *  \author		  bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
testthread::testthread( void )
{
    ThreadStopped = false;
    CounterMutex = new QMutex(QMutex::Recursive);
    TestCounter = 0;
}

/*******************************************************************************
 *  Method :      run()
 ******************************************************************************/
/** \brief        Task run-method. Main code of task
 *
 *  \author		  bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
void testthread::run()
{

    while( true )//this->ThreadStopped == false )
    {
        this->CounterMutex->lock();
        // say hello periodic:
        std::cout << "Hello, I am the test thread. Counter = "
                  << TestCounter << std::endl;
        TestCounter++;
        this->CounterMutex->unlock();

        this->sleep( 1 );
    }
}




/*******************************************************************************
 *  Method :      print()
 ******************************************************************************/
/** \brief        tests the Thread communication by printing the counter and
 *                increment it by 10.
 *                can be called from another Task.
 *
 *  \author		  bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
void testthread::print()
{
    //CounterMutex->lock();
    // say hello :
    std::cout << "\nHello, another thread called me. Counter = " << std::endl;// << TestCounter << std::endl;
    //TestCounter +=10;
//    CounterMutex->unlock();
}
