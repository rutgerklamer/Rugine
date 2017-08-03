#include "Mesh.h"
#include "Engine/OBJloader.h"

Mesh::Mesh()
{
  LoadObject("Assets/untitled.obj", false);
  lighting = 0;
  showNormals = false;
  enabled = true;
  reflective = false;
  transparent = false;
  meshData.vertices = 0;
  meshData.size = 0;
  meshData.texture = NULL;
  meshData.color = glm::vec3(0,0,0);
  meshData.normalMap = NULL;
  meshData.min = glm::vec3(0,0,0);
  meshData.max = glm::vec3(0,0,0);
}

Mesh::~Mesh()
{

}

int Mesh::getSize()
{
  return this->meshData.size;
}


void Mesh::Draw()
{
  glBindVertexArray(this->VAO);
}

void Mesh::setTexture(GLuint tex)
{  this->meshData.texture = tex;
}

GLuint Mesh::getTexture()
{
  return this->meshData.texture;
}

void Mesh::setNormalMap(GLuint tex)
{
  this->meshData.normalMap = tex;
}

GLuint Mesh::getNormalMap()
{
  return this->meshData.normalMap;
}

int Mesh::hasLighting()
{
  return this->lighting;
}

glm::mat4 Mesh::getModelMatrix()
{

}

void Mesh::setColor(glm::vec3 color)
{
  this->meshData.color = color;
}

glm::vec3 Mesh::getColor()
{
  return this->meshData.color;
}

glm::vec3 Mesh::getPosition()
{

}

void Mesh::LoadObject(const char* objectPath, bool isNormalMap)
{
   int multiplier;
   if (isNormalMap)
   {
     multiplier = 14;
   } else {
     multiplier = 8;
   }

   meshData = OBJloader::loadModel(objectPath, isNormalMap);
   meshData.texture = NULL;
   meshData.normalMap = NULL;

   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, meshData.size, meshData.vertices, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, multiplier * sizeof(GLfloat), (GLvoid *) 0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, multiplier * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, multiplier * sizeof(GLfloat), (GLvoid *)(5 * sizeof(GLfloat)));
   glEnableVertexAttribArray(2);
   if (isNormalMap) {
     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, multiplier * sizeof(GLfloat), (GLvoid *)(8 * sizeof(GLfloat)));
     glEnableVertexAttribArray(3);
     glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, multiplier * sizeof(GLfloat), (GLvoid *)(11 * sizeof(GLfloat)));
     glEnableVertexAttribArray(4);
   }
   glBindVertexArray(0);
   delete meshData.vertices;
}
