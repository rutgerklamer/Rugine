#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <GL/glew.h>
#include <vector>
#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"

class OBJloader
{
    public:
        OBJloader();
        ~OBJloader();
        static MeshData loadModel(const char* modelPath);
    private:

};

#endif // OBJLOADER_H
