/** \file       testthread.hpp
 *  \brief
 *******************************************************************************
 *
 *  \class
 *
 *  \brief
 *
 *  \authors    bartj2
 *
 *  \date       21.04.2015
 *
 *  \remark     Last Modification
 *               \li bartj2, 21.04.2015 created
 *
 ******************************************************************************/
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef TESTTHREAD_HPP
#define TESTTHREAD_HPP

/* Imports Library */
#include <QThread>
#include <QMutex>

/* Class Constant Declaration--------------------------------------------------*/
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/

class testthread : public QThread
{
    public:
    testthread(  );
    //virtual ~testthread();? noetig??

    private:
    void run();

    public:
    void print();

    public:
    volatile bool ThreadStopped;


    private:
    int TestCounter;
    QMutex *CounterMutex;

};


#endif // TESTTHREAD_HPP

