
#include <iostream>
#include <vector>
#include "Skybox.h"


Skybox::Skybox(std::string right, std::string left, std::string up, std::string down, std::string back, std::string front) : Mesh()
{
  //Make a cube
  LoadObject("Assets/cube.obj", false);
  //Make a cubemap
   std::vector<const char*> faces2;
     faces2.push_back(right.c_str());
     faces2.push_back(left.c_str());
     faces2.push_back(up.c_str());
     faces2.push_back(down.c_str());
     faces2.push_back(back.c_str());
     faces2.push_back(front.c_str());

    setTexture(tex::loadCubemap(faces2));
}

Skybox::~Skybox()
{

}
