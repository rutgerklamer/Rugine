#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "Light.h"

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();
        void render(double currentTime, Shader* shader, Camera* camera, Mesh* mesh, Light* light = NULL);
    private:

};

#endif // RENDERER_H
