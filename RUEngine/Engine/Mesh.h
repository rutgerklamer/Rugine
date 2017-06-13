#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"

#include <vector>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


struct MeshData
{
  GLfloat* vertices;
  int size;
  GLuint texture;
};

class Mesh
{
    public:
        Mesh();
        virtual ~Mesh();
        void Draw();
        int getSize();
        void setTexture(GLuint tex);
        GLuint getTexture();
        void LoadObject(const char* objectPath);
        int hasLighting();
        bool showNormals = false;
        virtual glm::mat4 getModelMatrix();
        virtual glm::vec3 getPosition();
    private:
      GLuint VAO, VBO, EBO;
      MeshData meshData;
      int lighting = 1;
};

#endif // MESH_H
