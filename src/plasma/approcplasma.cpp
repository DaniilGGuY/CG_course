#include "approcplasma.h"
#include "strategy/newton.h"
#include "strategy/leastsquares.h"
#include "strategy/spline.h"

#include <QDebug>

ApprocPlasma::ApprocPlasma(int width, int height, InterpolWay interpol, std::string filename)
    : BasePlasma(width, height), _filename(filename)
{
    readPlasma();
    if (_width != _data[0].size() || _height != _data.size())
    {
        if (interpol == NEWTON) approc_nw();
        else if (interpol == SPLINE) approc_spline();
        else approc_squares();
    }
}

ApprocPlasma::~ApprocPlasma() {}

void ApprocPlasma::setHeight(QVector<QVector<double>> data)
{
    int height = data.size(), width = data[0].size();
    _data.resize(height);
    for (int i = 0; i < height; ++i) {
        _data[i].resize(width);
        for (int j = 0; j < width; ++j)
            _data[i][j] = data[i][j];
    }
}

void ApprocPlasma::readPlasma()
{
    std::ifstream file(_filename);
    int width, height;
    file >> width >> height;
    QVector<QVector<double>> data(height, QVector<double>(width));
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            file >> data[i][j];
    file.close();
    setHeight(data);
}

void ApprocPlasma::approc_nw()
{
    // 5 - оптимальное значение степени полинома Ньютона
    int power = 4;
    Newton *nw = new Newton(power);
    int N = _data.size();
    int M = _data[0].size();
    while (M * 2 <= _width)
    {
        for (int i = 0; i < N; ++i)
        {
            QVector<double> row_x, row_y;
            for (int j = 0; j < M; ++j)
            {
                row_x.append(j);
                row_y.append(_data[i][j]);
            }
            for (int j = 0; j < M - 1; ++j)
            {
                double val = nw->calcValue(row_x, row_y, j + 0.5);
                _data[i].insert(2 * j + 1, val);
            }
        }
        M = M * 2 - 1;
    }

    nw = new Newton(power);
    while (N * 2 <= _height)
    {
        for (int i = 0; i < N - 1; ++i)
            _data.insert(2 * i + 1, QVector<double>(M, 0));
        for (int i = 0; i < M; ++i)
        {
            QVector<double> col_x, col_y;
            for (int j = 0; j < N; ++j)
            {
                col_x.append(j);
                col_y.append(_data[2 * j][i]);
            }
            for (int j = 0; j < N - 1; ++j)
            {
                double val = nw->calcValue(col_x, col_y, j + 0.5);
                _data[2 * j + 1][i] = val;
            }
        }
        N = N * 2 - 1;
    }
    _width = _data[0].size();
    _height = _data.size();
}

void ApprocPlasma::approc_squares()
{
    // 10 - оптимальное значение степени
    int power = 10;
    LeastSquares *squares = new LeastSquares(_data, power);
    squares->approc();
    int n = _data.size(), m = _data[0].size();
    _data.resize(_height);
    for (int i = 0; i < _height; ++i) {
        _data[i].resize(_width);
        for (int j = 0; j < _width; ++j)
            _data[i][j] = squares->calcZ(i * n * 1.0 / _height, j * m * 1.0 / _width);
    }
}

void ApprocPlasma::approc_spline()
{
    int N = _data.size();
    int M = _data[0].size();
    while (M * 2 <= _width)
    {
        for (int i = 0; i < N; ++i)
        {
            QVector<double> row = _data[i];
            Spline *spline = new Spline(row, 0, 0);
            for (int j = 0; j < M - 1; ++j)
            {
                double val = spline->calcValue(j + 0.5);
                _data[i].insert(2 * j + 1, val);
            }
        }
        M = M * 2 - 1;
    }
    while (N * 2 <= _height)
    {
        for (int i = 0; i < N - 1; ++i)
            _data.insert(2 * i + 1, QVector<double>(M, 0));
        for (int i = 0; i < M; ++i)
        {
            QVector<double> col;
            for (int j = 0; j < N; ++j) col.append(_data[2 * j][i]);
            Spline *spline = new Spline(col, 0, 0);
            for (int j = 0; j < N - 1; ++j)
            {
                double val = spline->calcValue(j + 0.5);
                _data[2 * j + 1][i] = val;
            }
        }
        N = N * 2 - 1;
    }
    _width = _data[0].size();
    _height = _data.size();
}
