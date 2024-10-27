#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "plasma/randomplasma.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _plasma = new RandomPlasma(WIDTH, HEIGHT, 30, 1.20);
    _plasma->setSceneRect(0, 0, WIDTH, HEIGHT);
    _plasma->draw();
    ui->graphicsView->setScene(_plasma);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    delete _plasma;
    _plasma = new RandomPlasma(WIDTH, HEIGHT, ui->deflection_spin->value(), ui->alpha_spin->value());
    _plasma->setSceneRect(0, 0, WIDTH, HEIGHT);
    _plasma->draw();
    ui->graphicsView->setScene(_plasma);
}

