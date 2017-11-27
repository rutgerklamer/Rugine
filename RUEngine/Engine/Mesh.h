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
            * Initialize the mesh, Calls the LoadObject().
            * \see Mesh::LoadObject().
            * So we have a standard mesh for an object.
            */
        Mesh();
        /**
            * deconstructor.
            */
        virtual ~Mesh();
        /**
            * Update the framebuffer to the VAO of our mesh.
            */
        void Draw();
        /**
            *  return the size of the VAO.
            */
        int getSize();
        /**
            * Set the texture of our mesh by calling.
            * /see Texture::loadTexture().
            */
        void setTexture(GLuint tex);
        /**
            *  return the texture of this mesh.
            */
        GLuint getTexture();
        /**
            *  return the color of this mesh.
            */
        glm::vec3 getColor();
        /**
            *  set the color of this mesh.
            *  takes in a vec3 representing the RGB values.
            */
        void setColor(glm::vec3 color);
        /**
            *  return the diffuse texture of this mesh.
            */
        void setNormalMap(GLuint tex);
        /**
            *  return the normalMap texture of this mesh.
            */
        void bind();

        void setShininess(float s);
        float getShininess();


        GLuint getNormalMap();
        /**
            *  load an obj file, This will not load ANY obj files.
            *  this will take in the location of this file.
            *  And if the model will use a normal map.
            *  Because we don't want to send tangent space if we have no normal map
            *  /see OBJLoader::loadModel().
            *  This will also bind the Array of vertices, uv's, normals, (tangents, bittangents(binormals)).
            */
        void LoadObject(const char* objectPath, bool isNormalMap);
        /**
            *  Check if this model will will use lighting.
            */
        int hasLighting();
        bool showNormals;
        bool enabled;
        bool reflective;
        bool transparent;
        MeshData meshData;
        /**
            *  Return the modelMatrix by translating, rotating and scaling the model matrix.
            */
        virtual glm::mat4 getModelMatrix();
        /**
            *  Return the 3D position of the mesh.
            */
        virtual glm::vec3 getPosition();
    private:
      GLuint VAO, VBO, EBO;
      int lighting;
      Material material;
};

#endif // MESH_H
