#ifndef SUPERSCENE_H
#define SUPERSCENE_H

#include <iostream>
#include <GL/glew.h>
#include <vector>
#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Input.h"
#include "Engine/Entity.h"
#include "Engine/Light.h"
#include "Skybox.h"
#include "Engine/Framebuffer.h"
#include "Water.h"

struct SceneData
{
  float gamma;
  float exposure;
  float fogDensity;
  glm::vec3 fogColor;
};

class Superscene
{
    public:
      /**
          *  Constructor
          *  Takes in a pointer of input so we can control it.
          */
        Superscene(Input* input);
        /**
            *  Destructor
            */
        virtual ~Superscene();
        /**
            *  Add a mesh to the vector of meshes.
            */
        void addChild(Entity* mesh);
        /**
            *  Add a skybox to the scene
            *  Takes in a Skybox pointer.
            */
        void addSkybox(Skybox* sb);
        /**
            *  Add a light to the vector of lights.
            *  Takes in a Entity pointer.
            */
        void addLight(Light* light);
        /**
            *  Set the gamma of this scene.
            *  Takes in a Light pointer.
            */
        void setGamma(float gamma);
        /**
            *  Set the exposure of this scene.
            *  Takes in a gamma value
            */
        void setExposure(float exposure);
        /**
            *  Set the size and position of the water
            *  Takes the size a water object
            */
        void addWater(Water* w);
        /**
            *  Set the exposure of this scene.
            *  Takes in a density value
            */
        void setFogDensity(float density);
        /**
            *  Set the fogColor of this scene.
            *  Takes in a vec3 which represents RGB
            */
        void setFogColor(glm::vec3 color);
        /**
            *  Tell the scene we want to use a framebuffer
            *  Takes in 5 const chars of all supported shader stages
            */
        void addFramebuffer(const char* vertexPath, const char* fragmentPath);
        /**
            *  Return the scenedata of this scene.
            *  Takes in a exposure value.
            */
        SceneData getSceneData();
        std::vector<Entity*> entities;
        std::vector<Light*> lights;
        Input* input;
        Camera* camera;
        Skybox* skybox;
        Framebuffer* framebuffer;
        Water* water;
        /**
            *  Update the scene and update the meshes.
            *  Takes in the deltaTime of the scene.
            */
        virtual void Update(float deltaTime);
    private:
      SceneData sceneData;

};

#endif // SUPERSCENE_H
