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
  GLuint normalMap;
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
            *  this will set the texture by taking in an loaded image from
            * /see Texture::loadTexture().
            */
        GLuint getTexture();
        /**
            *  return the diffuse texture of this mesh.
            */
        void setNormalMap(GLuint tex);
        /**
            *  return the normalMap texture of this mesh.
            */
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
        /**
            *  Return the modelMatrix by translating, rotating and scaling the model matrix.
            */
        virtual glm::mat4 getModelMatrix();
        /**
            *  Return the 3D position of the mesh.
            */
        virtual glm::vec3 getPosition();
    private:
      MeshData meshData;
      GLuint VAO, VBO, EBO;
      int lighting;
};

#endif // MESH_H
