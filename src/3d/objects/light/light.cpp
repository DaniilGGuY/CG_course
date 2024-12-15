#include "light.h"

Light::Light() : _dir({1, 1, 1}), _pos({0, 0, 0}), _color(Qt::white) {}

Light::Light(QVector3D dir, QVector3D pos, QColor color) : _dir(dir), _pos(pos), _color(color) {}

QVector3D Light::getPos() { return _pos; }

QColor Light::getColor() { return _color; }

QVector3D Light::getDir() { return _dir; }

void Light::setPos(QVector3D pos) { _pos = pos; }

void Light::setColor(QColor color) { _color = color; }

void Light::setDir(QVector3D dir) { _dir = dir; }
