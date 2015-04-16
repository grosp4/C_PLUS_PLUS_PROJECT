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

private:
    Ui::MainWindow *ui;
    int getvalues();
    int setamountofmeasurements(int increase);
    int getamountofmeasurements();

};

extern int testvalue;

#endif // MAINWINDOW_H
