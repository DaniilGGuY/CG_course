#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QKeyEvent>

#include "plasma/baseplasma.h"
#include "3d/scene3d.h"

#define  WIDTH     512
#define HEIGHT     512

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_generateButton_clicked();

    void on_savePlasmaButton_clicked();

    void on_loadPlasmaButton_clicked();

    void on_buildLandscape_clicked();

    void on_setLight_clicked();

private:
    Ui::MainWindow *ui;
    BasePlasma *_plasma;
    Scene3D *_scene3d;
};

#endif // MAINWINDOW_H
