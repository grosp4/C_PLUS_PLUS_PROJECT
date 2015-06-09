/******************************************************************************/
/** \file       mainwindow.cpp
 *  \brief      This File contain Everything about the GUI
 *
 *******************************************************************************
 *
 *  \class      MainWindow
 *
 *  \brief      This File contain Everything about the GUI
 *
 *  \authors    grosp4
 *
 *  \date       14.04.2015
 *
 *  \remark     Last Modification
 *               \li grosp4, 03.05.2015, Updated
 *
 ******************************************************************************/
/* Imports Header Files*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UltrasonicTagClass.hpp"
#include "MsgQueueClass.hpp"
#include "TextFileClass.h"

/* Imports Library */
#include <QtGui>
#include <QPainter>
#include <qwidget.h>
#include <iostream>
#include <QScrollBar>
#include <QScrollArea>
#include <QEvent>
#include <QTime>
#include <time.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
QString Fun[9] = {
"When Alexander Bell invented the telephone he had 3 missed calls from Chuck Norris",
"There used to be a street named after Chuck Norris, but it was changed because nobody crosses Chuck Norris and lives.",
"Chuck Norris died 20 years ago, Death just hasn't built up the courage to tell him yet.",
"Chuck Norris has already been to Mars; that's why there are no signs of life.",
"Some magicans can walk on water, Chuck Norris can swim through land.",
"Chuck Norris and Superman once fought each other on a bet. The loser had to start wearing his underwear on the outside of his pants.",
"Chuck Norris has a grizzly bear carpet in his room. The bear isn't dead it is just afriad to move.",
"Chuck Norris once urinated in a semi truck's gas tank as a joke....that truck is now known as Optimus Prime.",
"Chuck Norris counted to infinity - twice."
};
int iNumberOfMeasurements = 0;
int iMaxNumberOfMeasurements = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
 *  Constructor : MainWindow()
 ******************************************************************************/
/** \brief        Constructor of the Class
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
MainWindow::MainWindow( QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString windowTitle = "RoboNaviKali - " + Fun[getvalues()];

    this->setWindowTitle(windowTitle);


    // create msgQueues for RealValuesTop and ..Bottom:
    MyMsgQueueRealValuesTop = new MsgQueueClass;
    MyUltrasonicThread = new UltrasonicThread( this->MyMsgQueueRealValuesTop);
    MyUltrasonicThread->start();

    MyCalibrationMeasurement = new CalibrationMeasurementClass;

    /* set scroll layout for scroll area */
    ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->scrollAreaWidgetContents->resize(ui->scrollArea->size().width() ,ui->scrollArea->size().height());
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->adjustSize();

    /* connect a signal to a slot  */
    connect(ui->btnGetValues,SIGNAL(clicked()),this,SLOT(getValueButtonClicked()));
    connect(ui->btnBack,SIGNAL(clicked()),this,SLOT(getBackButtonClicked()));
    connect(ui->btnNext,SIGNAL(clicked()),this,SLOT(getNextButtonClicked()));
    connect(ui->portButton,SIGNAL(clicked()),this,SLOT(getPortValue()));
    connect(ui->btnSendCommand,SIGNAL(clicked()),this,SLOT(getCommandlineValue()));
    connect(ui->btnSendCommand,SIGNAL(clicked()),this,SLOT(WriteInScrollAreaSlot()));
    connect(ui->btnGenerateOutputFile,SIGNAL(clicked()),this,SLOT(generateOutputFile()));

    /* Communication for serial message stream to GUI:*/
    connect( MyUltrasonicThread, SIGNAL(printSerialMsg(QString)), this, SLOT(printSerialMsg(QString)));

    /* Communication for printing current real values to GUI:*/
    connect( MyUltrasonicThread, SIGNAL(printRealValues(int,int)), this, SLOT(printRealValues(int,int)));
}

/*******************************************************************************
 *  Deconstrunctor : ~MainWindow()
 ******************************************************************************/
/** \brief        Deconstrunctor of the Class
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
MainWindow::~MainWindow()
{
    MyUltrasonicThread->terminate();
    delete MyUltrasonicThread;
    delete ui;
}

/*******************************************************************************
 *  Method :getValueButtonClicked()
 ******************************************************************************/
/** \brief        stores the values given by ultrasonic thread to GUI in local
 *                array and prints it to gui
 *
 *  \author       grosp4/bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::getValueButtonClicked()
{

  /* get UPS Position data */
  int iXReal = 0, iYReal = 0;

  MyMsgQueueRealValuesTop->receive(&iXReal, &iYReal);

  /* save UPS Position data into array */
  MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->XReal = iXReal;
  MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->YReal = iYReal;

  /* print UPS Position data to second row of GUI */
  ui->lblRealXValue->clear();
  ui->lblRealXValue->setNum(iXReal);

  ui->lblRealYValue->clear();
  ui->lblRealYValue->setNum(iYReal);


  /* print User Info */
  ui->lblCalibrationStatus->setText("Values have been added to database \ntake next values by pressing NEXT ");

}


/*******************************************************************************
 *  Method :getBackButtonClicked()
 ******************************************************************************/
/** \brief        decreases the current number and refresh with new data the GUI
 *                is used for the measurements points
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::getBackButtonClicked()
{
    int iValue = 9999;
    /* decrase number of Measurements */
    iValue = setamountofmeasurements(0);
    ui->lblMeassureNumber->setNum((iValue + 1));

    /* get saved number and write them into the label */
    ui->lblRealXValue->clear();
    ui->lblRealXValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->XReal);
    ui->lblRealYValue->clear();
    ui->lblRealYValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->YReal);

    /* set desired values */
    ui->lblDesiredXValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->XDesired);
    ui->lblDesiredYValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->YDesired);


    /* update calibrationStatusLabel */
    ui->lblCalibrationStatus->setText("Ready to calibrate");

    /* repaint the picture */
    repaint();
}


/*******************************************************************************
 *  Method :getNextButtonClicked()
 ******************************************************************************/
/** \brief        increases the current number and refresh with new data the GUI
 *                is used for the measurements points
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::getNextButtonClicked()
{
    int iValue = 9999;
    /* increase number of Measurements */
    iValue = setamountofmeasurements(1);
    ui->lblMeassureNumber->setNum((iValue + 1));

    /* get saved number and write them into the label */
    ui->lblRealXValue->clear();
    ui->lblRealXValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->XReal);
    ui->lblRealYValue->clear();
    ui->lblRealYValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->YReal);

    /* set desired values */
    ui->lblDesiredXValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->XDesired);
    ui->lblDesiredYValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->YDesired);

    /* update calibrationStatusLabel */
    ui->lblCalibrationStatus->setText("Ready to calibrate");

    /* repaint the picture */
    repaint();
}

/*******************************************************************************
 *  Method :generateOutputFile()
 ******************************************************************************/
/** \brief        generate the Output File for saving the Data
 *
 *  \author       grosp4/bartj2
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::generateOutputFile()
{
     /* print User Info */
    MyCalibrationMeasurement->generateOutputFile();

    /* print User Info */
    ui->lblStatus->setText("Output File generated");
}


/*******************************************************************************
 *  Method :getvalues()
 ******************************************************************************/
/** \brief        auxillary function for getting a random Number
 *
 *  \author       grosp4
 *
 *  \return       iValue
 *
 ******************************************************************************/
int MainWindow::getvalues()
{
   srand (time(NULL));
   int iValue = rand() % 100;
   iValue = iValue / 10;
   return  iValue;
}

/*******************************************************************************
 *  Method :getamountofmeasurements()
 ******************************************************************************/
/** \brief          returns the number of measurements
 *
 *  \author         grosp4
 *
 *  \return         iNumberOfMeasurements
 *
 ******************************************************************************/
int MainWindow::getamountofmeasurements()
{
   return  iNumberOfMeasurements;
}


/*******************************************************************************
 *  Method :setamountofmeasurements()
 ******************************************************************************/
/** \brief          sets the amount of numbers of measurments in the data array
 *
 *
 *  \author         grosp4
 *
 *  \param          increase Value
 *
 *  \return         iNumberOfMeasurements
 *
 ******************************************************************************/
int MainWindow::setamountofmeasurements(int increase)
{
    if (increase)
    {
        if ( (iNumberOfMeasurements >= (MAX_MEASUREMENT_POINTS_PER_SITE-1)) && (iNumberOfMeasurements < (MAX_MEASUREMENT_POINTS-1) ))
        {
            iNumberOfMeasurements = iNumberOfMeasurements + 1;
            iMaxNumberOfMeasurements = iMaxNumberOfMeasurements + 1;
            ui->lblTeamSide->setText(("TEAM RIGHT"));

            /* inform UPS Calculation Thread about change of team site */
            UltrasonicTagClass::setTeamStartPosition(TeamRight);
        }


        if ( iNumberOfMeasurements < (MAX_MEASUREMENT_POINTS_PER_SITE -1))
        {
            iNumberOfMeasurements = iNumberOfMeasurements + 1;
            iMaxNumberOfMeasurements = iMaxNumberOfMeasurements + 1;
            ui->lblTeamSide->setText(("TEAM LEFT"));

            /* inform UPS Calculation Thread about change of team site */
            UltrasonicTagClass::setTeamStartPosition(TeamLeft);
        }


        else
        {
            iNumberOfMeasurements = iNumberOfMeasurements;
        }

    }
    else
    {
        if((iNumberOfMeasurements > 0) && (iNumberOfMeasurements < (MAX_MEASUREMENT_POINTS_PER_SITE + 1 ) ) )
        {
            iNumberOfMeasurements = iNumberOfMeasurements - 1;
            iMaxNumberOfMeasurements = iMaxNumberOfMeasurements - 1;
            ui->lblTeamSide->setText(("TEAM LEFT"));

            /* inform UPS Calculation Thread about change of team site */
            UltrasonicTagClass::setTeamStartPosition(TeamLeft);
        }
        if(iNumberOfMeasurements >= (MAX_MEASUREMENT_POINTS_PER_SITE + 1) )
        {
            iNumberOfMeasurements = iNumberOfMeasurements - 1;
            iMaxNumberOfMeasurements = iMaxNumberOfMeasurements - 1;
            ui->lblTeamSide->setText(("TEAM RIGHT"));

            /* inform UPS Calculation Thread about change of team site */
            UltrasonicTagClass::setTeamStartPosition(TeamRight);
        }
        else
        {
            iNumberOfMeasurements = iNumberOfMeasurements;

        }
    }
   return  iNumberOfMeasurements;
}



/*******************************************************************************
 *  Method :getPortValue()
 ******************************************************************************/
/** \brief          inreads the value of the number given by the User via GUI
 *                  forwards this information to the RS232 function
 *
 *  \author         grosp4
 *
 *  \return         None
 *
 ******************************************************************************/
void MainWindow::getPortValue()
{
    std:: string TempString;
    QString myString;

    myString = ui->textfieldPortEdit->text();
    ui->lblStatus->clear();
    this->MyUltrasonicThread->MySerialPort->changeHexamiteRS232Port(myString.toInt(), &TempString);
    ui->lblStatus->setText( QString::fromStdString(TempString));
}


/*******************************************************************************
 *  Method :getCommandlineValue()
 ******************************************************************************/
/** \brief          inreads commands given by the user via Commandline
 *
 *  \author         grosp4
 *
 *  \return         None
 *
 ******************************************************************************/
void MainWindow::getCommandlineValue()
{
    QString myString;
    myString = ui->textfieldCommandEdit->text();
    ui->lblStatus->clear();
    ui->lblStatus->setText("Command" + myString +" has been sent" );
}


/*******************************************************************************
 *  Method :printSerialMsg()
 ******************************************************************************/
/** \brief        This function is called another thread to write values given by RS232
 *                into the Log console.
 *
 *  \author       bartj2, grosp4
 *
 *  \param        myString String to Print out
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::printSerialMsg(QString myString)
{

    QString tempString;
    QScrollBar *sb = ui->scrollArea->verticalScrollBar();

    /* check if received String is not Empty */
    if( myString.isEmpty()!= 1)
    {
     ui->lblConsoleToWriteTo->setText(myString);
     sb->setValue(sb->maximum());
    }
}
/*******************************************************************************
 *  Method :WriteInScrollAreaSlot()
 ******************************************************************************/
/** \brief          This function is called by signal to write the Commandline text
 *                  into the Log console. Autoscroll is active by default
 *
 *  \author         grosp4
 *
 *  \return         None
 *
 ******************************************************************************/
void MainWindow::WriteInScrollAreaSlot()
{
    QString tempString;
    QString myString;
    QScrollBar *sb = ui->scrollArea->verticalScrollBar();


    /* get String from Textfield */
    myString = ui->textfieldCommandEdit->text();


    /* check if received String is not Empty */
    if( myString.isEmpty()!= 1)
    {
        tempString = ui->lblConsoleToWriteTo->text();
        ui->lblConsoleToWriteTo->setText(tempString + "\n" + myString   );
        this->MyUltrasonicThread->MySerialPort->sendHexamiteData(myString.toLocal8Bit().constData());
        ui->textfieldCommandEdit->clear();
        sb->setValue(sb->maximum());
    }

}

/*******************************************************************************
 *  Method :printRealValue()
 ******************************************************************************/
/** \brief          is called by another thread, sets values on the GUI, creates an event!
 *
 *  \author         grosp4, bartj2
 *
 *  \param          XTop    X-Coordinate
 *
 *  \param          YTop    Y-Coordinate
 *
 *  \return         None
 *
 ******************************************************************************/
void MainWindow::printRealValues(int XRealValue, int YRealValue)
{
    /* Update value*/
    iGraphicsRealXValue =XRealValue;
    iGraphicsRealYValue =YRealValue;
    ui->lblRealXValue->clear();
    ui->lblRealXValue->setNum(XRealValue);
    ui->lblRealYValue->clear();
    ui->lblRealYValue->setNum(YRealValue);

    /* repaint the picture */
    repaint();

}

/*******************************************************************************
 *  Method :paintEvent()
 ******************************************************************************/
/** \brief      gets called by any event, does some painting
 *
 *  \author     grosp4
 *
 *  \param         e QEvent from GUI
 *
 *  \return     None
 *
 ******************************************************************************/
void MainWindow::paintEvent(QPaintEvent *e)
{

    /* prints at every refresh static pictures */
    QPainter painter(this);
    painter.drawPixmap(310, 620 ,30,30,QPixmap(":/it_is.png"));
    painter.drawPixmap(310,575,30,30,QPixmap(":/it_should_be.jpg"));



        /* if the event is called while we have less than MAX_MEASUREMENT_POINTS_PER_SITE */
        if( iNumberOfMeasurements <= (MAX_MEASUREMENT_POINTS_PER_SITE-1))
        {
         painter.drawPixmap(199,60,761,469,QPixmap(":/Map_Left"));
        }
        else
        {
         painter.drawPixmap(199,60,761,469,QPixmap(":/Map_Right"));
        }
        /* reset flag for painting*/
        bpaintflag = false;



    /* Update graphics data on GUI */
    ui->lblMeassureNumber->setNum((iNumberOfMeasurements+1));
    ui->lblDesiredXValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->XDesired);
    ui->lblDesiredYValue->setNum(MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->YDesired);

    /* print desired coordinates */
    painter.drawPixmap(OFFSET_X_VALUE_PICTURE_LABEL + OFFSET_GRAPHICS_X + (MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->XDesired / RATIO_PICTURE_TO_COORDINATES_X),  OFFSET_Y_VALUE_PICTURE_LABEL + OFFSET_GRAPHICS_Y + (MyCalibrationMeasurement->MeasurementPoints[iNumberOfMeasurements]->YDesired / RATIO_PICTURE_TO_COORDINATES_Y), 30, 30, QPixmap(":/it_should_be.jpg"));
    painter.drawPixmap( OFFSET_X_VALUE_PICTURE_LABEL + OFFSET_GRAPHICS_X + (iGraphicsRealXValue / RATIO_PICTURE_TO_COORDINATES_X) , OFFSET_Y_VALUE_PICTURE_LABEL + OFFSET_GRAPHICS_Y + (iGraphicsRealYValue / RATIO_PICTURE_TO_COORDINATES_Y), 30, 30, QPixmap(":/it_is.png"));

    QMainWindow::paintEvent(e);
}

