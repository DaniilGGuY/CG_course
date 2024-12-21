#include "surfacemodel.h"
#include <QDebug>

SurfaceModel SurfaceModel::formModel(QVector<QVector<double>> map, QVector<QVector<QColor>> colors, int mxw, int mxh, bool monotic) {
    SurfaceModel model;

    int n = map.size(), m = map[0].size();

    int stepi = n / mxw, stepj =  m / mxh;
    QColor base = QColor(6, 125, 18);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            model._points.append(QVector3D(i * 1.0, map[i][j], j * 1.0));

    for (int i = 0; i < n - stepi; i += stepi)
        for (int j = 0; j < m - stepj; j += stepj) {
            model._faces.append({i * m + j, i * m + j + stepj, (i + stepi) * m + j});
            model._faces.append({i * m + j + stepj, (i + stepi) * m + j, (i + stepi) * m + j + stepj});
            if (monotic) {
                model._colors.append(base);
                model._colors.append(base);
            }
            else {
                model._colors.append(colors[i][j]);
                model._colors.append(colors[i + stepi][j + stepj]);
            }
        }

    model.centralizeModel();

    return model;
}

void SurfaceModel::centralizeModel() {
    QVector3D center(0, 0, 0);
    for (auto &vertex : _points)
        center += vertex;
    center /= _points.size();
    for (auto &vertex : _points)
        vertex -= center;
}
