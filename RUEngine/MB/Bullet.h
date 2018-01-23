#ifndef BULLET_H
#define BULLET_H

#include "Engine/Entity.h"
#include "Maths/Time.h"

class Bullet : public Entity
{
public:
    /**
        * This is used to determine where the bullet came from,
        * Bullets collide with enemies and the players,
        * And I didn't want to keep track of two vectors
        */
    enum Origin {
      ENEMY, PLAYER
    };
    /**
        * Constructor
        * Takes in glm::vec3 direction, this is the direction the bullet will fly
        * Takes in a Origin o, This is where the bullet originated from
        */
    Bullet(glm::vec3 direction, Origin o);
    /**
        * Destructor
        */
    ~Bullet();
    /**
        * Update loop, part of the Rugine
        * Takes in float deltaTime, You probably want to use this
        */
    virtual void update(float deltaTime);
    /** 
        * This will reflect the bullet in the X direction,
        * Used when it's colliding with a mirror
        */
    void mirrorDirX();
    /** 
        * This will reflect the bullet in the Z direction,
        * Used when it's colliding with a mirror
        */
    void mirrorDirZ();
    Origin origin;
    Time time;
private:
    glm::vec3 dir;
};

#endif
