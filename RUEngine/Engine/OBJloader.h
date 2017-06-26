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
      /**
          *  Constructor
          */
        OBJloader();
        /**
            *  Destructor
            */
        ~OBJloader();
        /**
            *  load a model, Returning the meshdata we created in here.
            *  takes n the path of the .obj and see if it has a normal map or not.
            */
        static MeshData loadModel(const char* modelPath, bool isNormalMap);
    private:

};

#endif // OBJLOADER_H
