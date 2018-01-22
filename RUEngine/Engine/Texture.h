#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>
#include "SOIL2/SOIL2.h"

namespace tex {
          /**
              * Calls the SOIL2 and gl functions
              * Takes in the texture path
              */
          GLuint loadTexture(const char* path);
          /**
              * Calls the SOIL2 and gl functions
              * Takes in a vector which has 6 different paths for the cubes faces
              */
          GLuint loadCubemap(std::vector<const char*> faces);
}
#endif // TEXTURE_H
