#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>
#include <QColor>


class Light {
public:
    Light();
    Light(QVector3D pos, QColor color, double intense);

    QVector3D getPos();
    QColor getColor();
    double getIntense();

    void setPos(QVector3D pos);
    void setColor(QColor color);
    void setIntense(double intense);

private:
    QVector3D _pos;
    QColor _color;
    double _intense;
};

#endif // LIGHT_H
