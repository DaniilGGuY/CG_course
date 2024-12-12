#include "leastsquares.h"

LeastSquares::LeastSquares(QVector<QVector<double>> mat, int n) : _n(n + 1)
{
    for (int i = 0; i < mat.size(); ++i)
        for (int j = 0; j < mat[0].size(); ++j)
            _table.append(QVector4D(i, j, mat[i][j], 1));
}

LeastSquares::~LeastSquares() {}

void LeastSquares::toTriangleMatrix()
{
    int n = _mat.size();
    for (int k = 0; k < n - 1; ++k) {
        for (int i = k + 1; i < n; ++i) {
            double coef = -(_mat[i][k] / _mat[k][k]);
            for (int j = k; j < n + 1; ++j)
                _mat[i][j] += coef * _mat[k][j];
        }
    }
}

void LeastSquares::solveMatrix()
{
    toTriangleMatrix();
    int n = _mat.size();

    _solve.resize(n, 0);
    for (int i = n - 1; i > -1; --i) {
        for (int j = n - 1; j > i; --j) {
            _mat[i][n] -= _solve[j] * _mat[i][j];
            _solve[i] = _mat[i][n] / _mat[i][i];
        }
    }
}

double LeastSquares::calcCoef(double x, double y, int degx, int degy) { return pow(x, degx) * pow(y, degy); }

double LeastSquares::calcZ(double x, double y) {
    double z = 0;
    int k = 0;
    for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n - i; ++j) {
            z += _solve[k] * calcCoef(x, y, i, j);
            k += 1;
        }
    }
    return z;
}

void LeastSquares::makeSlau() {
    QVector<QVector<double>> coefs;
    QVector<double> res;
    for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n - i; ++j) {
            QVector<double> row;
            for (int k = 0; k < _n; ++k) {
                for (int l = 0; l < _n - k; ++l) {
                    QVector<double> sum_arr;
                    for (int p = 0; p < _table.size(); ++p)
                        sum_arr.append(calcCoef(_table[p].x(), _table[p].y(), k + i, l + j) * _table[p].w());
                    double sum = 0;
                    for (int p = 0; p < sum_arr.size(); ++p)
                        sum += sum_arr[p];
                    row.append(sum);
                }
            }
            coefs.append(row);
            QVector<double> sum_arr;
            for (int p = 0; p < _table.size(); ++p)
                sum_arr.append(calcCoef(_table[p].x(), _table[p].y(), i, j) * _table[p].z() * _table[p].w());
            double sum = 0;
            for (int p = 0; p < sum_arr.size(); ++p)
                sum += sum_arr[p];
            res.append(sum);
        }
    }

    for (int i = 0; i < coefs.size(); ++i) {
        _mat.append(coefs[i]);
        _mat[i].append(res[i]);
    }
}

void LeastSquares::approc() {
    makeSlau();
    solveMatrix();
}
