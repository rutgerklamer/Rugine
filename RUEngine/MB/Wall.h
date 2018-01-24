#ifndef WALL_H
#define WALL_H

#include "Engine/Entity.h"

class Wall : public Entity
{
public:
    /**
        * Constructor
        */
    Wall();
    /**
        * Destructor
        */
    ~Wall();
    /** 
           * Update, part of Rugine
           * Takes in float deltaTime, you probably want to use this
           */
    virtual void update(float deltaTime);

private:

};

#endif
