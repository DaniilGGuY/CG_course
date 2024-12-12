#include "spline.h"

Spline::Spline(QVector<double> vec, double first, double last) : _first(first), _last(last)
{
    for (int i = 0; i < vec.size(); ++i)
        _table.append(QVector2D(i, vec[i]));
    _n = _table.size();
    calcA();
    calcC();
    calcB();
    calcD();
}

Spline::~Spline() {}

void Spline::calcA()
{
    _a.resize(_n - 1, 0);
    for (int i = 0; i < _n - 1; ++i)
        _a[i] = _table[i].y();
}

void Spline::calcB()
{
    _b.resize(_n - 1, 0);

    for (int i = 0; i < _n - 2; ++i)
    {
        double h_i = _table[i + 1].x() - _table[i].x();
        double dy_i = _table[i + 1].y() - _table[i].y();
        _b[i] = dy_i / h_i - 1 / 3 * h_i * (_c[i + 1] + 2 * _c[i]);
    }

    double h_N = _table[_n - 1].x() - _table[_n - 2].x();
    double dy_N = _table[_n - 1].y() - _table[_n - 2].y();
    _b[_n - 2] = dy_N / h_N - 1 / 3 * h_N * ((_last / 2) + 2 * _c[_n - 2]);
}

void Spline::calcC()
{
    _c.resize(_n - 1, 0);

    QVector<double> ksi(_n, 0), etta(_n, 0);
    _c[0] = _first / 2;
    ksi[1] = 0;
    etta[1] = _first / 2;

    for (int i = 2; i < _n; ++i)
    {
        double h_i = _table[i].x() - _table[i - 1].x();
        double h_i_1 = _table[i - 1].x() - _table[i - 2].x();
        ksi[i] = calc_ksi(ksi[i - 1], h_i, h_i_1);
        double dy_i = _table[i].y() - _table[i - 1].y();
        double dy_i_1 = _table[i - 1].y() - _table[i - 2].y();
        etta[i] = calc_etta(dy_i, dy_i_1, h_i, h_i_1, etta[i - 1], ksi[i - 1]);
    }
    _c[_n - 2] = etta[_n - 1] + (_last / 2) * ksi[_n - 1];

    for (int i = _n - 2; i > 0; --i)
        _c[i - 1] = etta[i] + _c[i] * ksi[i];
}

void Spline::calcD()
{
    _d.resize(_n - 1, 0);

    for (int i = 0; i < _n - 2; ++i)
    {
        double h_i = _table[i + 1].x() - _table[i].x();
        _d[i] = (_c[i + 1] - _c[i]) / (3 * h_i);
    }
    double h_N = _table[_n - 1].x() - _table[_n - 2].x();
    _d[_n - 2] = ((_last / 2) - _c[_n - 2]) / (3 * h_N);
}

double Spline::calc_ksi(double ksi_i, double h_i, double h_i_1)
{
    return -h_i / (2 * (h_i + h_i_1) + h_i_1 * ksi_i);
}

double Spline::calc_etta(double dy_i, double dy_i_1, double h_i, double h_i_1, double etta_i, double ksi_i)
{
    return (3 * (dy_i / h_i - dy_i_1 / h_i_1) - h_i_1 * etta_i) / (h_i_1 * ksi_i + 2 * (h_i + h_i_1));
}

double Spline::calcValue(double x)
{
    int i = 0;
    while (i < _table.size() - 2 && x > _table[i + 1].x()) ++i;

    double x_i = _table[i].x();
    double dx = x - x_i;

    return _a[i] + _b[i] * dx + _c[i] * dx * dx + _d[i] * dx * dx * dx;
}
