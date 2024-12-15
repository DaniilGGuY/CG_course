#ifndef RENDER_H
#define RENDER_H

#include <QColor>
#include <QVector>

#include "3d/objects/light/light.h"
#include "3d/objects/model/surfacemodel.h"

#define HEIGHT       512
#define WIDTH        512

class Render
{
public:
    Render();
    Render(int height, int width);

    QVector<QVector<QColor>> renderImage(SurfaceModel surface, Light light);

protected:
    void resetBuffers();
    QVector3D calcScreenPoint(QVector3D point);
    void renderFace(QVector<QVector3D> points, QVector3D face, QVector<QVector3D> normals, QColor color, Light light);
    QVector3D calcBaric(QVector2D pi, QVector3D p1, QVector3D p2, QVector3D p3);
    QColor calcPhong(QVector3D point, QVector3D normal, QColor color, Light light, QVector3D view);
    QVector3D calcNormal(QVector3D n1, QVector3D n2, QVector3D n3, QVector3D barometric);

private:
    int _height;
    int _width;
    QVector<QVector<double>> _z_buffer;
    QVector<QVector<QColor>> _image_buffer;
};

#endif // RENDER_H
