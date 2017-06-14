#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Entity.h"

struct LightData
{
  glm::vec3 lightColor;
  glm::vec3 lightPosition;
  float lightStrength;
  float specularStrength;
};

class Light : public Entity
{
    public:
        Light();
        virtual ~Light();
        LightData getLightData();
        void setLightColor(glm::vec3 color);
        void setStrength(float strength);
        void setSpecularStrength(float strength);
        void setPosition(glm::vec3 position);
    private:
      LightData lightData;

};

#endif // LIGHT_H
