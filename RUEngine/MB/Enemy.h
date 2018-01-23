#ifndef ENEMY_H
#define ENEMY_H

#include "Engine/Entity.h"
#include "Bullet.h"
#include "Maths/Time.h"

class Enemy : public Entity
{
public:
    /**
        * Constructor
        * Takes in Entity* entity, this is the player you want the entity to shoot at
        */
    Enemy(Entity* entity);
    /** 
        * Destructor
        */
    ~Enemy();
    
    /** 
        * Update, part of Rugine
        * Takes in float deltaTime, you probably want to use this
        */
    virtual void update(float deltaTime);
    std::vector<Bullet*> bullets;
private:
  Time time;
  Entity* player;

};

#endif
