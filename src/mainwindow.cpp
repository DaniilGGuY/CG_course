#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "plasma/randomplasma.h"
#include "plasma/approcplasma.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _scene3d = new Scene3D;
    _scene3d->setSceneRect(0, 0, WIDTH, HEIGHT);
    _scene3d->setParams(WIDTH, HEIGHT, {0, 1000, 0});
    ui->view3D->setScene(_scene3d);
    _monotic = false;
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        _scene3d->cameraRotateXZ(10);
        break;
    case Qt::Key_D:
        _scene3d->cameraRotateXZ(-10);
        break;
    case Qt::Key_W:
        _scene3d->cameraRotateZY(10);
        break;
    case Qt::Key_S:
        _scene3d->cameraRotateZY(-10);
        break;
    case Qt::Key_Q:
        _scene3d->cameraZoom(-500);
        break;
    case Qt::Key_E:
        _scene3d->cameraZoom(500);
        break;
    case Qt::Key_R:
        _scene3d->cameraReset();
    default:
        break;
    }

    _scene3d->draw();
}

void MainWindow::on_buildLandscape_clicked()
{
    _scene3d->loadModel(_plasma, _monotic);
    _scene3d->draw();
}

void MainWindow::on_setLight_clicked()
{
    QVector3D new_pos = QVector3D(ui->lightXSpin->value(), ui->lightYSpin->value(), ui->lightZSpin->value());
    _scene3d->setLightPos(new_pos);
    _scene3d->draw();
}

void MainWindow::on_landscapeParamsButton_clicked()
{
    _scene3d->setInterpols(ui->landscapeXWidthSpin->value(), ui->landscapeYWidthSpin->value());
    _scene3d->loadModel(_plasma, _monotic);
    _scene3d->draw();
}

void MainWindow::on_landscapeColorButton_clicked()
{
    _monotic = 1 - _monotic;
    _scene3d->loadModel(_plasma, _monotic);
    _scene3d->draw();
}

