#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Shader.h"
#include "Engine/Camera.h"
#include "Engine/Mesh.h"
#include "Engine/Texture.h"
#include "Engine/Light.h"
#include "Engine/Entity.h"
#include "Engine/Skybox.h"
#include "Engine/Superscene.h"

class Renderer
{
    public:
      /**
          *  Constructor
          */
        Renderer();
        /**
            *  Destructor
            */
        virtual ~Renderer();
        /**
            *  render the scene
            *  takes in the current Time //TODO remove <-
            *  the shader we want to use //TODO improve performance <-
            *  the camera we want to get the view from //TODO improve performance <-
            *  the entity we want to render.
            *  the data of the scene.
            *  and a vector of light if we want multiple lights.
            */
        void render(double currentTime, Shader* shader, Camera* camera, Entity* entity, SceneData scenedata, std::vector<Light*>* lights = nullptr);
        void renderSkybox(double currentTime, Shader* shader, Camera* camera, Mesh* entity, SceneData scenedata);
    private:

};

#endif // RENDERER_H
