#include "baseplasma.h"
#include <qdatetime.h>
#include <cmath>

BasePlasma::BasePlasma(int width, int height, int deflection, double alpha)
    : _width(width), _height(height), _deflection(deflection), _alpha(alpha)
{
    _data.resize(height);
    _colors.resize(height);
    for (int i = 0; i < height; ++i) {
        _data[i].resize(width);
        _colors[i].resize(width);
        for (int j = 0; j < width; ++j) {
            _data[i][j] = MAX_DEPTH - 1;
        }
    }
}

BasePlasma::~BasePlasma() {}

QVector<QVector<int>> BasePlasma::getHeight()
{
    return _data;
}

QVector<QVector<QColor>> BasePlasma::getColors()
{
    return _colors;
}

void BasePlasma::draw()
{
    convertToMap();
    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
            addLine(i, j, i, j, QPen(_colors[i][j]));
}

QColor BasePlasma::convertValToColor(int h)
{
    if (h >= 98) return QColor(255, 255, 255);
    if (h >= 85) return QColor(148, 28, 12);
    if (h >= 70) return QColor(217, 41, 17);
    if (h >= 55) return QColor(245, 144, 29);
    if (h >= 35) return QColor(232, 252, 10);
    if (h >= 10) return QColor(54, 224, 52);
    if (h >= 0) return QColor(99, 247, 96);
    if (h >= -20) return QColor(112, 222, 255);
    if (h >= -40) return QColor(60, 139, 229);
    if (h >= -60) return QColor(53, 50, 227);
    if (h >= -100) return QColor(14, 12, 150);
    return QColor();
}

void BasePlasma::convertToMap()
{
    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
            _colors[i][j] = convertValToColor(_data[i][j]);
}
