#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGraphicsScene>

#include "plasma/baseplasma.h"
#include "3d/objects/camera/camera.h"
#include "3d/objects/model/surfacemodel.h"
#include "3d/render/render.h"

#define MXW   50
#define MXH   50

class Scene3D : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Scene3D(QObject *parent = 0);
    ~Scene3D();

    void loadModel(BasePlasma *plasma);

    void cameraRotateXZ(double delta);
    void cameraRotateZY(double delta);
    void cameraZoom(double delta);
    void cameraReset();
    void setLightPos(QVector3D pos);
    void setParams(int width, int height, QVector3D light_pos);
    void setInterpols(int mxw, int mxh);

    void draw();

protected:
    SurfaceModel transformModelToCamera();
    QVector3D transformPointToCamera(QVector3D point);
    QVector<QVector3D> transformVectorToCamera(QVector<QVector3D> points);

private:
    int _width;
    int _height;
    int _mxw;
    int _mxh;
    QVector<QVector<QColor>> _scene;
    SurfaceModel _model;
    Light _light;
    Camera _camera;
    Render _render;
};

#endif // SCENE3D_H
