#include "camera.h"

Camera::Camera() : _radius(RADIUS), _angleXZ(XZ), _angleZY(ZY) {}

Camera::Camera(double radius, double xz, double zy) : _radius(radius), _angleXZ(xz), _angleZY(zy) {}

QMatrix4x4 Camera::getView()
{
    double xz_rad = qDegreesToRadians(_angleXZ), zy_rad = qDegreesToRadians(_angleZY);

    QMatrix4x4 scale(
        SCALE / _radius, 0, 0, 0,
        0, SCALE / _radius, 0, 0,
        0, 0, SCALE / _radius, 0,
        0, 0, 0              , 1);

    QMatrix4x4 zy_rot(
        1, 0           , 0          , 0,
        0, cos(zy_rad) , sin(zy_rad), 0,
        0, -sin(zy_rad), cos(zy_rad), 0,
        0, 0           , 0          , 1);

    QMatrix4x4 xz_rot(
        cos(xz_rad) , 0, sin(xz_rad), 0,
        0           , 1, 0          , 0,
        -sin(xz_rad), 0, cos(xz_rad), 0,
        0           , 0, 0          , 1);

    return scale * zy_rot * xz_rot;
}

QVector3D Camera::getPos()
{
    double xz_rad = qDegreesToRadians(_angleXZ), zy_rad = qDegreesToRadians(_angleZY);
    double x = _radius * cos(zy_rad) * sin(xz_rad);
    double y = _radius * sin(zy_rad);
    double z = _radius * cos(zy_rad) * cos(xz_rad);
    return QVector3D(x, y, z);
}

double Camera::getRadius() { return _radius; }

double Camera::getXZAngle() { return _angleXZ; }

double Camera::getZYAngle() { return _angleZY; }

void Camera::setRadius(double radius) { _radius = radius; }

void Camera::setXZAngle(double xz) { _angleXZ = xz; }

void Camera::setZYAngle(double zy) { _angleZY = zy; }

void Camera::addRadius(double delta) { _radius += delta; }

void Camera::addXZAngle(double delta) { _angleXZ += delta; }

void Camera::addZYAngle(double delta) { _angleZY += delta; }

void Camera::dropSettings()
{
    _radius = RADIUS;
    _angleXZ = XZ;
    _angleZY = ZY;
}
