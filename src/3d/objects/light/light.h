#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>
#include <QColor>

class Light {
public:
    Light(QVector3D pos = {10000, 10000, 0}, QColor color = Qt::white);

    void setPos(QVector3D pos);
    void setColor(QColor color);

    QVector3D getPos();
    QColor getColor();

private:
    QVector3D _pos;
    QColor _color;
};

#endif // LIGHT_H
