#include "zbuffer.h"
#include <QDebug>

ZBuffer::ZBuffer(int height, int width) : _height(height), _width(width)
{
    _z_buffer.resize(_height, QVector<double>(_width, 1e8));
    _image_buffer.resize(_height, QVector<QColor>(_width, Qt::black));
}

QVector<QVector<QColor>> ZBuffer::renderImage(SurfaceModel surface, Light light)
{
    resetBuffers();

    QVector<QVector3D> points = surface.getPoints();
    QVector<QVector3D> faces = surface.getFaces();
    QVector<QVector3D> normals = surface.getNormals();
    QVector<QColor> colors = surface.getColors();

    projection(points);
    for (int i = 0; i < faces.size(); ++i)
    {
        QVector3D face = faces[i];
        QColor color = colors[i];
        renderFace(points, face, normals, color, light);
    }

    return _image_buffer;
}

void ZBuffer::resetBuffers() {
    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
        {
            _z_buffer[i][j] = 1e8;
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
    QVector3D p1 = points[face.x()], p2 = points[face.y()], p3 = points[face.z()];
    double z1 = p1.z(), z2 = p2.z(), z3 = p3.z();
    if (QVector2D::dotProduct((proj2 - proj1), (proj2 - proj3)) == 0) return;

    int min_x = std::max(int(floor(std::min({proj1.x(), proj2.x(), proj3.x()}))), 0);
    int min_y = std::max(int(floor(std::min({proj1.y(), proj2.y(), proj3.y()}))), 0);
    int max_x = std::min(int(ceil(std::max({proj1.x(), proj2.x(), proj3.x()}))), _width - 1);
    int max_y = std::min(int(ceil(std::max({proj1.y(), proj2.y(), proj3.y()}))), _height - 1);
    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            QVector2D point(x + 0.5, y + 0.5);

            QVector3D baric = calcPoint(point, proj1, proj2, proj3);
            if (baric.x() < 0 || baric.y() < 0 || baric.z() < 0) continue;

            double z = baric.x() * z1 + baric.y() * z2 + baric.z() * z3;
            QVector3D normal = calcNormal(n1, n2, n3, baric);
            QVector3D world_point = baric.x() * p1 + baric.y() * p2 + baric.z() * p3;
            QVector3D view = -world_point.normalized();
            QColor pixel = calcPhong(world_point, normal, color, light, view);
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

QColor ZBuffer::calcPhong(QVector3D point, QVector3D normal, QColor color, Light light, QVector3D view)
{
    QVector3D light_vec = (light.getPos() - point).normalized();
    QVector3D reflect_vec = (2.0 * QVector3D::dotProduct(normal, light_vec) * normal - light_vec).normalized();
    double ambientStrength = 0.3;
    QColor ambient = QColor(color.red() * ambientStrength * light.getColor().red(),
                            color.green() * ambientStrength * light.getColor().green(),
                            color.blue() * ambientStrength * light.getColor().blue());

    double diffuseStrength = std::pow(std::max(QVector3D::dotProduct(normal, light_vec), 0.2f), 0.7);
    QColor diffuse = QColor(color.red() * diffuseStrength * light.getIntense() * light.getColor().red(),
                            color.green() * diffuseStrength * light.getIntense() * light.getColor().green(),
                            color.blue() * diffuseStrength * light.getIntense() * light.getColor().blue());

    double specularStrength = 0.0;
    double spec = std::pow(std::max(QVector3D::dotProduct(view, reflect_vec), 0.0f), 32.0);
    QColor specular = QColor(255 * spec * light.getIntense() * specularStrength * light.getColor().red(),
                             255 * spec * light.getIntense() * specularStrength * light.getColor().green(),
                             255 * spec * light.getIntense() * specularStrength * light.getColor().blue());

    int r = std::min(ambient.red() + diffuse.red() + specular.red(), 255);
    int g = std::min(ambient.green() + diffuse.green() + specular.green(), 255);
    int b = std::min(ambient.blue() + diffuse.blue() + specular.blue(), 255);

    return QColor(r, g, b);
}

QVector3D ZBuffer::calcNormal(QVector3D n1, QVector3D n2, QVector3D n3, QVector3D barometric)
{
    QVector3D normal;
    normal.setX(n1.x() * barometric.x() + n2.x() * barometric.y() + n3.x() * barometric.z());
    normal.setY(n1.y() * barometric.x() + n2.y() * barometric.y() + n3.y() * barometric.z());
    normal.setZ(n1.z() * barometric.x() + n2.z() * barometric.y() + n3.z() * barometric.z());
    return normal;
}

