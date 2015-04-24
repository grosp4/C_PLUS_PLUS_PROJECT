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
int  MeasurementValues [20][4] = {0} ;
int  DesiredValues [20][4] = {0} ;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* Constructor */
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

    UltrasonicThread *MyUltrasonicThread = new UltrasonicThread;
    MyUltrasonicThread->start();


    /* get relativ values of the picture*/
    QPixmap Pixmap_X(qApp->applicationDirPath() + "//madeingermany.jpg");

    if (Pixmap_X.isNull())
    {
        ui->PictureLabel->setText("Picture could not be loaded");
    }
    else
    {
        ui->PictureLabel->setPixmap(Pixmap_X);
    }



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

/* Destructor */
MainWindow::~MainWindow()
{
    //MyUltrasonicThread->terminate(); // programmabsturz hier!
    //delete MyUltrasonicThread;
    delete ui;
}

/************************************************************** MainWindow Functions ************************************************************/

void MainWindow::getValueButtonClicked()
{
    /* Call function to get values, cleanr the label write them into our labels */
  int value = 9999;

  /* update number of observations */
  value = getamountofmeasurements();
  ui->NumberLabel->setNum(value);


  value = getvalues ();
  ui->realXTopValue->clear();
  ui->realXTopValue->setNum(value);
  /* Save in Array */
  MeasurementValues[NumberOfMeasurements][0] = value;

  value = getvalues ();
  ui->realYTopValue->clear();
  ui->realYTopValue->setNum(value);
  /* Save in Array */
  MeasurementValues[NumberOfMeasurements][1] = value;

  value = getvalues ();
  ui->realXBottomValue->clear();
  ui->realXBottomValue->setNum(value);
  /* Save in Array */
  MeasurementValues[NumberOfMeasurements][2] = value;


  value = getvalues ();
  ui->realYBottomValue->clear();
  ui->realYBottomValue->setNum(value);
  /* Save in Array */
  MeasurementValues[NumberOfMeasurements][3] = value;

    ui->calibrationStatusLabel->setText("Values have been added to database \ntake next values with NEXT ");

}

/* goes back and shows old values */
void MainWindow::getBackButtonClicked()
{
    int value = 9999;
    /* decrase number of Measurements */
    value = setamountofmeasurements(0);
    ui->NumberLabel->setNum(value);

    /* get saved number and write it into the label */
    value = MeasurementValues[NumberOfMeasurements][3];
    ui->realYBottomValue->clear();
    ui->realYBottomValue->setNum(value);

    /* get saved number and write it into the label */
    value = MeasurementValues[NumberOfMeasurements][2];
    ui->realXBottomValue->clear();
    ui->realXBottomValue->setNum(value);

    /* get saved number and write it into the label */
    value = MeasurementValues[NumberOfMeasurements][1];
    ui->realYTopValue->clear();
    ui->realYTopValue->setNum(value);

    /* get saved number and write it into the label */
    value = MeasurementValues[NumberOfMeasurements][0];
    ui->realXTopValue->clear();
    ui->realXTopValue->setNum(value);


    /* update calibrationStatusLabel */
    ui->calibrationStatusLabel->setText("Ready to calibrate");
}


/* goes forward and shows values which are measured or 0 if not */
void MainWindow::getNextButtonClicked()
{
    int value = 9999;
    /* increase number of Measurements */
    value = setamountofmeasurements(1);
    ui->NumberLabel->setNum(value);


    /* get saved number and write it into the label */
    value = MeasurementValues[NumberOfMeasurements][3];
    ui->realYBottomValue->clear();
    ui->realYBottomValue->setNum(value);

    /* get saved number and write it into the label */
    value = MeasurementValues[NumberOfMeasurements][2];
    ui->realXBottomValue->clear();
    ui->realXBottomValue->setNum(value);

    /* get saved number and write it into the label */
    value = MeasurementValues[NumberOfMeasurements][1];
    ui->realYTopValue->clear();
    ui->realYTopValue->setNum(value);

    /* get saved number and write it into the label */
    value = MeasurementValues[NumberOfMeasurements][0];
    ui->realXTopValue->clear();
    ui->realXTopValue->setNum(value);

    /* update calibrationStatusLabel */
    ui->calibrationStatusLabel->setText("Ready to calibrate");
}



/* right now a function that pretends to get values from RS232 port */
int MainWindow::getvalues()
{
   int value = rand() % 100;
   return  value;
}

/* get measurement count */
int MainWindow::getamountofmeasurements()
{
   return  NumberOfMeasurements;
}


/*set measurement count */
/* increase == 1 , increase in steps of 1
 * increase == 0 , decrease in steps of 1
 * */
int MainWindow::setamountofmeasurements(int increase)
{
    if (increase)
    {
        if ( NumberOfMeasurements < 11)
        {
            NumberOfMeasurements = NumberOfMeasurements + 1;
            MaxNumberOfMeasurements = MaxNumberOfMeasurements +1;
            ui->TeamnameLabel->setText(("TEAM LEFT"));
        }
        if ( (NumberOfMeasurements >= 11)&& (NumberOfMeasurements < 20) )
        {
            NumberOfMeasurements = NumberOfMeasurements + 1;
            MaxNumberOfMeasurements = MaxNumberOfMeasurements +1;
           ui->TeamnameLabel->setText(("TEAM RIGHT"));

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



/* read portnumber and forward it */
void MainWindow::getPortValue()
{
    QString myString;
    myString = ui->PortEdit->text();
    ui->statusLabel->clear();
    ui->statusLabel->setText("Port has been set to " + myString );
}


/* read commandline and forward it to the status message */
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


/* Transform a integer into a string to write it to the mssage area */
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

/* get command of commandline and write it to console message area*/
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

/* print Current Real Value of Top Device to GUI */
void MainWindow::printRealValueTop(int XTop, int YTop)
{
    ui->realXTopValue->clear();
    ui->realXTopValue->setNum(XTop);
    ui->realYTopValue->clear();
    ui->realYTopValue->setNum(YTop);
}

/* print current real value of top device to GUI */
void MainWindow::printRealValueBottom(int XBottom, int YBottom)
{
    ui->realXBottomValue->clear();
    ui->realXBottomValue->setNum(XBottom);
    ui->realYBottomValue->clear();
    ui->realYBottomValue->setNum(YBottom);
}
