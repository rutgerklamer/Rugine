#ifndef BULLET_H
#define BULLET_H

#include "Engine/Entity.h"

class Bullet : public Entity
{
public:
    Bullet(glm::vec3 direction);
    ~Bullet();

    virtual void update(float deltaTime);
    void mirrorDirX();
    void mirrorDirY();
private:
    glm::vec3 dir;

};

#endif
