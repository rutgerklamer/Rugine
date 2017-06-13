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
        Entity();
        virtual ~Entity();
        glm::mat4 getModelMatrix();
        glm::vec3 getPosition();
        glm::vec3 position;
        glm::vec3 scale = glm::vec3(1,1,1);
        glm::vec3 eularAngles;
        glm::quat quaternation;
    private:


};

#endif // ENTITY_H
