/******************************************************************************/
/** \file       UltrasonicThread.cpp
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
#include "UltrasonicThread.hpp"
#include "UltrasonicTagClass.hpp"
#include "HexamiteRS232PortClass.h"

/* Imports Library */
#include <string>
#include <iostream>

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
UltrasonicThread::UltrasonicThread()
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
    //delete MySerialPort; // wenn diese Zeile einkommentiert ist, kommt
       // nach beendigung des GUIs "test.exe" funktioniert nicht mehr. (nicht immer reproduzierbar)
}


/*******************************************************************************
 *  Method :    run()
 ******************************************************************************/
/** \brief      The Thread main run method.
 *
 *  \author     bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
void UltrasonicThread::run()
{
    /* Define Local Variable */
    std::string sUSARTString;
    std::string sSerialData1;
    std::string sSerialData2;
    std::string sSerialData3;

    /* Create Object from UltrasonicTag Class*/
    UltrasonicTagClass TagRobotBigEnemy("P20");			/*!<  ID Tag Number T20 */
    UltrasonicTagClass TagRobotSmallEnemy("P21");		/*!<  ID Tag Number T21 */

    /* Set Team start Position for the UltrasonicTag Class */
    UltrasonicTagClass::setTeamStartPosition(TeamRight);

    /* Initialize USART-Interface with COM-Port 4 */
    MySerialPort = new HexamiteRS232Port(4);

    /*  Turn on Hexamite synchronizer  */
    MySerialPort->turnHexamiteUsbSynchronizerOn();

    std::string *strUnfilteredData = new std::string("...");

    while(1)
    {
        //DEBUG:
        //std::cout << "Hello, I am the Ultrasonic Thread." << std::endl;
        //msleep(1000);



        /* Get USART-String */
        MySerialPort->getHexamiteData(&sSerialData1, &sSerialData2, &sSerialData3);

        /* not working... */
        //MySerialPort->getAllLastUnfilteredHexamiteData(strUnfilteredData);
        //std::cout << "\nUnfilt.: " << *strUnfilteredData;
        //strUnfilteredData->clear();

        /* Put data on screen */
        std::cout << sSerialData1 << std::endl;
        std::cout << sSerialData2 << std::endl;
        std::cout << sSerialData3 << std::endl;
        emit newSerialMsgAvaiable( QString("") );
        emit newSerialMsgAvaiable( QString(sSerialData1.c_str()) );
        emit newSerialMsgAvaiable( QString(sSerialData2.c_str()) );
        emit newSerialMsgAvaiable( QString(sSerialData3.c_str()) );



        /* Check for Calculation*/
        if(TagRobotBigEnemy.checkSerialMessage(sSerialData1, sSerialData2, sSerialData3))
        {
             TagRobotBigEnemy.calculatePosition();

             std::cout <<  "Enemy Big Robot"  << std::endl;
             std::cout <<  "X-Position: " << TagRobotBigEnemy.getX_Position() << std::endl;
             std::cout <<  "Y-Position: " << TagRobotBigEnemy.getY_Position() << std::endl;
             emit newRealValueTopAvaiable(TagRobotBigEnemy.getX_Position(), TagRobotBigEnemy.getY_Position());
        }
        else if(TagRobotSmallEnemy.checkSerialMessage(sSerialData1, sSerialData2, sSerialData3))
        {
             TagRobotSmallEnemy.calculatePosition();

             std::cout <<  "Enemy Small Robot"  << std::endl;
             std::cout <<  "X-Position: " << TagRobotSmallEnemy.getX_Position() << std::endl;
             std::cout <<  "Y-Position: " << TagRobotSmallEnemy.getY_Position() << std::endl;
             emit newRealValueBottomAvaiable(TagRobotSmallEnemy.getX_Position(), TagRobotSmallEnemy.getY_Position());
        }

    }
}
