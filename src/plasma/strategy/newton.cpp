#include "newton.h"

Newton::Newton(int power) : _power(power) {}

Newton::~Newton() {}

double Newton::calcValue(QVector<double> x_vals, QVector<double> y_vals, double num)
{
    QVector<double> x, y;
    int i = 0;
    while (x_vals[i] < num) ++i;
    --i;
    if (i + _power + 1 > x_vals.size()) {
        for (int j = x_vals.size() - _power - 1; j < x_vals.size(); ++j) {
            x.append(x_vals[j]);
            y.append(y_vals[j]);
        }
    }
    else {
        for (int j = i; j < i + _power + 1; ++j) {
            x.append(x_vals[j]);
            y.append(y_vals[j]);
        }
    }

    int n = x.size();
    _table.resize(n);
    for (int i = 0; i < n; ++i) _table[i].resize(n);
    for (int i = 0; i < n; ++i) _table[0][i] = y[i];
    for (int i = 1; i < n; ++i)
        for (int j = i; j < n; ++j)
            _table[i][j] = (_table[i - 1][j] - _table[i - 1][j - 1]) / (x[j] - x[j - i]);

    double res = 0.0;
    for (int i = 0; i <= _power; ++i) {
        double temp = _table[i][i];
        for (int j = 0; j < i; ++j) {
            temp *= num - x[j];
        }
        res += temp;
    }
    return res;
}
