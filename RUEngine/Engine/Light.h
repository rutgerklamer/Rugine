#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Entity.h"

class Light : public Entity
{
    public:
        Light();
        virtual ~Light();
        glm::vec3 getLightColor();
        void setLightColor(glm::vec3 color);
    private:
      glm::vec3 lightColor;


};

#endif // LIGHT_H
