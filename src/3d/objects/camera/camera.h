#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

class Camera {
public:
    Camera();

    QMatrix4x4 getView();

    void reset();

    void addXZ(double delta);
    void addZY(double delta);
    void addRadius(double delta);

private:
    double _radius;
    double _angleXZ;
    double _angleZY;
};

#endif // CAMERA_H
