#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>
#include "Engine/Entity.h"
#include <glm/gtx/rotate_vector.hpp>

class Collision
{
    public:
        Collision();
        virtual ~Collision();
        static bool intersectAABB(Entity* e1, Entity* e2);
    private:
};

#endif // TIME_H
