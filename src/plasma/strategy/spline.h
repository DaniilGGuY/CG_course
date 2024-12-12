#ifndef SPLINE_H
#define SPLINE_H

#include <QVector>
#include <QVector2D>

class Spline
{
public:
    Spline(QVector<double> vec, double first, double last);
    ~Spline();
    double calcValue(double x);

protected:
    void calcA();
    void calcB();
    void calcC();
    void calcD();
    double calc_ksi(double ksi_i, double h_i, double h_i_1);
    double calc_etta(double dy_i, double dy_i_1, double h_i, double h_i_1, double etta_i, double ksi_i);

private:
    double _first, _last;
    int _n;
    QVector<QVector2D> _table;
    QVector<double> _a;
    QVector<double> _b;
    QVector<double> _c;
    QVector<double> _d;
};

#endif // SPLINE_H
