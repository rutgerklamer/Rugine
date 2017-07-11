#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>
#include "SOIL2/SOIL2.h"

namespace tex {
          /**
              *  Calls the SOIL2 and gl functions.
              */
          GLuint loadTexture(const char* path);
          GLuint loadCubemap(std::vector<const char*> faces);

}
#endif // TEXTURE_H
