#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Mesh.h"

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
        void update(float deltaTime);
        /**
            *  Return the modelMatrix by translating, rotating and scaling the model matrix.
            */
        glm::mat4 getModelMatrix();
        /**
            *  Return the 3D position of the mesh.
            */
        glm::vec3 getPosition();
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 eularAngles;
    private:
      glm::quat quaternation;

};

#endif // ENTITY_H
