/******************************************************************************/
/** \file       MainWindow.c
 *  \brief      Controls the GUI an all elements which are taking interactions with it
 *******************************************************************************
 *
 *  \brief     Controls the GUI an all elements which are taking interactions with it
 *
 *  \mainpage   -
 *
 *  \details    -
 *
 *  \addtogroup  MainWindow.c
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
#include "ui_mainwindow.h"
#include <QtGui>
#include "testthread.hpp"
#include "debug_configurations.hpp"
#include <QPainter>
#include <qwidget.h>
#include "MsgQueue.hpp"
#include <iostream>
#include <QScrollBar>
#include <QScrollArea>
#include <QEvent>
#include "TextFile.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* initialize counting variable */
int NumberOfMeasurements = 0;
int MaxNumberOfMeasurements = 0;
char myString[] = "Error";
int consoleHasBeenUsed  = 0;

/* initialize measurement array */
/* it will be used as following: 10 measurements, 4 values each measurement: X,Y TOP, X,Y BOTTOM */
QString  MeasurementValues [21][4] = {"0"} ;
int  DesiredValues [21][4] = {0} ;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
 *  Constructor : MainWindow
 ******************************************************************************/
/** \brief        Constructor of the Class
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
#ifdef TEST_THREAD_HELLO_WORLD
MainWindow::MainWindow(testthread *OtherTestThread, QWidget *parent) :
    QMainWindow(parent), MyTestThread(OtherTestThread),
    ui(new Ui::MainWindow)
#else
MainWindow::MainWindow( QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//,
    //MyUltrasonicThread(NewUltrasonicThread)
#endif

{
    ui->setupUi(this);
    QString windowTitle = " Chuck Norris jokes are coming soon";
    this->setWindowTitle(windowTitle);


    // create msgQueues for RealValuesTop and ..Bottom:
    MyMsgQueueRealValuesTop = new MsgQueue;
    MyMsgQueueRealValuesBottom = new MsgQueue;
    MyUltrasonicThread =
            new UltrasonicThread( this->MyMsgQueueRealValuesTop, this->MyMsgQueueRealValuesBottom);
    MyUltrasonicThread->start();

    // create whole measurement data:
    MyCalibrationMeasurement = new CalibrationMeasurement;


    /* set scroll layout for scroll area */
    ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->scrollAreaWidgetContents->resize(ui->scrollArea->size().width() ,ui->scrollArea->size().height());
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->adjustSize();

    /* connect a signal to a slot  */
    connect(ui->getvaluesbutton,SIGNAL(clicked()),this,SLOT(getValueButtonClicked()));
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(getBackButtonClicked()));
    connect(ui->nextButon,SIGNAL(clicked()),this,SLOT(getNextButtonClicked()));
    connect(ui->portButton,SIGNAL(clicked()),this,SLOT(getPortValue()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(getCommandlineValue()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(WriteInScrollAreaSlot()));
    connect(ui->generateOutputfile, SIGNAL(clicked()),
            MyCalibrationMeasurement, SLOT(generateOutputFile()));







    // Communication for serial message stream to GUI:
    connect( MyUltrasonicThread, SIGNAL(printSerialMsg(QString)),
             this, SLOT(printSerialMsg(QString)));
    // Communication for printing current real values to GUI:
    connect( MyUltrasonicThread, SIGNAL(printRealValueTop(int,int)),
             this, SLOT(printRealValueTop(int,int)));
    connect( MyUltrasonicThread, SIGNAL(printRealValueBottom(int,int)),
             this, SLOT(printRealValueBottom(int,int)));

#ifdef TEST_THREAD_HELLO_WORLD
    connect(ui->getvaluesbutton, SIGNAL(clicked()), MyTestThread, SLOT(print()) );
#endif

}

/*******************************************************************************
 *  Deconstrunctor : ~MainWindow
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
    //MyUltrasonicThread->terminate(); // programmabsturz hier!
    //delete MyUltrasonicThread;
    delete ui;
}

/************************************************************** MainWindow Functions ************************************************************/





/*******************************************************************************
 *  Method :getValueButtonClicked
 ******************************************************************************/
/** \brief        stores the values given by ultrasonic thread to GUI in local data
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::getValueButtonClicked()
{
    /* Call function to get values, clean the label write them into our labels */
  int value = 9999;
  QString valuesbymeasurement;

  /* update number of observations */
  value = getamountofmeasurements();
  ui->NumberLabel->setNum(value);


  /* get data and save it */
  valuesbymeasurement = ui->realXTopValue->text();
  ui->realXTopValue_2->clear();
  ui->realXTopValue_2->setText(valuesbymeasurement);
  /* Save in Array */
  MeasurementValues[NumberOfMeasurements][0] = valuesbymeasurement;

  valuesbymeasurement = ui->realYTopValue->text();
  ui->realYTopValue_2->clear();
  ui->realYTopValue_2->setText(valuesbymeasurement);
  /* Save in Array */
  MeasurementValues[NumberOfMeasurements][1] = valuesbymeasurement;

  valuesbymeasurement = ui->realXBottomValue->text();
  ui->realXBottomValue_2->clear();
  ui->realXBottomValue_2->setText(valuesbymeasurement);
  /* Save in Array */
  MeasurementValues[NumberOfMeasurements][2] = valuesbymeasurement;

  valuesbymeasurement = ui->realYBottomValue->text();
  ui->realYBottomValue_2->clear();
  ui->realYBottomValue_2->setText(valuesbymeasurement);
  /* Save in Array */
  MeasurementValues[NumberOfMeasurements][3] = valuesbymeasurement;

  ui->calibrationStatusLabel->setText("Values have been added to database \ntake next values by pressing NEXT ");

  int XBottom = 0;
  int YBottom = 0;
  int XTop = 0;
  int YTop = 0;

  MyMsgQueueRealValuesTop->receive(&XTop, &YTop);
  MyMsgQueueRealValuesBottom->receive(&XBottom, &YBottom);
  //MyCalibrationMeasurement.MeasurementPoints[NumberOfMeasurements].XRealTop = XTop;
  std::cout << "Top: X = " << XTop << ", Y = " << YTop << std::endl;
  std::cout << "Bottom: X = " << XBottom << ", Y = " << YBottom << std::endl;
}





/*******************************************************************************
 *  Method :getBackButtonClicked
 ******************************************************************************/
/** \brief        decreases the current number and refresh with new data the GUI
 *                is used for the measurements points
 *
 *  \author     grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::getBackButtonClicked()
{
    int value = 9999;
    /* decrase number of Measurements */
    value = setamountofmeasurements(0);
    ui->NumberLabel->setNum(value);


    QString valuesbymeasurement;

    /* get saved number and write it into the label */
    valuesbymeasurement = MeasurementValues[NumberOfMeasurements][3];
    ui->realYBottomValue_2->clear();
    ui->realYBottomValue_2->setText(valuesbymeasurement);


    /* get saved number and write it into the label */
    valuesbymeasurement = MeasurementValues[NumberOfMeasurements][2];
    ui->realXBottomValue_2->clear();
    ui->realXBottomValue_2->setText(valuesbymeasurement);

    /* get saved number and write it into the label */
    valuesbymeasurement = MeasurementValues[NumberOfMeasurements][1];
    ui->realYTopValue_2->clear();
    ui->realYTopValue_2->setText(valuesbymeasurement);

    /* get saved number and write it into the label */
    valuesbymeasurement = MeasurementValues[NumberOfMeasurements][0];
    ui->realXTopValue_2->clear();
    ui->realXTopValue_2->setText(valuesbymeasurement);


    /* update calibrationStatusLabel */
    ui->calibrationStatusLabel->setText("Ready to calibrate");
}


/*******************************************************************************
 *  Method :getNextButtonClicked
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
    int value = 9999;
    /* increase number of Measurements */
    value = setamountofmeasurements(1);
    ui->NumberLabel->setNum(value);

    QString valuesbymeasurement;
    /* get saved number and write it into the label */
    valuesbymeasurement = MeasurementValues[NumberOfMeasurements][3];
    ui->realYBottomValue_2->clear();
    ui->realYBottomValue_2->setText(valuesbymeasurement);

    /* get saved number and write it into the label */
    valuesbymeasurement = MeasurementValues[NumberOfMeasurements][2];
    ui->realXBottomValue_2->clear();
    ui->realXBottomValue_2->setText(valuesbymeasurement);

    /* get saved number and write it into the label */
    valuesbymeasurement = MeasurementValues[NumberOfMeasurements][1];
    ui->realYTopValue_2->clear();
    ui->realYTopValue_2->setText(valuesbymeasurement);

    /* get saved number and write it into the label */
    valuesbymeasurement = MeasurementValues[NumberOfMeasurements][0];
    ui->realXTopValue_2->clear();
    ui->realXTopValue_2->setText(valuesbymeasurement);

    /* update calibrationStatusLabel */
    ui->calibrationStatusLabel->setText("Ready to calibrate");
}



/*******************************************************************************
 *  Method :getvalues       - OBSOLETE -
 ******************************************************************************/
/** \brief        auxillary function for getting a random Number
 *
 *  \author       grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
int MainWindow::getvalues()
{
   int value = rand() % 100;
   return  value;
}

/*******************************************************************************
 *  Method :getamountofmeasurements
 ******************************************************************************/
/** \brief          returns the number of measurements
 *
 *  \author         grosp4
 *
 *  \return         None
 *
 ******************************************************************************/
int MainWindow::getamountofmeasurements()
{
   return  NumberOfMeasurements;
}


/*******************************************************************************
 *  Method :setamountofmeasurements
 ******************************************************************************/
/** \brief          sets the amount of numbers of measurments in the data array
 *
 *
 *  \author         grosp4
 *
 *  \return         None
 *
 ******************************************************************************/
int MainWindow::setamountofmeasurements(int increase)
{
    if (increase)
    {
        if ( (NumberOfMeasurements >= MAX_MEASUREMENT_POINTS_PER_SITE)&& (NumberOfMeasurements < MAX_MEASUREMENT_POINTS) )
        {
            NumberOfMeasurements = NumberOfMeasurements + 1;
            MaxNumberOfMeasurements = MaxNumberOfMeasurements +1;
            ui->TeamnameLabel->setText(("TEAM RIGHT"));

        }


        if ( NumberOfMeasurements < MAX_MEASUREMENT_POINTS_PER_SITE)
        {
            NumberOfMeasurements = NumberOfMeasurements + 1;
            MaxNumberOfMeasurements = MaxNumberOfMeasurements +1;
            ui->TeamnameLabel->setText(("TEAM LEFT"));
        }


        else
        {
            NumberOfMeasurements = NumberOfMeasurements;
        }

    }
    else
    {
        if((NumberOfMeasurements > 1) && (NumberOfMeasurements < (MAX_MEASUREMENT_POINTS_PER_SITE +2 ) ) )
        {
            NumberOfMeasurements = NumberOfMeasurements - 1;
            MaxNumberOfMeasurements = MaxNumberOfMeasurements - 1;
            ui->TeamnameLabel->setText(("TEAM LEFT"));
        }
        if(NumberOfMeasurements >= (MAX_MEASUREMENT_POINTS_PER_SITE +2) )
        {
            NumberOfMeasurements = NumberOfMeasurements - 1;
            MaxNumberOfMeasurements = MaxNumberOfMeasurements - 1;
            ui->TeamnameLabel->setText(("TEAM RIGHT"));
        }
        else
        {
            NumberOfMeasurements = NumberOfMeasurements;

        }
    }
   return  NumberOfMeasurements;
}



/*******************************************************************************
 *  Method :getPortValue
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
    QString myString;
    myString = ui->PortEdit->text();
    ui->statusLabel->clear();
    ui->statusLabel->setText("Port has been set to " + myString );
}


/*******************************************************************************
 *  Method :getCommandlineValue
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
    myString = ui->commandEdit->text();
    ui->statusLabel->clear();
    ui->statusLabel->setText("Command" + myString +" has been sent" );



#ifdef TEST_THREAD_HELLO_WORLD
    MyTestThread->print();
#endif
}


/*******************************************************************************
 *  Method :printSerialMsg
 ******************************************************************************/
/** \brief        This function is called another thread to write values given by RS232
 *                into the Log console.
 *
 *  \author       bartj2, grosp4
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::printSerialMsg(QString myString)
{

    QString tempString;
    QScrollBar *sb = ui->scrollArea->verticalScrollBar();

    /* activate the console and delete the dummy text */
    if (consoleHasBeenUsed == 0)
    {
        ui->ConsoleLabelToWriteTo->clear();
        tempString = ui->ConsoleLabelToWriteTo->text();
        ui->ConsoleLabelToWriteTo->setText(tempString + "\n" + myString   );
        ui->commandEdit->clear();
        consoleHasBeenUsed = 1;
    }
    else
    {

        tempString = ui->ConsoleLabelToWriteTo->text();
        ui->ConsoleLabelToWriteTo->setText(tempString + "\n" + myString   );
        ui->commandEdit->clear();
        sb->setValue(sb->maximum());

    }





}

/*******************************************************************************
 *  Method :WriteInScrollAreaSlot
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


    if (consoleHasBeenUsed == 0)
    {
        myString = ui->commandEdit->text();
        ui->commandEdit->clear();
        ui->ConsoleLabelToWriteTo->clear();
        ui->ConsoleLabelToWriteTo->setText(myString );
        ui->commandEdit->clear();
        consoleHasBeenUsed = 1;
    }

    else
    {
        myString = ui->commandEdit->text();
        tempString = ui->ConsoleLabelToWriteTo->text();
        ui->ConsoleLabelToWriteTo->setText(tempString + "\n" + myString   );
        ui->commandEdit->clear();
        sb->setValue(sb->maximum());
    }

}

/*******************************************************************************
 *  Method :printRealValueTop
 ******************************************************************************/
/** \brief          is called by another thread, sets values on the GUI, creates an event!
 *
 *  \author         grosp4, bartj2
 *
 *  \return         None
 *
 ******************************************************************************/
void MainWindow::printRealValueTop(int XTop, int YTop)
{
    ui->realXTopValue->clear();
    ui->realXTopValue->setNum(XTop);
    ui->realYTopValue->clear();
    ui->realYTopValue->setNum(YTop);

    QApplication::postEvent(this,new QEvent(QEvent::Type(MyEvent)));
}

/*******************************************************************************
 *  Method :printRealValueBottom
 ******************************************************************************/
/** \brief       is called by another thread, sets values on the GUI, creates an event!
 *
 *  \author      grosp4, bartj2
 *
 *  \return      None
 *
 ******************************************************************************/
void MainWindow::printRealValueBottom(int XBottom, int YBottom)
{

    YBottomValue = 50 + YBottomValue;
    XBottomValue = 50 + XBottomValue;
    ui->realXBottomValue->clear();
    ui->realXBottomValue->setNum(XBottom);
    ui->realYBottomValue->clear();
    ui->realYBottomValue->setNum(YBottom);

    QApplication::postEvent(this,new QEvent(QEvent::Type(MyEvent)));



}

/*******************************************************************************
 *  Method :paintEvent
 ******************************************************************************/
/** \brief      gets called by any event, does some painting
 *
 *  \author     grosp4
 *
 *  \return     None
 *
 ******************************************************************************/
void MainWindow::paintEvent(QPaintEvent *e)
{

    /* prints at every refresh static pictures */
    QPainter painter(this);
    painter.drawPixmap(310, 585 ,40,40,QPixmap(":/it_is.jpg"));
    painter.drawPixmap(310,640,40,40,QPixmap(":/it_should_be.png"));
    QMainWindow::paintEvent(e);


    /* prints initial field at startup */
    if (consoleHasBeenUsed == 0)
    {
        painter.drawPixmap(199,60,761,469,QPixmap(":/Map_Left"));
    }

    /* if a custom event has been called */
    if(mpaintflag)
    {
        /* if the event is called while we have less than MAX_MEASUREMENT_POINTS_PER_SITE */
        if( NumberOfMeasurements <= MAX_MEASUREMENT_POINTS_PER_SITE)
        {
          painter.drawPixmap(199,60,761,469,QPixmap(":/Map_Left"));
        }
        else
        {
           painter.drawPixmap(199,60,761,469,QPixmap(":/Map_Right"));
        }

        /* Update graphics data on GUI */
       QPainter painter(this);
       painter.drawPixmap(XBottomValue,XBottomValue,40,40,QPixmap(":/it_is.jpg"));

       /* reset flag for painting*/
       mpaintflag = false;
    }



}

/*******************************************************************************
 *  Method :customEvent
 ******************************************************************************/
/** \brief         Overridden Slot that is called when a Custom Event is caught
 *
 *  \author        grosp4
 *
 *  \return        None
 *
 ******************************************************************************/
void MainWindow::customEvent(QEvent* e)
  {
      if(e->type() == (QEvent::Type)1001)
      {
          /* if the specific custom event has been called, set the painting flag */
        mpaintflag = true;
        update();

      }
  }
