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
      unsigned int size;
      int lighting = 1;
      GLuint texture;
      std::vector<glm::vec3> temp_vertices;
      std::vector<glm::vec2> temp_textures;
      std::vector<glm::vec3> temp_normals;

      std::vector<int> vertexIndices;
      std::vector<int> uvIndices;
      std::vector<int> normalIndices;

      FILE* file;

};

#endif // MESH_H
