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
  float extinction;
};

class Light : public Entity
{
    public:
      /**
          * Constructor
          */
        Light();
        /**
            * Destructor
            */
        virtual ~Light();
        /**
            * Return the struct of lightdata this light has
            */
        LightData getLightData();
        /**
            * Set the lightColor
            * Takes in a vector3 with (r,g,b) values
            */
        void setLightColor(glm::vec3 color);
        /**
            * Set the strength of the light
            * Takes in the strength
            */
        void setStrength(float strength);
        /**
            * Set the extinction of the light
            * Takes in the extinction
            */
        void setExtinction(float extinction);
        /**
            * Set the specular strength of the light
            * Takes in the strength
            //TODO Move to mesh!!!!!
            */
        void setSpecularStrength(float strength);
        /**
            * Change the position of the light
            * Takes in a vector3 of the position
            */
        void setPosition(glm::vec3 position);
    private:
      LightData lightData;

};

#endif // LIGHT_H
