#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "plasma/randomplasma.h"
#include "plasma/approcplasma.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    int width = ui->widthSpin->value(), height = ui->heightSpin->value();
    _plasma = new RandomPlasma(height,
                               width,
                               ui->deflectionSpin->value(),
                               ui->alphaSpin->value());
    _plasma->setSceneRect(0, 0, width, height);
    _plasma->draw();
    ui->plasmaView->setScene(_plasma);
}

void MainWindow::on_savePlasmaButton_clicked()
{
    QString path = QFileDialog::getSaveFileName();
    QByteArray bytearray = path.toUtf8();
    const char *filename = bytearray.constData();
    _plasma->savePlasma(filename);
}

void MainWindow::on_loadPlasmaButton_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    QByteArray bytearray = path.toUtf8();
    const char *filename = bytearray.constData();

    InterpolWay interpol;
    if (ui->newtonRadio->isChecked()) interpol = NEWTON;
    else if (ui->splineRadio->isChecked()) interpol = SPLINE;
    else interpol = MINSQUARES;
    int width = ui->widthSpin->value(), height = ui->heightSpin->value();
    _plasma = new ApprocPlasma(height,
                               width,
                               interpol,
                               filename);
    _plasma->setSceneRect(0, 0, width, height);
    _plasma->draw();
    ui->plasmaView->setScene(_plasma);
}
