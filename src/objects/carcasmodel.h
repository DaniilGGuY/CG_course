#ifndef CARCASMODEL_H
#define CARCASMODEL_H

#include "basemodel.h"
#include "structures/carcasstructure.h"

class CarcasModel : public BaseModel
{
public:
    CarcasModel();
    explicit CarcasModel(const CarcasModel &carcas);
    explicit CarcasModel(std::shared_ptr<CarcasStructure> model);
    ~CarcasModel() = default;

    Point getCenter() const override;

private:
    std::shared_ptr<CarcasStructure> _model;
};

#endif // CARCASMODEL_H
