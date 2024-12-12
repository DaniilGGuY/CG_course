#include "listsurfacestructure.h"

ListSurfaceStructure::ListSurfaceStructure() : _center(Point()), _points(std::vector<Point>()), _faces(std::vector<Face>()) {}

void ListSurfaceStructure::transform(std::shared_ptr<TransformAction> action)
{
    for (auto &point : _points)
        action->transform(point);

    action->transform(_center);
}

std::shared_ptr<SurfaceStructure> ListSurfaceStructure::clone() const
{
    std::shared_ptr<ListSurfaceStructure> clone_model = std::make_shared<ListSurfaceStructure>();

    clone_model->setCenter(_center);
    for (auto &it : _points)
        clone_model->addPoint(it);

    for (auto &it : _faces)
        clone_model->addFace(it);

    return clone_model;
}

void ListSurfaceStructure::addPoint(const Point &point) { _points.push_back(point); }

void ListSurfaceStructure::addFace(const Face &face) { _faces.push_back(face); }

void ListSurfaceStructure::setCenter(const Point &point) { _center = point; }

std::vector<Point> ListSurfaceStructure::getPoints() const { return _points; }

std::vector<Face> ListSurfaceStructure::getFaces() const { return _faces; }

Point ListSurfaceStructure::getCenter() const
{
    Point copy(_center);
    return copy;
}
