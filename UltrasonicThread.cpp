/******************************************************************************/
/** \file       UltrasonicThread.cpp
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

/* Imports Header Files*/
#include "UltrasonicThread.hpp"
#include "UltrasonicTagClass.hpp"
#include "HexamiteRS232PortClass.h"

/* Imports Library */
#include <string>
#include <iostream>
#include <QTime>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*******************************************************************************
 *  Constructor :
 ******************************************************************************/
/** \brief        Constructor of the Class
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
UltrasonicThread::UltrasonicThread( MsgQueueClass *QueueRealValuesTop, MsgQueueClass *QueueRealValuesBottom ):
    MyQueueRealValuesTop( QueueRealValuesTop ),
    MyQueueRealValuesBottom( QueueRealValuesBottom )
{

}


/*******************************************************************************
 *  Destructor :
 ******************************************************************************/
/** \brief        Destructor of the Class
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
UltrasonicThread::~UltrasonicThread()
{
    MySerialPort->turnHexamiteUsbSynchronizerOff();
    sleep(1);
    delete MySerialPort;
}


/*******************************************************************************
 *  Method :    run()
 ******************************************************************************/
/** \brief      The Thread main run method.
 *
 *  \author     bartj2
 *
 *  \return     None
 *
 ******************************************************************************/
void UltrasonicThread::run()
{
    /* Define Local Variable */
    std::string sSerialData1;
    std::string sSerialData2;
    std::string sSerialData3;

    /* Create Object from UltrasonicTag Class*/
    UltrasonicTagClass TagRobotBigEnemy("P20");			/*!<  ID Tag Number T20 */
    UltrasonicTagClass TagRobotSmallEnemy("P21");		/*!<  ID Tag Number T21 */

    /* Set Team start Position for the UltrasonicTag Class */
    UltrasonicTagClass::setTeamStartPosition(TeamLeft);

    /* Initialize USART-Interface with COM-Port 14 */
    MySerialPort = new HexamiteRS232Port(6);

    /*  Turn on Hexamite synchronizer  */
    MySerialPort->turnHexamiteUsbSynchronizerOn();

    //std::string *strUnfilteredData = new std::string("...");
    QTime Stopwatch;
    Stopwatch.start();

    while(1)
    {
        /* Get USART-String */
        MySerialPort->getHexamiteData(&sSerialData1, &sSerialData2, &sSerialData3);

        /* check if next printing is needed */
        if( Stopwatch.elapsed() >= 1000 ) // if 1000ms elapsed since last start of stopwatch.
        {
            // print Msg:
            emit printSerialMsg( QString("") );
            emit printSerialMsg( QString(sSerialData1.c_str()) );
            emit printSerialMsg( QString(sSerialData2.c_str()) );
            emit printSerialMsg( QString(sSerialData3.c_str()) );
            // restart Stopwatch:
            Stopwatch.restart();
        }

        /* Check for Calculation*/
        if(TagRobotBigEnemy.checkSerialMessage(sSerialData1, sSerialData2, sSerialData3))
        {
             TagRobotBigEnemy.calculatePosition();
             emit printRealValueTop(TagRobotBigEnemy.getX_Position(), TagRobotBigEnemy.getY_Position());
             this->MyQueueRealValuesTop->send(TagRobotBigEnemy.getX_Position(), TagRobotBigEnemy.getY_Position() );
        }
        else if(TagRobotSmallEnemy.checkSerialMessage(sSerialData1, sSerialData2, sSerialData3))
        {
             TagRobotSmallEnemy.calculatePosition();
             emit printRealValueBottom(TagRobotSmallEnemy.getX_Position(), TagRobotSmallEnemy.getY_Position());
             this->MyQueueRealValuesBottom->send( TagRobotSmallEnemy.getX_Position(), TagRobotSmallEnemy.getY_Position() );
        }

    }
}
