#ifndef SURFACEMODEL_H
#define SURFACEMODEL_H

#include <QColor>
#include <QVector>
#include <QVector3D>

#define MXW    50
#define MXH   50

class SurfaceModel {
public:
    QVector<QVector3D> _normals;
    QVector<QVector3D> _points;
    QVector<QVector<int>> _faces;
    QVector<QColor> _colors;

    static SurfaceModel formModel(QVector<QVector<double>> map, QVector<QVector<QColor>> colors);
private:
    void checkNormals();
    void calcNormals();
    void centralizeModel();
};

#endif // SURFACEMODEL_H
