#ifndef NEWTON_H
#define NEWTON_H

#include <QVector>

class Newton
{
public:
    Newton(int power);
    ~Newton();
    double calcValue(QVector<double> x_vals, QVector<double> y_vals, double num);

private:
    int _power;
    QVector<QVector<double>> _table;
};

#endif // NEWTON_H
