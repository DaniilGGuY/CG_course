#include "scene3d.h"
#include <QElapsedTimer>

Scene3D::Scene3D(QObject *parent) : QGraphicsScene(parent) { }

Scene3D::~Scene3D() {}

void Scene3D::setParams(int width, int height, QVector3D light_pos)
{
    _width = width;
    _height = height;
    _mxw = MXW;
    _mxh = MXH;
    _camera = Camera();
    _light = Light(light_pos, Qt::white);
    _render = Render(_height, _width, Qt::black);
}

void Scene3D::setInterpols(int mxw, int mxh)
{
    _mxw = mxw;
    _mxh = mxh;
}

void Scene3D::loadModel(BasePlasma *plasma) { _model = SurfaceModel::formModel(plasma->getHeight(), plasma->getColors(), _mxw, _mxh); }

void Scene3D::cameraRotateXZ(double delta) { _camera.addXZ(delta); }

void Scene3D::cameraRotateZY(double delta) { _camera.addZY(delta); }

void Scene3D::cameraZoom(double delta) { _camera.addRadius(delta); }

void Scene3D::cameraReset() { _camera.reset(); }

void Scene3D::setLightPos(QVector3D pos) { _light.setPos(pos); }

void Scene3D::draw()
{
    Light transformedLight = _light;
    transformedLight.setPos(transformPointToCamera(_light.getPos()));
    auto tranformedModel = transformModelToCamera();
    auto renderedImage = _render.renderImage(tranformedModel, transformedLight);
    /*QElapsedTimer t;
    t.start();
    for (int i = 0; i < 100; ++i)
        auto ri = _render.renderImage(tranformedModel, transformedLight);
    qint64 time = t.elapsed();
    qDebug() << time / 100 << "ms";*/

    clear();
    for (int i = 0; i < _width; ++i)
        for (int j = 0; j < _height; ++j)
            addLine(i, j, i, j, QPen(renderedImage[_height - 1 - j][_width - 1 - i]));
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
    auto transformed_surface = _model;
    QVector<QVector3D> transform_points = transformVectorToCamera(_model._points);
    transformed_surface._points = transform_points;
    return transformed_surface;
}
