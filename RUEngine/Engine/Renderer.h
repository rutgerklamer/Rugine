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
#include "Engine/Superscene.h"

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();
        void render(double currentTime, Shader* shader, Camera* camera, Entity* entity, SceneData scenedata, std::vector<Light*>* lights = nullptr);
    private:

};

#endif // RENDERER_H
