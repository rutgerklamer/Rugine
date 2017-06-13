#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Engine/Shader.h"
#include "Engine/Camera.h"

class ResourceManager
{
    public:
        ResourceManager();
        virtual ~ResourceManager();
        void updateShaders(Shader* shader, Camera* camera);
        void setProjectionMatrix(Shader* shader, Camera* camera);
    private:


};

#endif // RESOURCEMANAGER_H
