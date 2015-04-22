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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
#ifdef TEST_THREAD_HELLO_WORLD
    explicit MainWindow(QWidget *parent = 0, testthread *OtherTestThread = 0);
#else
    explicit MainWindow(QWidget *parent = 0);
#endif

    ~MainWindow();


public:
    #ifdef TEST_THREAD_HELLO_WORLD
    testthread *MyTestThread; // holder for TestThread
    #endif
    void WriteInScrollArea(int testvalue);


public slots:
    void getValueButtonClicked();
    void getBackButtonClicked();
    void getNextButtonClicked();
    void getPortValue();
    void getCommandlineValue();
    void WriteInScrollAreaSlot();

private:
    Ui::MainWindow *ui;
    int getvalues();
    int setamountofmeasurements(int increase);
    int getamountofmeasurements();
    void getPortNumber();



};


#endif // MAINWINDOW_H
