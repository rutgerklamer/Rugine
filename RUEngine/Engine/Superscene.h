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

struct SceneData
{
  float gamma;
  float exposure;
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
            *  Return the scenedata of this scene.
            *  Takes in a exposure value.
            */
        SceneData getSceneData();
        std::vector<Entity*> entities;
        std::vector<Light*> lights;
        Input* input;
        Camera* camera;
        /**
            *  Update the scene and update the meshes.
            *  Takes in the deltaTime of the scene.
            */
        virtual void Update(float deltaTime);
    private:
      SceneData sceneData;

};

#endif // SUPERSCENE_H
