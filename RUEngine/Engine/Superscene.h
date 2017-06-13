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

class Superscene
{
    public:
        Superscene(Input* input);
        virtual ~Superscene();
        void addChild(Mesh* mesh);
        void addLight(Mesh* light);
        std::vector<Mesh*> meshes;
        std::vector<Mesh*> lights;
        Input* input;
        Camera* camera;
        virtual void Update(float deltaTime);
    private:

};

#endif // SUPERSCENE_H
