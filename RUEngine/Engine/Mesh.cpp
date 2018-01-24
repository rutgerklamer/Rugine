#include "Mesh.h"
#include "Engine/OBJloader.h"

Mesh::Mesh()
{
//  LoadObject("Assets/untitled.obj", false);
  lighting = 0;
  showNormals = false;
  enabled = true;
  reflective = false;
  transparent = false;
  meshData.vertices = 0;
  meshData.size = 0;
  meshData.texture = NULL;
  material.color = glm::vec3(0,0,0);
  meshData.normalMap = NULL;
  meshData.min = glm::vec3(0,0,0);
  meshData.max = glm::vec3(0,0,0);
  meshData.indices = 0;
  meshData.indsize = 0;

  material.shininess = 8.0f;
  is2D = false;
}

Mesh::~Mesh()
{
}

bool Mesh::check2D()
{
    return is2D;
}

void Mesh::make2D()
{
    GLfloat vertices[] = {
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, 0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f,  -0.5f, -0.5f,  0.0f, 0.0f,
   };
   meshData.min = glm::vec3(1.0f,-1.0f,-1.0f);
   meshData.max = glm::vec3(1.0f,-1.0f,1);
   meshData.size = sizeof(vertices) / sizeof(vertices[0]) / 5;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
   glEnableVertexAttribArray(2);
   glBindVertexArray(0);
   this->is2D = true;
}

int Mesh::getSize()
{
  return this->meshData.size;
}

void Mesh::setShininess(float s)
{
  this->material.shininess = s;
}
float Mesh::getShininess()
{
  return this->material.shininess;
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
	return glm::mat4(0);
}

void Mesh::setColor(glm::vec3 color)
{
  this->material.color = color;

}

glm::vec3 Mesh::getColor()
{
  return this->material.color;
}

glm::vec3 Mesh::getPosition()
{
	return glm::vec3(0);
}

void Mesh::bind()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, meshData.size, meshData.vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData.indsize, meshData.indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(3);
  glBindVertexArray(0);
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
