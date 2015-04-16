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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void getValueButtonClicked();
    void getBackButtonClicked();
    void getNextButtonClicked();
    void getPortValue();
    void getCommandlineValue();


private:
    Ui::MainWindow *ui;
    int getvalues();
    int setamountofmeasurements(int increase);
    int getamountofmeasurements();
    void getPortNumber();



};


#endif // MAINWINDOW_H
