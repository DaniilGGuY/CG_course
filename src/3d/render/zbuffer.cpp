#include "zbuffer.h"

ZBuffer::ZBuffer(int height, int width) : _height(height), _width(width)
{
    _z_buffer.resize(_height, QVector<double>(_width, std::numeric_limits<double>::infinity()));
    _image_buffer.resize(_height, QVector<QColor>(_width, Qt::black));
}

QVector<QVector<QColor>> ZBuffer::renderImage(SurfaceModel surface, Light light)
{
    resetBuffers();

    QVector<QVector3D> points = surface.getPoints();
    QVector<QVector3D> faces = surface.getFaces();
    QVector<QVector3D> normals = surface.getNormals();
    QVector<QColor> colors = surface.getColors();

    projection(surface.getPoints());
    for (int i = 0; i < faces.size(); ++i)
    {
        QVector3D face = faces[i];
        QColor color = colors[i];
    }

    return _image_buffer;
}

void ZBuffer::resetBuffers() {
    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
        {
            _z_buffer[i][j] = std::numeric_limits<double>::infinity();
            _image_buffer[i][j] = Qt::black;
        }
}

void ZBuffer::projection(QVector<QVector3D> points)
{
    double perspective = 1000;
    for (auto &point : points) {
        double scale = perspective / (perspective + point.z());
        double x = _width / 2 + point.x() * scale;
        double y = _height / 2 + point.y() * scale;

        _proj.append(QVector2D(x, y));
    }
}

void ZBuffer::renderFace(QVector<QVector3D> points, QVector3D face, QVector<QVector3D> normals, QColor color, Light light)
{
    QVector2D proj1 = _proj[face.x()], proj2 = _proj[face.y()], proj3 = _proj[face.z()];
    QVector3D n1 = normals[face.x()], n2 = normals[face.y()], n3 = normals[face.z()];
    double z1 = points[face.x()].z(), z2 = points[face.y()].z(), z3 = points[face.z()].z();
    QVector3D p1 = points[face.x()], p2 = points[face.y()], p3 = points[face.z()];

    if ((proj2.y() - proj3.y()) * (proj1.x() - proj3.x()) + (proj3.x() - proj2.x()) * (proj1.y() - proj3.y())) return;

    int min_x = std::max(int(std::min({proj1.x(), proj2.x(), proj3.x()})), 0);
    int min_y = std::max(int(std::min({proj1.y(), proj2.y(), proj3.y()})), 0);
    int max_x = std::min(int(std::max({proj1.x(), proj2.x(), proj3.x()})), _width - 1);
    int max_y = std::min(int(std::max({proj1.y(), proj2.y(), proj3.y()})), _height - 1);

    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            QVector2D point(x + 0.5, y + 0.5);

            QVector3D baric = calcPoint(point, proj1, proj2, proj3);
            if (baric.x() < 0 || baric.y() < 0 || baric.z() < 0) continue;

            double z = baric.x() * z1 + baric.y() * z2 + baric.z() * z3;

            QColor pixel = color;
            /*if (light.isEnable) {
                QVector3D normal = interpolate_normals(n0, n1, n2, alpha, beta, gamma);
                QVector3D worldPoint = alpha * v0 + beta * v1 + gamma * v2;
                QVector3D viewDir = -worldPoint.normalized();
                pixelColor = computePhongShading(normal, viewDir, light, worldPoint, baseColor);
            } else {
                pixelColor = baseColor;
            }*/

            if (z < _z_buffer[y][x]) {
                _z_buffer[y][x] = z;
                _image_buffer[y][x] = pixel;
            }
        }
    }
}

QVector3D ZBuffer::calcPoint(QVector2D pi, QVector2D p1, QVector2D p2, QVector2D p3) {
    double denom = (p2.y() - p3.y()) * (p1.x() - p3.x()) + (p3.x() - p2.x()) * (p1.y() - p3.y());
    double alpha = ((p2.y() - p3.y()) * (pi.x() - p3.x()) + (p3.x() - p2.x()) * (pi.y() - p3.y())) / denom;
    double beta = ((p3.y() - p1.y()) * (pi.x() - p3.x()) + (p1.x() - p3.x()) * (pi.y() - p3.y())) / denom;
    double gamma = 1.0 - alpha - beta;
    return QVector3D(alpha, beta, gamma);
}
