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
      /**
          *  Constructor
          */
        ResourceManager();
        /**
            *  Destructor
            */
        virtual ~ResourceManager();
        /**
            *  Update the shaders viewmatrix.
            *  Takes in the shader you want to update
            *  and the camera you want the viewmatrix from.
            */
        void updateShaders(Shader* shader, Camera* camera);
        /**
            *  Update the shaders projection matrix.
            *  Takes in the shader you want to update
            *  and the camera you want the projectionmatrix from.
            */
        void setProjectionMatrix(Shader* shader, Camera* camera);
        /**
            *  Remove lights still binded to the shader
            *  Takes in the shader you want to update
            */
        void removeLights(Shader* shader);
    private:


};

#endif // RESOURCEMANAGER_H
