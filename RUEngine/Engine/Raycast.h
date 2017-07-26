
#ifndef RAYCAST_H
#define RAYCAST_H

#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Input.h"
#include "Entity.h"

class Raycast
{
public:
    Raycast(Camera* camera, Input* input);
    ~Raycast();
    void Update();
    void checkCollision(Entity* entity);
    void setCamera(Camera*camera);
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec2 mouse;
    glm::vec3 mouseRay;
    Camera* camera;
    Input* input;
};

#endif
