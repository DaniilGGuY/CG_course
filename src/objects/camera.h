#ifndef CAMERA_H
#define CAMERA_H

#include "invisibleobject.h"
#include "transform/cameraaction.h"

class Camera : public InvisibleObject
{
    friend class CameraAction;
public:
    Camera();
    Camera(double x, double y, double z);
    explicit Camera(const Point &point);
    explicit Camera(const Camera &camera);
    virtual ~Camera() = default;

    virtual Point getCenter() const override;
    virtual bool isComposite() const override;

protected:
    Point _self;
    Point _normalForward;
    Point _normalUp;
    Point _normalRight;
};

#endif // CAMERA_H
