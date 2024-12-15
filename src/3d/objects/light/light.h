#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>
#include <QColor>


class Light {
public:
    Light();
    Light(QVector3D pos, QVector3D dir, QColor color);

    QVector3D getPos();
    QColor getColor();
    QVector3D getDir();

    void setPos(QVector3D pos);
    void setColor(QColor color);
    void setDir(QVector3D dir);

private:
    QVector3D _dir;
    QVector3D _pos;
    QColor _color;
};

#endif // LIGHT_H
