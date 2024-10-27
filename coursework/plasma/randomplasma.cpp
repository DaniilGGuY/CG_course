#include "randomplasma.h"

RandomPlasma::RandomPlasma(int width, int height, int deflection, double alpha)
    : BasePlasma(width, height, deflection, alpha)
{
    _rand.seed(QDateTime::currentMSecsSinceEpoch());

    _data[0][0] = _rand.bounded(MAX_DEPTH, MAX_HEIGHT);
    _data[0][_width - 1] = _rand.bounded(MAX_DEPTH, MAX_HEIGHT);
    _data[_height - 1][0] = _rand.bounded(MAX_DEPTH, MAX_HEIGHT);
    _data[_height - 1][_width - 1] = _rand.bounded(MAX_DEPTH, MAX_HEIGHT);

    build(0, 0, _width - 1, _height - 1);
}

RandomPlasma::~RandomPlasma() {}

void RandomPlasma::build(int x1, int y1, int x2, int y2)
{
    if (x2 - x1 <= 1 && y2 - y1 <= 1) return ;
    int mx = x1 + (x2 - x1) / 2, my = y1 + (y2 - y1) / 2;
    int noise = getRandValue() * (log2(x2  - x1) / log2(_width) * _alpha);
    if (_data[mx][my] == MAX_DEPTH - 1) {
        _data[mx][my] = getMiddleVal({_data[x1][y1], _data[x1][y2], _data[x2][y1], _data[x2][y2]});
        _data[mx][my] = fixValue(_data[mx][my] + noise);
    }
    if (_data[x1][my] == MAX_DEPTH - 1) {
        _data[x1][my] = getMiddleVal({_data[x1][y1], _data[x1][y2], _data[mx][my]});
        _data[x1][my] = fixValue(_data[x1][my] + noise);
    }
    if (_data[x2][my] == MAX_DEPTH - 1) {
        _data[x2][my] = getMiddleVal({_data[x2][y1], _data[x2][y2], _data[mx][my]});
        _data[x2][my] = fixValue(_data[x2][my] + noise);
    }
    if (_data[mx][y1] == MAX_DEPTH - 1) {
        _data[mx][y1] = getMiddleVal({_data[x1][y1], _data[x2][y1], _data[mx][my]});
        _data[mx][y1] = fixValue(_data[mx][y1] + noise);
    }
    if (_data[mx][y2] == MAX_DEPTH - 1) {
        _data[mx][y2] = getMiddleVal({_data[x1][y2], _data[x2][y2], _data[mx][my]});
        _data[mx][y2] = fixValue(_data[mx][y2] + noise);
    }

    build(x1, y1, mx, my);
    build(x1, my, mx, y2);
    build(mx, y1, x2, my);
    build(mx, my, x2, y2);
}

int RandomPlasma::getRandValue()
{
    return _rand.bounded(-_deflection, _deflection);
}

int RandomPlasma::getMiddleVal(QVector<int> points)
{
    int val = 0;
    for (auto i : points)
        val += i;
    return val / points.size();
}

int RandomPlasma::fixValue(int value)
{
    if (value < MAX_DEPTH) return MAX_DEPTH;
    else if (value > MAX_HEIGHT) return MAX_HEIGHT;
    return value;
}
