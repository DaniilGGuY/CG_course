#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGraphicsScene>

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

private:
    int _width;
    int _height;
    QVector<QVector<QColor>> _colors;
};

#endif // SCENE3D_H
