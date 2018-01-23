#ifndef WATER_H
#define WATER_H

#include "Mesh.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "Entity.h"
class Water
{
public:
    /**
        * Constructor
        * Takes in glm::vec2 s, this is used to determine the size of the 2d water plane
        * Takes in a glm::vec3 p, This is the position of the water plane
        */
    Water(glm::vec2 s, glm::vec3 p);
    /** 
        * Destructor
        */
    ~Water();
    glm::vec2 waterSize;
    glm::vec3 waterPosition;
    Framebuffer* top;
    Framebuffer* bottom;
    Entity* entity;
    GLuint DUDVmap;
    GLuint normalMap;
};

#endif
