#ifndef PLASMA_H
#define PLASMA_H

#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QDateTime>

class Plasma : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Plasma(QObject *parent = 0, int width = 512, int height = 512, int deflection = 40);
    ~Plasma();

    void buildPlasma(int x1, int y1, int x2, int y2);
    void drawPlasma();

protected:
    int getRandValue();
    QColor getRandColor();
    QColor getMiddleColor(QVector<QColor> points);
    void addNoise(QColor &color);
    int fixValue(int value);

private:
    int _width;
    int _height;
    int _deflection;
    QVector<QVector<QColor>> _data;
    QRandomGenerator _rand;
};

#endif // PLASMA_H
