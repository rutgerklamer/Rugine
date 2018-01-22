
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
     /**
            * Constructor
            * Takes in a camera and input
            */
    Raycast(Camera* camera, Input* input);
     /**
            * Destructor
            */
    ~Raycast();
     /**
            * Update loop
            */
    void Update();
     /**
            * Check if the ray is colliding with a entity
            * Takes in a 3D entity, 2D entities can be send but calculations won't make any sense
            */
    void checkCollision(Entity* entity);
    /**
            * Change the camera we are sending the ray from
            * Takes in the camera you want to use
            */
    void setCamera(Camera*camera);
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec2 mouse;
    glm::vec3 mouseRay;
    Camera* camera;
    Input* input;
};

#endif
