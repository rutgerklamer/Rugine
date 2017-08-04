
#ifndef WATER_H
#define WATER_H

#include "Mesh.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "Entity.h"
class Water
{
public:
    Water(glm::vec2 s, glm::vec3 p);
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
