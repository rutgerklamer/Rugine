#ifndef ENEMY_H
#define ENEMY_H

#include "Engine/Entity.h"
#include "Bullet.h"
#include "Maths/Time.h"

class Enemy : public Entity
{
public:
    Enemy(Entity* entity);
    ~Enemy();

    virtual void update(float deltaTime);
    std::vector<Bullet*> bullets;
private:
  Time time;
  Entity* player;

};

#endif
