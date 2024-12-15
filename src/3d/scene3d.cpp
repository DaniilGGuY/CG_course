#include "scene3d.h"
#include <QDebug>

Scene3D::Scene3D(int width, int height, BasePlasma *plasma) : _width(width), _height(height)
{
    if (plasma) {
        _surface = SurfaceModel(plasma->getHeight(), plasma->getColors());
        _light = Light(QVector3D(-1, 0, 1), QVector3D(500, 0, 0), Qt::white);
        _render = Render(_height, _width);
    }
}

Scene3D::~Scene3D() {}

void Scene3D::draw()
{
    auto transformed_light = _light;
    transformed_light.setPos(transformPointToCamera(_light.getPos()));
    auto transformed_surface = transformModelToCamera();
    _scene = _render.renderImage(transformed_surface, transformed_light);

    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
            addLine(i, j, i, j, QPen(_scene[i][j]));
}

QVector3D Scene3D::transformPointToCamera(QVector3D point) { return _camera.getView().map(point); }

QVector<QVector3D> Scene3D::transformVectorToCamera(QVector<QVector3D> points)
{
    QMatrix4x4 transform_mat = _camera.getView();
    QVector<QVector3D> transform_points;
    for (auto &point : points)
        transform_points.append(transform_mat.map(point));
    return transform_points;
}

SurfaceModel Scene3D::transformModelToCamera()
{
    auto transformed_surface = _surface;

    QVector<QVector3D> transform_points = transformVectorToCamera(_surface.getPoints());
    QVector<QVector3D> transform_normals = transformVectorToCamera(_surface.getNormals());

    transformed_surface.setNormals(transform_normals);
    transformed_surface.setPoints(transform_points);

    return transformed_surface;
}

void Scene3D::keyPressEvent(QKeyEvent *event) {
    switch (event->key())
    {
        case Qt::Key_A:
            _camera.addXZAngle(-5);
            break;
        case Qt::Key_D:
            _camera.addXZAngle(5);
            break;
        case Qt::Key_W:
            _camera.addZYAngle(-5);
            break;
        case Qt::Key_S:
            _camera.addZYAngle(5);
            break;
        case Qt::Key_Q:
            _camera.addRadius(-100);
            break;
        case Qt::Key_E:
            _camera.addRadius(100);
            break;
        case Qt::Key_R:
            _camera.dropSettings();
            break;
        default:
            break;
    }

    draw();
}
