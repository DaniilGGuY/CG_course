#ifndef SURFACEMODEL_H
#define SURFACEMODEL_H

#include <QColor>
#include <QVector>
#include <QVector3D>

class SurfaceModel {
public:
    SurfaceModel() = default;
    SurfaceModel(QVector<QVector<double>> map, QVector<QVector<QColor>> color);

    void checkOrientation();
    void calcNormals();
    void centralize();

    void setPoints(QVector<QVector3D> points);
    void setFaces(QVector<QVector3D> faces);
    void setNormals(QVector<QVector3D> normals);
    void setColors(QVector<QColor> colors);

    QVector<QVector3D> getPoints();
    QVector<QVector3D> getFaces();
    QVector<QVector3D> getNormals();
    QVector<QColor> getColors();

private:
    QVector<QVector3D> _points;
    QVector<QVector3D> _faces;
    QVector<QVector3D> _normals;
    QVector<QColor> _colors;
};

#endif // SURFACEMODEL_H
