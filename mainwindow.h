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
    UltrasonicThread *MyUltrasonicThread;
    int getvalues();
    int setamountofmeasurements(int increase);
    int getamountofmeasurements();
    void getPortNumber();



};


#endif // MAINWINDOW_H
