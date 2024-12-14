#include "surfacemodel.h"
#include <QDebug>
SurfaceModel::SurfaceModel(QVector<QVector<double>> map, QVector<QVector<QColor>> color)
{
    int n = map.size(), m = map[0].size();

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            _points.append(QVector3D(i, j, map[i][j]));

    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < m - 1; ++j) {
            _faces.append(QVector3D(i * m + j, i * m + j + 1, i * (m + 1) + j));
            _colors.append(color[i][j]);
            _faces.append(QVector3D(i * m + j + 1, i * (m + 1) + j, i * (m + 1) + j + 1));
            _colors.append(color[i + 1][j + 1]);
        }

    checkNormals();
    calcNormals();
    centralize();
}

void SurfaceModel::checkNormals() {
    for (int i = 0; i < _faces.size(); ++i) {
        QVector3D p1 = _points[_faces[i].y()] - _points[_faces[i].x()];
        QVector3D p2 = _points[_faces[i].z()] - _points[_faces[i].x()];
        QVector3D normal = QVector3D::crossProduct(p1, p2);
        QVector3D center = (_points[_faces[i].x()] + _points[_faces[i].y()] + _points[_faces[i].z()]) / 3.0;

        if (QVector3D::dotProduct(normal, center) < 0) {
            double tmp = _faces[i].y();
            _faces[i].setY(_faces[i].z());
            _faces[i].setZ(tmp);
        }
    }
}

void SurfaceModel::calcNormals() {
    _normals.resize(_points.size());

    for (int i = 0; i < _faces.size(); ++i) {
        QVector3D p1 = _points[_faces[i].y()] - _points[_faces[i].x()];
        QVector3D p2 = _points[_faces[i].z()] - _points[_faces[i].x()];
        QVector3D normal = QVector3D::crossProduct(p1, p2);
        _normals[_faces[i].x()] += normal;
        _normals[_faces[i].y()] += normal;
        _normals[_faces[i].z()] += normal;
    }

    for (auto &normal : _normals)
        if (!normal.isNull())
            normal.normalize();

}

void SurfaceModel::centralize()
{
    QVector3D center(0, 0, 0);
    for (auto &point : _points)
        center += point;
    center /= _points.size();
    for (auto &point : _points)
        point -= center;
}

void SurfaceModel::setPoints(QVector<QVector3D> points) { _points = points; }

void SurfaceModel::setFaces(QVector<QVector3D> faces) { _faces = faces; }

void SurfaceModel::setNormals(QVector<QVector3D> normals) { _normals = normals; }

void SurfaceModel::setColors(QVector<QColor> colors) { _colors = colors; }

QVector<QVector3D> SurfaceModel::getPoints() { return _points; }

QVector<QVector3D> SurfaceModel::getFaces() { return _faces; }

QVector<QVector3D> SurfaceModel::getNormals() { return _normals; }

QVector<QColor> SurfaceModel::getColors() { return _colors; }
