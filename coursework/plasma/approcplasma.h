#ifndef APPROCPLASMA_H
#define APPROCPLASMA_H

#include "baseplasma.h"

class ApprocPlasma : public BasePlasma
{
public:
    explicit ApprocPlasma(int width = 512, int height = 512, int deflection = 30, double alpha = 2,
                         QVector<QVector<int>> data = QVector<QVector<int>>(0, QVector<int>(0)));
    ~ApprocPlasma();

    void setHeight(QVector<QVector<int>> data);

protected:
    void approc();

private:

};

#endif // APPROCPLASMA_H
