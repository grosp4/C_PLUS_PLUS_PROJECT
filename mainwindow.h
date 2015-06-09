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

/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/* Imports Header Files*/
#include "UltrasonicThread.hpp"
#include "CalibrationMeasurementClass.h"
#include "MsgQueueClass.hpp"


/* Imports Library */
#include <QMainWindow>
#include <QObject>


/* Class Constant Declaration--------------------------------------------------*/
#define RATIO_PICTURE_TO_COORDINATES_X          (6.2)
#define RATIO_PICTURE_TO_COORDINATES_Y          (6.4)
#define OFFSET_X_VALUE_PICTURE_LABEL            (355)
#define OFFSET_Y_VALUE_PICTURE_LABEL            (170)

#define OFFSET_GRAPHICS_X                         (-30)
#define OFFSET_GRAPHICS_Y                         (-30)
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public:
   void paintEvent(QPaintEvent *e);


public slots:
    void getValueButtonClicked();
    void getBackButtonClicked();
    void getNextButtonClicked();
    void generateOutputFile();
    void getPortValue();
    void getCommandlineValue();
    void WriteInScrollAreaSlot();
    void printSerialMsg(QString myString);
    void printRealValues(int XRealValue, int YRealValue);

private:
    Ui::MainWindow *ui;
    MsgQueueClass *MyMsgQueueRealValuesTop;
    MsgQueueClass *MyMsgQueueRealValuesBottom;
    CalibrationMeasurementClass *MyCalibrationMeasurement;
    UltrasonicThread *MyUltrasonicThread;
    int getvalues();
    int setamountofmeasurements(int increase);
    int getamountofmeasurements();
    void getPortNumber();

    /* private variables */
    bool bpaintflag = 0 ;
    int iGraphicsRealXValue = 0;
    int iGraphicsRealYValue = 0;

};

enum {FALSE = 0, TRUE = 1 };


#endif // MAINWINDOW_H
