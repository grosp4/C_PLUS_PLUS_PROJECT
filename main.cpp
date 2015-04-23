/******************************************************************************/
/** \file       Main.c
 *  \brief      Startup file. In this file is the main function, which is
 *              called at the startup of the program.
 *******************************************************************************
 *
 *  \brief      Startup file. In this file is the main function, which is
 *              called at the startup of the program.
 *
 *  \mainpage   -
 *
 *  \details    -
 *
 *  \addtogroup  main
 *  \brief      -
 *
 *  \authors    grosp4
 *
 *  \date       16.04.2015
 *
 *  \remark     Last Modification
 *               \li grosp4, 16.04.2015, Created
 *               \li bartj2, 21.04.2015, added test thread
 *
 *
 *
 ******************************************************************************/



/* Includes ------------------------------------------------------------------*/
#include "mainwindow.h"
#include <QApplication>
#include <QThread>
#include "debug_configurations.hpp"
#include "testthread.hpp"
#include <iostream>


/* Private functions ---------------------------------------------------------*/

int main(int argc, char *argv[])
{

#ifdef TEST_THREAD_HELLO_WORLD // ################################################
    // Create new thread:
    std::cout << "\n\nStart Test Thread..." << std::endl;
    testthread MyTestThread;
    MyTestThread.start();


    QApplication a(argc, argv);
    MainWindow GUI( &MyTestThread );


#else
    QApplication a(argc, argv);
    MainWindow GUI;
#endif

    GUI.show();   
    return a.exec();

}
