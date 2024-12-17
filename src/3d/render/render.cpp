#include "render.h"

#include <QDebug>
#include <cmath>

Render::Render(int height, int width, QColor bg_color) : _height(height), _width(width) {
    _z_buffer.resize(_height, QVector<double>(_width, std::numeric_limits<double>::infinity()));
    _image_buffer.resize(_height, QVector<QColor>(_width, bg_color));
}

QColor Render::calcShadow(QVector3D &normal, Light &light, QVector3D &point, QColor &baseColor) {
    QVector3D lightDir = (light.getPos() - point);
    lightDir.normalize();

    double intensity = QVector3D::dotProduct(lightDir, normal);
    if (intensity < 0) intensity = -intensity;
    if (intensity > 1) intensity = 1;

    return QColor(baseColor.red()*intensity, baseColor.green()*intensity, baseColor.blue()*intensity);

}

QVector<QVector<QColor>> Render::renderImage(SurfaceModel &model, Light &light) {
    resetBuffers();

    auto projectedVertices = calcProj(model._points);

    for (int i = 0; i < model._faces.size(); ++i) {
        auto &triangle = model._faces[i];
        auto color = model._colors[i];

        renderTriangle(projectedVertices, model._points, triangle, color, light);
    }

    return _image_buffer;
}

QVector3D Render::calcNormal(QVector<QVector3D> &points, QVector<int> &face) {
    QVector3D p1 = points[face[1]] - points[face[0]];
    QVector3D p2 = points[face[2]] - points[face[0]];
    QVector3D normal = QVector3D::crossProduct(p1, p2).normalized();
    if (normal.y() < 0)
        normal *= -1;
    return normal;
}

void Render::renderTriangle(QVector<QPointF> &projs, QVector<QVector3D> &points, QVector<int> &face, QColor &color, Light &light) {
    QPointF p0 = projs[face[0]], p1 = projs[face[1]], p2 = projs[face[2]];
    double z0 = points[face[0]].z(), z1 = points[face[1]].z(), z2 = points[face[2]].z();
    QVector3D v0 = points[face[0]], v1 = points[face[1]], v2 = points[face[2]];

    int minX = std::max(0, static_cast<int>(std::floor(std::min({p0.x(), p1.x(), p2.x()}))));
    int maxX = std::min(_width - 1, static_cast<int>(std::ceil(std::max({p0.x(), p1.x(), p2.x()}))));
    int minY = std::max(0, static_cast<int>(std::floor(std::min({p0.y(), p1.y(), p2.y()}))));
    int maxY = std::min(_height - 1, static_cast<int>(std::ceil(std::max({p0.y(), p1.y(), p2.y()}))));
    //qDebug() << face;
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            QPointF point(x, y);

            QVector3D baric = calcBaric(point, p0, p1, p2);
            if (baric.x() < 0 || baric.y() < 0 || baric.z() < 0) continue;

            double z = baric.x() * z0 + baric.y() * z1 + baric.z() * z2;

            QVector3D normal = calcNormal(points, face);
            QVector3D worldPoint = baric.x() * v0 + baric.y() * v1 + baric.z() * v2;
            QColor pix_color = calcShadow(normal, light, worldPoint, color);

            if (z < _z_buffer[y][x]) {
                _z_buffer[y][x] = z;
                _image_buffer[y][x] = pix_color;
            }
        }
    }
}

QVector3D Render::calcBaric(QPointF &point, QPointF &p0, QPointF &p1, QPointF &p2) {
    double denom = (p1.y() - p2.y()) * (p0.x() - p2.x()) + (p2.x() - p1.x()) * (p0.y() - p2.y());
    double alpha = ((p1.y() - p2.y()) * (point.x() - p2.x()) + (p2.x() - p1.x()) * (point.y() - p2.y())) / denom;
    double beta = ((p2.y() - p0.y()) * (point.x() - p2.x()) + (p0.x() - p2.x()) * (point.y() - p2.y())) / denom;
    double gamma = 1.0 - alpha - beta;
    return QVector3D(alpha, beta, gamma);
}

QVector<QPointF> Render::calcProj(QVector<QVector3D> &points) {
    QVector<QPointF> projs;
    double perspective = 1000;
    for (const auto &point : points) {
        double scale = perspective / (perspective + point.z());
        double x = _width / 2 + point.x() * scale;
        double y = _height / 2 + point.y() * scale;
        projs.append(QPointF(x, y));
    }
    return projs;
}

void Render::resetBuffers() {
    for (auto &row : _z_buffer)
        std::fill(row.begin(), row.end(), std::numeric_limits<double>::infinity());
    for (auto &row : _image_buffer)
        std::fill(row.begin(), row.end(), Qt::black);
}
