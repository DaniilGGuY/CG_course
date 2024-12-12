#ifndef SURFACEMODEL_H
#define SURFACEMODEL_H

#include "basemodel.h"
#include "structures/surfacestructure.h"

class SurfaceModel : public BaseModel
{
public:
    SurfaceModel();
    explicit SurfaceModel(const SurfaceModel &carcas);
    explicit SurfaceModel(std::shared_ptr<SurfaceStructure> model);
    ~SurfaceModel() = default;

    Point getCenter() const override;

private:
    std::shared_ptr<SurfaceStructure> _model;
};

#endif // SURFACEMODEL_H
