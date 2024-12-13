#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QColor>
#include <QVector>

#include "3d/objects/light/light.h"
#include "3d/objects/model/surfacemodel.h"

class ZBuffer
{
public:
    ZBuffer(int height, int width);

    QVector<QVector<QColor>> renderImage(SurfaceModel surface, Light light);

protected:
    void resetBuffers();
    void projection(QVector<QVector3D> points);
    void renderFace(QVector<QVector3D> points, QVector3D face, QVector<QVector3D> normals, QColor color, Light light);
    QVector3D calcPoint(QVector2D pi, QVector2D p1, QVector2D p2, QVector2D p3);

private:
    int _height;
    int _width;
    QVector<QVector<double>> _z_buffer;
    QVector<QVector<QColor>> _image_buffer;
    QVector<QVector2D> _proj;
};

#endif // ZBUFFER_H
