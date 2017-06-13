#include "Mesh.h"

Mesh::Mesh()
{

  //Set vertices manually
  //TODO rely on object loading only
  float vertices[] = {
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0,  0.0,  -1.0,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,  0.0,  -1.0,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0,  0.0,  -1.0,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0,  0.0,  -1.0,
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0,  0.0,  -1.0,
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0,  0.0,  -1.0,

     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0,  0.0,  1.0,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0,  0.0,  1.0,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0,  0.0,  1.0,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0,  0.0,  1.0,
     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,  0.0,  1.0,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0,  0.0,  1.0,

     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0,  0.0,  0.0,
     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0,  0.0,  0.0,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0,  0.0,  0.0,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0,  0.0,  0.0,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0,  0.0,  0.0,
     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0,  0.0,  0.0,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0,  0.0,  0.0,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,1.0,  0.0,  0.0,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0,  0.0,  0.0,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0,  0.0,  0.0,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0,  0.0,  0.0,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0,  0.0,  0.0,

     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0,  -1.0,  0.0,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0,  -1.0,  0.0,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0,  -1.0,  0.0,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0,  -1.0,  0.0,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0,  -1.0,  0.0,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0,  -1.0,  0.0,

     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0,  1.0, 0.0,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0,  1.0, 0.0,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0,  1.0, 0.0,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0,  1.0, 0.0,
     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0,  1.0, 0.0,
     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0,  1.0, 0.0,
  };

  //Manual indices
   GLuint indices[] = {
       0, 1, 2,
       3, 4, 5,
       6, 7, 8,
       9, 10, 11,
       12, 13, 14,
       15, 16, 17,
       18, 19, 20,
       21, 22, 23,
       24, 25, 26,
       27, 28, 29,
       30, 31, 32,
       33, 34, 35,
       36
   };


  //Get indices size
  size = sizeof(indices) / sizeof(indices[0]);

  //Generate the Buffer Objects
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  //Bind vertex (array) buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //Bind element (array) buffer object
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  //Tell where the vertices, texture coordinates and normals are stored in the array
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
  //Location in vertex shader we want to send them to
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(5 * sizeof(GLfloat)));
  glEnableVertexAttribArray(3);
  glBindVertexArray(0);
}

Mesh::~Mesh()
{

}

int Mesh::getSize()
{
  //Return size of the "EBO"
  return this->size;
}

void Mesh::Draw()
{
  //Bind the VAO of this object

  glBindVertexArray(this->VAO);
}

void Mesh::setTexture(GLuint tex)
{
  //Set the texture
  this->texture = tex;
}

GLuint Mesh::getTexture()
{
  //Give texture to anybody that asks for it
  return this->texture;
}

int Mesh::hasLighting()
{
  return this->lighting;
}

glm::mat4 Mesh::getModelMatrix()
{

}

glm::vec3 Mesh::getPosition()
{

}

void Mesh::LoadObject(const char* objectPath)
{
  file = fopen(objectPath, "r");
  if( file == NULL ){
    std::cout << "failed to open: " << objectPath << std::endl;
  }
while( 1 ){
    char lineHeader[256];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) {
        break; // EOF = End Of File. Quit the loop.
      }
      if ( strcmp( lineHeader, "v" ) == 0 ){
        //On line start with v push vertex data to vertices
        glm::vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
        temp_vertices.push_back(vertex);
      } else if ( strcmp( lineHeader, "vt" ) == 0 ) {
        //On line start with vt push UV data to vertices
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        temp_textures.push_back(uv);
      } else if ( strcmp( lineHeader, "vn" ) == 0 ) {
        //On line start with vn push normal data to vertices
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        temp_normals.push_back(normal);
      } else if ( strcmp( lineHeader, "f" ) == 0 ) {

      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
      if (matches != 9){
          printf("File can't be read\n");
      }
      //On line start with f push indices data to indices
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      uvIndices    .push_back(uvIndex[0]);
      uvIndices    .push_back(uvIndex[1]);
      uvIndices    .push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    }
  }
  GLfloat *vertices = new GLfloat[vertexIndices.size()* 8];
  GLfloat *indices[vertexIndices.size()];
   for( unsigned int i=0; i<vertexIndices.size(); i++ ) {
     //push vertices/uv's and normals to correct place in vertices
     unsigned int vertexIndex = vertexIndices[i];
     vertices[i * 8] = temp_vertices[ vertexIndex-1 ].x;
     vertices[i * 8 + 1] = temp_vertices[ vertexIndex-1 ].y;
     vertices[i * 8 + 2] = temp_vertices[ vertexIndex-1 ].z;
     unsigned int uvIndex = uvIndices[i];
     vertices[i * 8 + 3] = temp_textures[ uvIndex-1 ].x;
     vertices[i * 8 + 4] = temp_textures[ uvIndex-1 ].y;
     unsigned int normalIndex = normalIndices[i];
     vertices[i * 8 + 5] = temp_normals[ normalIndex-1 ].x;
     vertices[i * 8 + 6] = temp_normals[ normalIndex-1 ].y;
     vertices[i * 8 + 7] = temp_normals[ normalIndex-1 ].z;


   }
   size = vertexIndices.size()* 8 * sizeof(GLfloat);
   std::cout << "size ::::" << size << std::endl;

   //See Plane() for more information
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *) 0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(5 * sizeof(GLfloat)));
   glEnableVertexAttribArray(2);
   glBindVertexArray(0);

   fclose(file);
}
