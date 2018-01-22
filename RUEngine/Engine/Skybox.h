#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"
#include "Texture.h"

class Skybox : public Mesh
{
public:
    /**
        * Constructor
        * Takes in all the paths of the textures you want to use for the skybox
        */
    Skybox(std::string right, std::string left, std::string up, std::string down, std::string back, std::string front);
    /** 
        * Deconstructor
        */
    ~Skybox();

};

#endif
