#include "light.h"

Light::Light(QVector3D pos, QColor color, double intense) : _pos(pos), _color(color), _intense(intense) {}

QVector3D Light::getPos() { return _pos; }

QColor Light::getColor() { return _color; }

double Light::getIntense() { return _intense; }

void Light::setPos(QVector3D pos) { _pos = pos; }

void Light::setColor(QColor color) { _color = color; }

void Light::setIntense(double intense) { _intense = intense; }
