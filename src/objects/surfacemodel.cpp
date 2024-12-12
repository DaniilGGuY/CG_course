#include "surfacemodel.h"

SurfaceModel::SurfaceModel() : _model(nullptr) {}

SurfaceModel::SurfaceModel(const SurfaceModel &carcas) : _model(carcas._model) {}

SurfaceModel::SurfaceModel(std::shared_ptr<SurfaceStructure> model) : _model(model) {}

Point SurfaceModel::getCenter() const { return _model->getCenter(); }
