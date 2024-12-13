#include "scene3d.h"

Scene3D::Scene3D(int width, int height, BasePlasma *plasma) : _width(width), _height(height)
{
    if (plasma) {
        SurfaceModel surface(plasma->getHeight(), plasma->getColors());
        Light light(QVector3D(0, 0, 0));
        ZBuffer image(_height, _width);
        _colors = image.renderImage(surface, light);
    }
}

Scene3D::~Scene3D() {}

void Scene3D::draw()
{
    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
            addLine(i, j, i, j, QPen(_colors[i][j]));
}
