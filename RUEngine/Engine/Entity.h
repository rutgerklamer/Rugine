#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Mesh.h"
#include "Input.h"

class Entity : public Mesh
{
    public:
      /**
              *  Constructor
              */
        Entity();
        /**
                *  Deconstructor
                */
        virtual ~Entity();
        /**
                *  called by the Superscene
                */
        virtual void update(float deltaTime);
        /**
            *  Return the modelMatrix by translating, rotating and scaling the model matrix.
            */
        glm::mat4 getModelMatrix();
        void fixedUpdate(float deltaTime);
        glm::mat4 getRotationScaleMatrix();
        glm::mat4 getRotationMatrix();
        glm::mat4 getScaleMatrix();
        glm::quat getQuaternation();
        void setInput(Input* i);
        glm::vec4 getScreenPosition();
        Input* input();
        /**
            *  Return the 3D position of the mesh.
            */
        glm::vec3 getPosition();

        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 scale;
        glm::vec3 eularAngles;
    private:
      glm::quat quaternation;
      Input* _input;

};

#endif // ENTITY_H
