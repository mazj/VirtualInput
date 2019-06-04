#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setProperty("keyboard",true); // enable the keyboard. when there is no validator set the keyboard will show
    validator.setRange(0, 500);
    ui->lineEdit->setValidator(&validator); //add a int validator min value 0 max value 500. This will force the numpad to show, you can also use a QDoubleValidator

    ui->lineEdit_2->setProperty("keyboard",true);
    ui->lineEdit_2->setProperty("maxLength",5);//this can be used to limit the length of the string

    //it is also possible to set the properties in QT designer
}

MainWindow::~MainWindow()
{
    delete ui;
}
