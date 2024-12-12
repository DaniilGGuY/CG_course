#ifndef BASEMODEL_H
#define BASEMODEL_H

#include "visibleobject.h"

class BaseModel : public VisibleObject
{
public:
    BaseModel();
    virtual ~BaseModel() = 0;

    virtual iterator begin();
    virtual iterator end();

    virtual void add(std::shared_ptr<Object> obj);
    virtual void remove(const iterator &it);

    virtual std::shared_ptr<Object> clone() const;
};

#endif // BASEMODEL_H
