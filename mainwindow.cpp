#include "mainwindow.h"
#include "ui_mainwindow.h"

/* initialize counting variable */
int NumberOfMeasurements = 0;
int MaxNumberOfMeasurements = 0;

/* initialize measurement array */
/* it will be used as following: 10 measurements, 4 values each measurement: X,Y TOP, X,Y BOTTOM */
int  MeasurementValues [10][4] = {0} ;


/* Constructor */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    /* get relativ values of the picture*/
     QPixmap Pixmap_X(qApp->applicationDirPath() + "/pictures/madeingermany.jpeg");
       ui->PictureLabel->setPixmap(Pixmap_X);

    /* connect a signal to a slot function to change a value of a label */
    connect(ui->getvaluesbutton,SIGNAL(clicked()),this,SLOT(getValueButtonClicked()));
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(getBackButtonClicked()));
    connect(ui->nextButon,SIGNAL(clicked()),this,SLOT(getNextButtonClicked()));

}

/* Destructor */
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::getValueButtonClicked()
{
    /* Call function to get values, cleanr the label write them into our labels */
  int value = 9999;

  /* update number of observations */
  value = setamountofmeasurements(1);
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
        NumberOfMeasurements = NumberOfMeasurements + 1;
        MaxNumberOfMeasurements = MaxNumberOfMeasurements +1;
    }
    else
    {
         NumberOfMeasurements = NumberOfMeasurements - 1;
    }
   return  NumberOfMeasurements;
}
