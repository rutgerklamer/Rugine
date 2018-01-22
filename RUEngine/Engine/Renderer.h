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
            *  Render the scene
            *  Takes in the current Time //TODO remove <-
            *  The shader we want to use //TODO improve performance <-
            *  The camera we want to get the view from //TODO improve performance <-
            *  The entity we want to render
            *  The data of the scene
            *  And a vector of light if we want multiple lights
            */
        void render(double currentTime, Shader* shader, Camera* camera, Entity* entity, SceneData scenedata, glm::vec4 waterPlane, std::vector<Light*>* lights = nullptr);
        /**
            * Render the 2D GUI stuff of the scene
            * Takes in current time //TODO remove 
            * Takes in the shader we want to use
            * Takes in the entity 
            */
        void render2D(double currentTime, Shader* shader, Entity* entity);
        /**
            *  Render the scene's skybox
            *  Takes in the current Time //TODO remove <-
            *  The shader we want to use //TODO improve performance <-
            *  The camera we want to get the view from //TODO improve performance <-
            *  The entity we want to render
            *  The data of the scene
            */
        void renderSkybox(double currentTime, Shader* shader, Camera* camera, Mesh* entity, SceneData scenedata, glm::vec4 waterPlane, GLuint skybox);
        /**
            *  Tender the scene
            *  Takes in the shader we want to use //TODO improve performance <-
            *  The texture to display on the quad
            */
        void renderFramebuffer(Shader* shader, GLuint texture, Input* input);
        /**
            *  Tender the water of the scene
            *  Takes in the shader we want to use //TODO improve performance <-
            *  The texture to display on the water quad
            */
        void renderWater(Shader* shader, GLuint reflectionTexture, GLuint refractionTexture, GLuint waterTexture, GLuint normalTexture, Entity* entity);

        GLuint Texture;
    private:

};

#endif // RENDERER_H
