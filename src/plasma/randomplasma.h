#ifndef RANDOMPLASMA_H
#define RANDOMPLASMA_H

#include <QRandomGenerator>
#include <QDateTime>

#include "baseplasma.h"

class RandomPlasma : public BasePlasma
{
public:
    explicit RandomPlasma(int width = 512, int height = 512, int deflection = 30, double alpha = 2);
    ~RandomPlasma();

protected:
    void build(int x1, int y1, int x2, int y2);
    int getRandValue();
    int getMiddleVal(QVector<double> points);
    int fixValue(int value);

private:
    int _deflection;
    double _alpha;
    QRandomGenerator _rand;
};

#endif // RANDOMPLASMA_H
