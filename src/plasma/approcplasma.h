#ifndef APPROCPLASMA_H
#define APPROCPLASMA_H

#include "baseplasma.h"

enum InterpolWay {
    NEWTON = 1,
    SPLINE = 2,
    MINSQUARES = 3
};

class ApprocPlasma : public BasePlasma
{
public:
    explicit ApprocPlasma(int width = 512, int height = 512, InterpolWay interpol = SPLINE, std::string filename = "");
    ~ApprocPlasma();

protected:
    void setHeight(QVector<QVector<double>> data);
    void readPlasma();
    void approc_nw();
    void approc_squares();
    void approc_spline();

private:
    std::string _filename;
};

#endif // APPROCPLASMA_H
