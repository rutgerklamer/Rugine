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
        Superscene(Input* input);
        virtual ~Superscene();
        void addChild(Entity* mesh);
        void addLight(Light* light);
        void setGamma(float gamma);
        void setExposure(float exposure);
        SceneData getSceneData();
        std::vector<Entity*> entities;
        std::vector<Light*> lights;
        Input* input;
        Camera* camera;
        virtual void Update(float deltaTime);
    private:
      SceneData sceneData;

};

#endif // SUPERSCENE_H
