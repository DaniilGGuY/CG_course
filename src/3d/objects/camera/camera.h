#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

#define RADIUS    1000
#define SCALE     5000
#define XZ           0
#define ZY           0

class Camera {
public:
    Camera();
    Camera(double radius, double xz, double zy);

    QMatrix4x4 getView();
    QVector3D getPos();

    double getRadius();
    double getXZAngle();
    double getZYAngle();

    void setRadius(double radius);
    void setXZAngle(double xz);
    void setZYAngle(double zy);

    void addRadius(double delta);
    void addXZAngle(double delta);
    void addZYAngle(double delta);

    void dropSettings();

private:
    double _radius;
    double _angleXZ;
    double _angleZY;
};

#endif // CAMERA_H
