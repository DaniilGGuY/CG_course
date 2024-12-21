#ifndef SURFACEMODEL_H
#define SURFACEMODEL_H

#include <QColor>
#include <QVector>
#include <QVector3D>

class SurfaceModel {
public:
    QVector<QVector3D> _points;
    QVector<QVector<int>> _faces;
    QVector<QColor> _colors;

    static SurfaceModel formModel(QVector<QVector<double>> map, QVector<QVector<QColor>> colors, int mxw, int mxh, bool monotic);
private:
    void centralizeModel();
};

#endif // SURFACEMODEL_H
