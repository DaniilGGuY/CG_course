#include "approcplasma.h"

ApprocPlasma::ApprocPlasma(int width, int height, int deflection, double alpha, QVector<QVector<int>> data)
    : BasePlasma(width, height, deflection, alpha)
{
    setHeight(data);
    if (_width != data[0].size() || _height != data.size())
        approc();
}

ApprocPlasma::~ApprocPlasma() {}

void ApprocPlasma::setHeight(QVector<QVector<int>> data)
{
    int height = data.size(), width = data[0].size();
    _data.resize(height);
    for (int i = 0; i < height; ++i) {
        _data[i].resize(width);
        for (int j = 0; j < width; ++j)
            _data[i][j] = data[i][j];
    }
}

void ApprocPlasma::approc()
{

}
