#include "randomplasma.h"

RandomPlasma::RandomPlasma(int width, int height, int deflection, double alpha)
    : BasePlasma(width, height), _deflection(deflection), _alpha(alpha)
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
    int noise = getRandValue() * (log2(x2 - x1) / log2(_width) * _alpha);
    if (_data[my][mx] == MAX_DEPTH - 1) {
        _data[my][mx] = getMiddleVal({_data[y1][x1], _data[y2][x1], _data[y1][x2], _data[y2][x2]});
        _data[my][mx] = fixValue(_data[my][mx] + noise);
    }
    if (_data[my][x1] == MAX_DEPTH - 1) {
        _data[my][x1] = getMiddleVal({_data[y1][x1], _data[y2][x1], _data[my][mx]});
        _data[my][x1] = fixValue(_data[my][x1] + noise);
    }
    if (_data[my][x2] == MAX_DEPTH - 1) {
        _data[my][x2] = getMiddleVal({_data[y1][x2], _data[y2][x2], _data[my][mx]});
        _data[my][x2] = fixValue(_data[my][x2] + noise);
    }
    if (_data[y1][mx] == MAX_DEPTH - 1) {
        _data[y1][mx] = getMiddleVal({_data[y1][x1], _data[y1][x2], _data[my][mx]});
        _data[y1][mx] = fixValue(_data[y1][mx] + noise);
    }
    if (_data[y2][mx] == MAX_DEPTH - 1) {
        _data[y2][mx] = getMiddleVal({_data[y2][x1], _data[y2][x2], _data[my][mx]});
        _data[y2][mx] = fixValue(_data[y2][mx] + noise);
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

int RandomPlasma::getMiddleVal(QVector<double> points)
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
