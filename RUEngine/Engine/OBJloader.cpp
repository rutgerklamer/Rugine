#include "OBJloader.h"

OBJloader::OBJloader()
{
  std::cout << "OBJloader initialized" << std::endl;
}

OBJloader::~OBJloader()
{

}

MeshData OBJloader::loadModel(const char* modelPath)
{
  std::vector<glm::vec3> temp_vertices;
  std::vector<glm::vec2> temp_textures;
  std::vector<glm::vec3> temp_normals;

  std::vector<int> vertexIndices;
  std::vector<int> uvIndices;
  std::vector<int> normalIndices;

  FILE* file = fopen(modelPath, "r");
  if( file == NULL ){
    std::cout << "failed to open: " << modelPath << std::endl;
    fclose(file);
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
   MeshData meshData;
   meshData.size = vertexIndices.size() * 8 * sizeof(GLfloat);
   meshData.vertices = vertices;
   return meshData;
}
