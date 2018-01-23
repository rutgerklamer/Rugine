#ifndef MIRROR_H
#define MIRROR_H

#include "Engine/Entity.h"

class Mirror : public Entity
{
public:
    /**
        * Constructor
        * Takes in float ma, this is the max units this mirror can move in the positive given direction
        * Takes in float mi, this is the max units this mirror can move in the negative given direction
        * Takes in bool z, This is used to determine whether the mirror is horizontal or vertical
        * Takes in glm::vec3 o, This is the origin of the mirror
        */
    Mirror(float ma, float mi, bool z, glm::vec3 o);
    /** 
        * Destructor
        */
    ~Mirror();
    /** 
        * Update, part of Rugine
        * Takes in float deltaTime, you probably want to use this
        */
    virtual void update(float deltaTime);
    /**
        * Returns if the mirror is horizontal or vertical
        */
    bool checkZ();
private:
  float max,cur,min;
  bool isZ;
  glm::vec3 origin;

};

#endif
