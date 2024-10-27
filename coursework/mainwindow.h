#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    BasePlasma *_plasma;
};
#endif // MAINWINDOW_H
