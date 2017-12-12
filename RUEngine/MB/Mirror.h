#ifndef MIRROR_H
#define MIRROR_H

#include "Engine/Entity.h"

class Mirror : public Entity
{
public:
    Mirror(float ma, float mi, bool z, glm::vec3 o);
    ~Mirror();

    virtual void update(float deltaTime);
    bool checkZ();
private:
  float max,cur,min;
  bool isZ;
  glm::vec3 origin;

};

#endif
