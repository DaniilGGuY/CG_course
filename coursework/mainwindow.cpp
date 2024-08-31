#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _plasma = new Plasma(0, 512, 512, 30);
    _plasma->setSceneRect(0, 0, 512, 512);
    _plasma->drawPlasma();
    ui->graphicsView->setScene(_plasma);
}

MainWindow::~MainWindow()
{
    delete ui;
}
