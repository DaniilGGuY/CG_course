#ifndef BASE_PLASMA_H
#define BASE_PLASMA_H

#include <QGraphicsScene>
#include <string>
#include <fstream>

#define MAX_DEPTH        -100
#define MAX_HEIGHT        100

class BasePlasma : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit BasePlasma(int width = 512, int height = 512);
    virtual ~BasePlasma() = 0;

    virtual QVector<QVector<double>> getHeight();
    virtual QVector<QVector<QColor>> getColors();

    virtual void draw();

    virtual void savePlasma(std::string filename);

protected:
    virtual void convertToMap();
    virtual QColor convertValToColor(int h);

protected:
    int _width;
    int _height;
    QVector<QVector<QColor>> _colors;
    QVector<QVector<double>> _data;
};

#endif // BASE_PLASMA_H
