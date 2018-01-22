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
  GLuint* indices;
  int size;
  int indsize;
  GLuint texture;
  GLuint normalMap;

  glm::vec3 min;
  glm::vec3 max;
};

struct Material {
  float shininess;
  glm::vec3 color;
};

class Mesh
{
    public:
        /**
            * Constructor
            * Initialize the mesh, Calls the LoadObject()
            * \see Mesh::LoadObject()
            * So we have a standard mesh for an object
            */
        Mesh();
        /**
            * Deconstructor
            */
        virtual ~Mesh();
        /**
            * Update the framebuffer to the VAO of our mesh
            */
        void Draw();
        /**
            * Return the size of the VAO
            */
        int getSize();
        /**
            * Set the texture of our mesh by calling
            * /see Texture::loadTexture()
            */
        void setTexture(GLuint tex);
        /**
            * Return the texture of this mesh
            */
        GLuint getTexture();
        /**
            * Make a mesh 2D so it will be rendered in 2D
            */
        void make2D();
        /**
            * Check if the mesh has been made 2D
            */
        bool check2D();
        /**
            * Return the color of this mesh
            */
        glm::vec3 getColor();
        /**
            * Set the color of this mesh
            * Takes in a vec3 representing the RGB values
            */
        void setColor(glm::vec3 color);
        /**
            * Return the diffuse texture of this mesh
            */
        void setNormalMap(GLuint tex);
        /**
            * Return the normalMap texture of this mesh
            */
        void bind();
         /**
            * Set the shininess of this mesh
            * Takes in a float you want the shininess to be
            */
        void setShininess(float s);
        /**
            * Returns the shininess of this mesh
            */
        float getShininess();

        GLuint getNormalMap();
        /**
            *  load an obj file, This will not load ANY obj files
            *  This will take in the location of this file
            *  And if the model will use a normal map
            *  Because we don't want to send tangent space if we have no normal map
            *  /see OBJLoader::loadModel()
            *  This will also bind the Array of vertices, uv's, normals, (tangents, bittangents(binormals))
            */
        void LoadObject(const char* objectPath, bool isNormalMap);
        /**
            * Check if this model will will use lighting
            */
        int hasLighting();
        bool showNormals;
        bool enabled;
        bool reflective;
        bool transparent;
        MeshData meshData;
        /**
            * Return the modelMatrix by translating, rotating and scaling the model matrix
            */
        virtual glm::mat4 getModelMatrix();
        /**
            * Return the 3D position of the mesh
            */
        virtual glm::vec3 getPosition();
    private:
      bool is2D;
      GLuint VAO, VBO, EBO;
      int lighting;
      Material material;
};

#endif // MESH_H
