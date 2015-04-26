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

#define MAX_MEASUREMENT_POINTS_PER_SITE     ( 10 )
#define MAX_MEASUREMENT_POINTS              ( MAX_MEASUREMENT_POINTS_PER_SITE*2 )

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
    bool mpaintflag = 0 ;
    int XBottomValue = 0;
    int XTopValue = 0;
    int YTopValue = 0;
    int YBottomValue = 0;

};

enum {FALSE = 0, TRUE = 1 };


#endif // MAINWINDOW_H
