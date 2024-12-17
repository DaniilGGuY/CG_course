#include "light.h"

Light::Light(QVector3D pos, QColor color)
    : _pos(pos), _color(color) {}

void Light::setPos(QVector3D pos) { _pos = pos; }

void Light::setColor(QColor color) { _color = color; }

QVector3D Light::getPos() { return _pos; }

QColor Light::getColor() { return _color; }
