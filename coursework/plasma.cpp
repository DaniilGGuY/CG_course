#include "plasma.h"
#include <qdatetime.h>

Plasma::Plasma(QObject *parent, int width, int height, int deflection)
    : QGraphicsScene(parent), _width(width), _height(height), _deflection(deflection)
{
    _rand.seed(QDateTime::currentMSecsSinceEpoch());
    _data.resize(height);
    for (int i = 0; i < height; ++i)
        _data[i].resize(width);
}

Plasma::~Plasma() {}

void Plasma::buildPlasma(int x1, int y1, int x2, int y2)
{
    if (x2 - x1 <= 1 && y2 - y1 <= 1) return ;
    int mx = x1 + (x2 - x1) / 2, my = y1 + (y2 - y1) / 2;
    if (!_data[mx][my].isValid()) {
        _data[mx][my] = getMiddleColor({_data[x1][y1], _data[x1][y2], _data[x2][y1], _data[x2][y2]});
        addNoise(_data[mx][my]);
    }
    if (!_data[x1][my].isValid()) {
        _data[x1][my] = getMiddleColor({_data[x1][y1], _data[x1][y2], _data[mx][my]});
        addNoise(_data[x1][my]);
    }
    if (!_data[x2][my].isValid()) {
        _data[x2][my] = getMiddleColor({_data[x2][y1], _data[x2][y2], _data[mx][my]});
        addNoise(_data[x2][my]);
    }
    if (!_data[mx][y1].isValid()) {
        _data[mx][y1] = getMiddleColor({_data[x1][y1], _data[x2][y1], _data[mx][my]});
        addNoise(_data[mx][y1]);
    }
    if (!_data[mx][y2].isValid()) {
        _data[mx][y2] = getMiddleColor({_data[x1][y2], _data[x2][y2], _data[mx][my]});
        addNoise(_data[mx][y2]);
    }

    buildPlasma(x1, y1, mx, my);
    buildPlasma(x1, my, mx, y2);
    buildPlasma(mx, y1, x2, my);
    buildPlasma(mx, my, x2, y2);
}

void Plasma::drawPlasma()
{
    _data[0][0] = getRandColor();
    _data[0][_width - 1] = getRandColor();
    _data[_height - 1][0] = getRandColor();
    _data[_height - 1][_width - 1] = getRandColor();

    buildPlasma(0, 0, _width - 1, _height - 1);

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
            addLine(i, j, i, j, QPen(_data[i][j]));
}

int Plasma::getRandValue()
{
    return _rand.bounded(-_deflection, _deflection);
}

QColor Plasma::getRandColor()
{
    return QColor(_rand.bounded(0, 255), _rand.bounded(0, 255), _rand.bounded(0, 255));
}

QColor Plasma::getMiddleColor(QVector<QColor> points)
{
    int r = 0, g = 0, b = 0;
    for (auto i : points)
    {
        r += i.red();
        g += i.green();
        b += i.blue();
    }
    r /= points.size();
    g /= points.size();
    b /= points.size();

    return QColor(r, g, b);
}

void Plasma::addNoise(QColor &color)
{
    int r = color.red(), g = color.green(), b = color.blue();

    r = fixValue(r + getRandValue());
    g = fixValue(g + getRandValue());
    b = fixValue(b + getRandValue());

    color.setRed(r);
    color.setGreen(g);
    color.setBlue(b);
}

int Plasma::fixValue(int value)
{
    if (value < 0) return 0;
    else if (value > 255) return 255;
    return value;
}
