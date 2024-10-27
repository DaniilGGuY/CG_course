#ifndef BASE_PLASMA_H
#define BASE_PLASMA_H

#include <QGraphicsScene>

#define MAX_DEPTH        -100
#define MAX_HEIGHT        100

class BasePlasma : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit BasePlasma(int width = 512, int height = 512, int deflection = 30, double alpha = 2);
    virtual ~BasePlasma() = 0;

    virtual QVector<QVector<int>> getHeight();
    virtual QVector<QVector<QColor>> getColors();

    virtual void draw();

protected:
    virtual void convertToMap();
    virtual QColor convertValToColor(int h);

protected:
    int _width;
    int _height;
    int _deflection;
    double _alpha;
    QVector<QVector<QColor>> _colors;
    QVector<QVector<int>> _data;
};

#endif // BASE_PLASMA_H
