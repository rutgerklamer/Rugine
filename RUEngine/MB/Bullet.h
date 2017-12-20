#ifndef BULLET_H
#define BULLET_H

#include "Engine/Entity.h"
#include "Maths/Time.h"

class Bullet : public Entity
{
public:
    enum Origin {
      ENEMY, PLAYER
    };
    Bullet(glm::vec3 direction, Origin o);
    ~Bullet();

    virtual void update(float deltaTime);
    void mirrorDirX();
    void mirrorDirZ();
    Origin origin;
    Time time;
private:
    glm::vec3 dir;


};

#endif
