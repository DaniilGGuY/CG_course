#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "plasma\baseplasma.h"

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

private slots:
    void on_generateButton_clicked();

    void on_savePlasmaButton_clicked();

    void on_loadPlasmaButton_clicked();

private:
    Ui::MainWindow *ui;
    BasePlasma *_plasma;
};
#endif // MAINWINDOW_H
