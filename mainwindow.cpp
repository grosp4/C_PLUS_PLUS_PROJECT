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

    // create msgQueues for RealValuesTop and ..Bottom:
    this->MyMsgQueueRealValuesTop = new MsgQueue;
    this->MyMsgQueueRealValuesBottom = new MsgQueue;
    UltrasonicThread *MyUltrasonicThread =
            new UltrasonicThread( this->MyMsgQueueRealValuesTop, this->MyMsgQueueRealValuesBottom);
    MyUltrasonicThread->start();

    /* set scroll layout for scroll area */
    ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->scrollAreaWidgetContents->resize(ui->scrollArea->size().width() ,ui->scrollArea->size().height());
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->adjustSize();

    /* connect a signal to a slot function to change a value of a label */
    connect(ui->getvaluesbutton,SIGNAL(clicked()),this,SLOT(getValueButtonClicked()));

    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(getBackButtonClicked()));
    connect(ui->nextButon,SIGNAL(clicked()),this,SLOT(getNextButtonClicked()));
    connect(ui->portButton,SIGNAL(clicked()),this,SLOT(getPortValue()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(getCommandlineValue()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(WriteInScrollAreaSlot()));




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
 *  Method :getBackButtonClicked
 ******************************************************************************/
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::getValueButtonClicked()
{
    /* Call function to get values, cleanr the label write them into our labels */
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

  ui->calibrationStatusLabel->setText("Values have been added to database \ntake next values with NEXT ");

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
/** \brief
 *
 *  \author
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
/** \brief
 *
 *  \author
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
 *  Method :getvalues
 ******************************************************************************/
/** \brief
 *
 *  \author
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
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
int MainWindow::getamountofmeasurements()
{
   return  NumberOfMeasurements;
}


/*******************************************************************************
 *  Method :setamountofmeasurements
 ******************************************************************************/
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
int MainWindow::setamountofmeasurements(int increase)
{
    if (increase)
    {
        if ( (NumberOfMeasurements >= 10)&& (NumberOfMeasurements < 20) )
        {
            NumberOfMeasurements = NumberOfMeasurements + 1;
            MaxNumberOfMeasurements = MaxNumberOfMeasurements +1;
            ui->TeamnameLabel->setText(("TEAM RIGHT"));

        }


        if ( NumberOfMeasurements < 10)
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
        if((NumberOfMeasurements > 1) && (NumberOfMeasurements < 12) )
        {
            NumberOfMeasurements = NumberOfMeasurements - 1;
            ui->TeamnameLabel->setText(("TEAM LEFT"));
        }
        if(NumberOfMeasurements >= 12 )
        {
            NumberOfMeasurements = NumberOfMeasurements - 1;
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
/** \brief
 *
 *  \author
 *
 *  \return       None
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
/** \brief
 *
 *  \author
 *
 *  \return       None
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
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::printSerialMsg(QString myString)
{
    //QString myString = QString::number(testvalue);
    QString tempString;

    /* activate the console and delete the dumy text */
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
        //myString = ui->commandEdit->text();
        tempString = ui->ConsoleLabelToWriteTo->text();
        ui->ConsoleLabelToWriteTo->setText(tempString + "\n" + myString   );
        ui->commandEdit->clear();


    }





}

/*******************************************************************************
 *  Method :WriteInScrollAreaSlot
 ******************************************************************************/
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::WriteInScrollAreaSlot()
{
    QString tempString;
    QString myString;

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


    }

}

/*******************************************************************************
 *  Method :printRealValueTop
 ******************************************************************************/
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::printRealValueTop(int XTop, int YTop)
{
    ui->realXTopValue->clear();
    ui->realXTopValue->setNum(XTop);
    ui->realYTopValue->clear();
    ui->realYTopValue->setNum(YTop);
}

/*******************************************************************************
 *  Method :printRealValueBottom
 ******************************************************************************/
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::printRealValueBottom(int XBottom, int YBottom)
{
    ui->realXBottomValue->clear();
    ui->realXBottomValue->setNum(XBottom);
    ui->realYBottomValue->clear();
    ui->realYBottomValue->setNum(YBottom);

//    QPainter painter(this);
//    painter.drawPixmap(310,580,200,200,QPixmap(":/it_is.jpg"));
//    painter.drawPixmap(310,640,40,40,QPixmap(":/it_should_be.png"));
//    QMainWindow::paintingActive();
}

/*******************************************************************************
 *  Method :paintEvent
 ******************************************************************************/
/** \brief
 *
 *  \author
 *
 *  \return       None
 *
 ******************************************************************************/
void MainWindow::paintEvent(QPaintEvent *e)
{

      QPainter painter(this);
      painter.drawPixmap(280,0,681,551,QPixmap(":/emily_batty_1.jpg"));
      painter.drawPixmap(310,580,40,40,QPixmap(":/it_is.jpg"));
      painter.drawPixmap(310,640,40,40,QPixmap(":/it_should_be.png"));
      QMainWindow::paintEvent(e);


}
