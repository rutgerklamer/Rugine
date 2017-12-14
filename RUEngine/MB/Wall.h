#ifndef WALL_H
#define WALL_H

#include "Engine/Entity.h"

class Wall : public Entity
{
public:
    Wall();
    ~Wall();

    virtual void update(float deltaTime);

private:

};

#endif
