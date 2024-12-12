#ifndef SURFACESTRUCTURE_H
#define SURFACESTRUCTURE_H

#include <vector>
#include <memory>

#include "transform/transformaction.h"
#include "objects/point.h"
#include "objects/face.h"

class SurfaceStructure
{
public:
    SurfaceStructure() = default;
    SurfaceStructure(const SurfaceStructure &carcas) = delete;
    SurfaceStructure(SurfaceStructure &&carcas) = delete;
    virtual ~SurfaceStructure() = 0;

    virtual void transform(std::shared_ptr<TransformAction> action) = 0;
    virtual std::shared_ptr<SurfaceStructure> clone() const = 0;

    virtual void addPoint(const Point &point) = 0;
    virtual void addFace(const Face &edge) = 0;
    virtual void setCenter(const Point &point) = 0;

    virtual std::vector<Point> getPoints() const = 0;
    virtual std::vector<Face> getFaces() const = 0;
    virtual Point getCenter() const = 0;
};

#endif // SURFACESTRUCTURE_H
