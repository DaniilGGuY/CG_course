#ifndef RENDER_H
#define RENDER_H

#include <QColor>
#include <QVector>

#include "3d/objects/light/light.h"
#include "3d/objects/model/surfacemodel.h"

class Render
{
public:
    Render() = default;
    explicit Render(int height, int width, QColor bg_color);

    QVector<QVector<QColor>> renderImage(SurfaceModel &model, Light &light);

protected:
    void resetBuffers();
    void renderTriangle(QVector<QPointF> &projs, QVector<QVector3D> &points, QVector<int> &face, QColor &color, Light &light);

    QColor calcShadow(QVector3D &normal, Light &light, QVector3D &point, QColor &baseColor);
    QVector3D calcBaric(QPointF &point, QPointF &p0, QPointF &p1, QPointF &p2);
    QVector<QPointF> calcProj(QVector<QVector3D> &points);
    QVector3D calcNormal(QVector<QVector3D> &points, QVector<int> &face);

private:
    int _height;
    int _width;
    QVector<QVector<double>> _z_buffer;
    QVector<QVector<QColor>> _image_buffer;
};

#endif // RENDER_H
