
#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"
#include "Texture.h"

class Skybox : public Mesh
{
public:
    Skybox(std::string right, std::string left, std::string up, std::string down, std::string back, std::string front);
    ~Skybox();

};

#endif
