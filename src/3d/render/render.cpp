#include "render.h"

#include <QDebug>

Render::Render(int height, int width, QColor bg_color) : _height(height), _width(width) {
    _z_buffer.resize(_height, QVector<double>(_width, std::numeric_limits<double>::infinity()));
    _image_buffer.resize(_height, QVector<QColor>(_width, bg_color));
}

QColor Render::calcShadow(QVector3D &normal, Light &light, QVector3D &point, QColor &baseColor) {
    QVector3D lightDir = (light.getPos() - point);
    lightDir.normalize();

    double intensity = QVector3D::dotProduct(lightDir, normal);
    intensity = intensity > 1 ? 1 : intensity;
    if (intensity > 0)
        return QColor(baseColor.red()*intensity, baseColor.green()*intensity, baseColor.blue()*intensity);
    qDebug() << point << lightDir << normal;
    return Qt::black;
}

QVector<QVector<QColor>> Render::renderImage(SurfaceModel &model, Light &light) {
    resetBuffers();

    auto projectedVertices = calcProj(model._points);

    for (int i = 0; i < model._faces.size(); ++i) {
        auto &triangle = model._faces[i];
        auto &normals = model._normals;
        auto color = model._colors[i];

        renderTriangle(projectedVertices, model._points, normals, triangle, color, light);
    }

    return _image_buffer;
}

QVector3D Render::calcNormals(QVector3D n0, QVector3D n1, QVector3D n2, double alpha, double beta, double gamma) {
    QVector3D result;
    result.setX(n0.x() * alpha + n1.x() * beta + n2.x() * gamma);
    result.setY(n0.y() * alpha + n1.y() * beta + n2.y() * gamma);
    result.setZ(n0.z() * alpha + n1.z() * beta + n2.z() * gamma);

    return result;
}

void Render::renderTriangle(QVector<QPointF> &projs, QVector<QVector3D> &points, QVector<QVector3D> &normals, QVector<int> &face,
                            QColor &color, Light &light) {
    QPointF p0 = projs[face[0]], p1 = projs[face[1]], p2 = projs[face[2]];
    QVector3D n0 = normals[face[0]], n1 = normals[face[1]], n2 = normals[face[2]];
    double z0 = points[face[0]].z(), z1 = points[face[1]].z(), z2 = points[face[2]].z();
    QVector3D v0 = points[face[0]], v1 = points[face[1]], v2 = points[face[2]];

    if ((p1.y() - p2.y()) * (p0.x() - p2.x()) + (p2.x() - p1.x()) * (p0.y() - p2.y()) < 1e-6) return;

    int minX = std::max(0, static_cast<int>(std::floor(std::min({p0.x(), p1.x(), p2.x()}))));
    int maxX = std::min(_width - 1, static_cast<int>(std::ceil(std::max({p0.x(), p1.x(), p2.x()}))));
    int minY = std::max(0, static_cast<int>(std::floor(std::min({p0.y(), p1.y(), p2.y()}))));
    int maxY = std::min(_height - 1, static_cast<int>(std::ceil(std::max({p0.y(), p1.y(), p2.y()}))));

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            QPointF point(x + 0.5, y + 0.5);

            QVector3D baric = calcBaric(point, p0, p1, p2);
            if (baric.x() < 0 || baric.y() < 0 || baric.z() < 0) continue;

            double z = baric.x() * z0 + baric.y() * z1 + baric.z() * z2;

            QVector3D normal = calcNormals(n0, n1, n2, baric.x(), baric.y(), baric.z());
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
