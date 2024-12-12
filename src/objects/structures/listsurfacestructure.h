#ifndef LISTSURFACESTRUCTURE_H
#define LISTSURFACESTRUCTURE_H

#include "surfacestructure.h"

class ListSurfaceStructure : public SurfaceStructure
{
public:
    ListSurfaceStructure();
    ~ListSurfaceStructure() = default;

    void transform(std::shared_ptr<TransformAction> action) override;
    std::shared_ptr<SurfaceStructure> clone() const override;

    void addPoint(const Point &point) override;
    void addFace(const Face &edge) override;
    void setCenter(const Point &point) override;

    std::vector<Point> getPoints() const override;
    std::vector<Face> getFaces() const override;
    Point getCenter() const override;

private:
    Point _center;
    std::vector<Point> _points;
    std::vector<Face> _faces;
};

#endif // LISTSURFACESTRUCTURE_H
