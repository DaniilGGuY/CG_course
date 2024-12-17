#include "surfacemodel.h"
#include <QDebug>

SurfaceModel SurfaceModel::formModel(QVector<QVector<double>> map, QVector<QVector<QColor>> colors) {
    SurfaceModel model;

    int n = map.size(), m = map[0].size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            model._points.append(QVector3D(j, map[i][j], i));

    int stepi = 1, stepj = 1;

    for (int i = 0; i < n - stepi; i += stepi)
        for (int j = 0; j < m - stepj; j += stepj) {
            model._faces.append({i * m + j, i * m + j + stepj, (i + stepi) * m + j});
            model._colors.append(colors[i][j]);
            model._faces.append({i * m + j + stepj, (i + stepi) * m + j, (i + stepi) * m + j + stepj});
            model._colors.append(colors[i + stepi][j + stepj]);
        }

    model.centralizeModel();
    model.checkNormals();
    model.calcNormals();

    return model;
}

void SurfaceModel::checkNormals() {
    for (auto &face : _faces) {
        QVector3D p1 = _points[face[1]] - _points[face[0]];
        QVector3D p2 = _points[face[2]] - _points[face[0]];
        QVector3D normal = QVector3D::crossProduct(p1, p2).normalized();
        QVector3D center = ((_points[face[0]] + _points[face[1]] + _points[face[2]]) / 3.0).normalized();
        if (QVector3D::dotProduct(normal, center) < 0)
            std::swap(face[1], face[2]);
    }
}

void SurfaceModel::calcNormals() {
    _normals.resize(_points.size());
    for (auto &face : _faces) {
        QVector3D p1 = _points[face[1]] - _points[face[0]];
        QVector3D p2 = _points[face[2]] - _points[face[0]];
        QVector3D normal = QVector3D::crossProduct(p1, p2).normalized();
        if (normal.y() < 0)
            normal *= -1;

        _normals[face[0]] = normal;
        _normals[face[1]] = normal;
        _normals[face[2]] = normal;
    }
}

void SurfaceModel::centralizeModel() {
    QVector3D center(0, 0, 0);
    for (auto &vertex : _points)
        center += vertex;
    center /= _points.size();
    for (auto &vertex : _points)
        vertex -= center;
}
