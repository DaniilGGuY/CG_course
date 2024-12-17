#include "camera.h"
#include <cmath>

Camera::Camera()
    : _radius(5000.0),
    _angleXZ(-45),
    _angleZY(-45) {}

QMatrix4x4 Camera::getView()
{
    double radXZ = qDegreesToRadians(_angleXZ);
    double radZY = qDegreesToRadians(_angleZY);

    QMatrix4x4 rotZY(1, 0                 , 0                , 0,
                     0, (float)cos(radZY) , (float)sin(radZY), 0,
                     0, (float)-sin(radZY), (float)cos(radZY), 0,
                     0, 0                 , 0                , 1);

    QMatrix4x4 rotXZ((float)cos(radXZ) , 0, (float)sin(radXZ), 0,
                     0                 , 1, 0                , 0,
                     (float)-sin(radXZ), 0, (float)cos(radXZ), 0,
                     0                 , 0, 0                , 1);

    QMatrix4x4 scale((float)(5000 / _radius), 0, 0, 0,
                     0, (float)(5000 / _radius), 0, 0,
                     0, 0, (float)(5000 / _radius), 0,
                     0, 0, 0                      , 1);

    return scale * rotZY * rotXZ;
}

void Camera::reset() {
    _angleXZ = -45;
    _angleZY = -45;
    _radius = 5000;
}

void Camera::addXZ(double delta) {
    _angleXZ += delta;
}

void Camera::addZY(double delta) {
    _angleZY += delta;
}

void Camera::addRadius(double delta) {
    _radius += delta;
}
