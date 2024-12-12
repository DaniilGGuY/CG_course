#ifndef LEASTSQUARES_H
#define LEASTSQUARES_H

#include <QVector>
#include <cmath>
#include <QVector4D>

class LeastSquares
{
public:
    LeastSquares(QVector<QVector<double>> mat, int n);
    ~LeastSquares();
    double calcZ(double x, double y);
    void approc();

protected:
    void toTriangleMatrix();
    void solveMatrix();
    double calcCoef(double x, double y, int degx, int degy);
    void makeSlau();

private:
    int _n;
    QVector<QVector<double>> _mat;
    QVector<double> _solve;
    QVector<QVector4D> _table;
};

#endif // LEASTSQUARES_H
