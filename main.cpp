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
 *
 *
 *
 ******************************************************************************/



/* Includes ------------------------------------------------------------------*/
#include "mainwindow.h"
#include <QApplication>


/* Private functions ---------------------------------------------------------*/

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow GUI;
    GUI.show();
    return a.exec();
}
