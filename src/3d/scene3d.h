#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGraphicsScene>
#include <QKeyEvent>

#include "plasma/baseplasma.h"
#include "3d/objects/camera/camera.h"
#include "3d/objects/model/surfacemodel.h"
#include "3d/render/zbuffer.h"

class Scene3D : public QGraphicsScene
{
public:
    explicit Scene3D(int width = 512, int height = 512, BasePlasma *plasma = NULL);
    ~Scene3D();

    void draw();

protected:
    SurfaceModel transformModelToCamera();
    QVector3D transformPointToCamera(QVector3D point);
    QVector<QVector3D> transformVectorToCamera(QVector<QVector3D> points);
    void keyPressEvent(QKeyEvent *event) override;

private:
    int _width;
    int _height;
    QVector<QVector<QColor>> _colors;
    SurfaceModel _surface;
    Camera _camera;
    Light _light;
    ZBuffer _render;
};

#endif // SCENE3D_H
