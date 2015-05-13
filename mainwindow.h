/*****************************************************************************/
/** \file       MAINWINDOW_H
 *  \brief      Mainwindow headerfile
 *******************************************************************************
 *
 *  \defgroup   -
 *
 *  \ingroup    -
 *
 *  \brief      This file contains all slots and functions regarding MainWindow
 *
 *  \authors    grosp4
 *
 *  \date       14.04.2015
 *
 *  \remark     Last Modification
 *               \li grosp4, 14.04.2015, Created
 *
 ********************************************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "debug_configurations.hpp"
#include "testthread.hpp"
#include "UltrasonicThread.hpp"
#include "MsgQueue.hpp"
#include "CalibrationMeasurement.h"
//#include <globaldefines.h>

#define RATIO_PICTURE_TO_COORDINATES_X          (6.2)
#define RATIO_PICTURE_TO_COORDINATES_Y          (6.4)
#define OFFSET_X_VALUE_PICTURE_LABEL            (360)
#define OFFSET_Y_VALUE_PICTURE_LABEL            (155)

#define OFFSET_GRAPHICS_X                         (-30)
#define OFFSET_GRAPHICS_Y                         (-30)
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
#ifdef TEST_THREAD_HELLO_WORLD
    explicit MainWindow(testthread *OtherTestThread, QWidget *parent = 0);
#else
    //explicit MainWindow(UltrasonicThread *NewUltrasonicThread, QWidget *parent = 0);
    explicit MainWindow(QWidget *parent = 0);
#endif

    ~MainWindow();


public:
    #ifdef TEST_THREAD_HELLO_WORLD
    testthread *MyTestThread; // holder for TestThread
    #endif
   void paintEvent(QPaintEvent *e);
   void customEvent(QEvent* e);
   static const int MyEvent=1001;


public slots:
    void getValueButtonClicked();
    void getBackButtonClicked();
    void getNextButtonClicked();
    void getPortValue();
    void getCommandlineValue();
    void WriteInScrollAreaSlot();
    void printSerialMsg(QString myString);
    void printRealValueTop(int XTop, int YTop);
    void printRealValueBottom(int XBottom, int YBottom);

private:
    Ui::MainWindow *ui;
    MsgQueue *MyMsgQueueRealValuesTop;
    MsgQueue *MyMsgQueueRealValuesBottom;
    CalibrationMeasurement *MyCalibrationMeasurement;
    UltrasonicThread *MyUltrasonicThread;
    int getvalues();
    int setamountofmeasurements(int increase);
    int getamountofmeasurements();
    void getPortNumber();

    /* private variables */
    bool bpaintflag = 0 ;
    int iGraphicsXBottomValue = 0;
    int iGraphicsXTopValue = 0;
    int iGraphicsYTopValue = 0;
    int iGraphicsYBottomValue = 0;
};

enum {FALSE = 0, TRUE = 1 };


#endif // MAINWINDOW_H
