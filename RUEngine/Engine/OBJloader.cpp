#include "OBJloader.h"

OBJloader::OBJloader()
{
  std::cout << "OBJloader initialized" << std::endl;
}

OBJloader::~OBJloader()
{

}

MeshData OBJloader::loadModel(const char* modelPath, bool isNormalMap)
{
  int multiplier;
  if (isNormalMap)
  {
    multiplier = 14;
  } else {
    multiplier = 8;
  }
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
    MeshData temp;
    return temp;
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
      uvIndices.push_back(uvIndex[0]);
      uvIndices.push_back(uvIndex[1]);
      uvIndices.push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    }
  }
  fclose(file);
  glm::vec3 min;
  glm::vec3 max;
  GLfloat *vertices = new GLfloat[vertexIndices.size()* multiplier];
   for( unsigned int i=0; i<vertexIndices.size(); i++ ) {
     //push vertices/uv's and normals to correct place in vertices
     unsigned int vertexIndex = vertexIndices[i];
     vertices[i * multiplier] = temp_vertices[ vertexIndex-1 ].x;
     vertices[i * multiplier + 1] = temp_vertices[ vertexIndex-1 ].y;
     vertices[i * multiplier + 2] = temp_vertices[ vertexIndex-1 ].z;
     if (temp_vertices[ vertexIndex-1 ].x < min.x) min.x = temp_vertices[ vertexIndex-1 ].x;
     if (temp_vertices[ vertexIndex-1 ].x > max.x) max.x = temp_vertices[ vertexIndex-1 ].x;
     if (temp_vertices[ vertexIndex-1 ].y < min.y) min.y = temp_vertices[ vertexIndex-1 ].y;
     if (temp_vertices[ vertexIndex-1 ].y > max.y) max.y = temp_vertices[ vertexIndex-1 ].y;
     if (temp_vertices[ vertexIndex-1 ].z < min.z) min.z = temp_vertices[ vertexIndex-1 ].z;
     if (temp_vertices[ vertexIndex-1 ].z > max.z) max.z = temp_vertices[ vertexIndex-1 ].z;
     unsigned int uvIndex = uvIndices[i];
     vertices[i * multiplier + 3] = temp_textures[ uvIndex-1 ].x;
     vertices[i * multiplier + 4] = temp_textures[ uvIndex-1 ].y;
     unsigned int normalIndex = normalIndices[i];
     vertices[i * multiplier + 5] = temp_normals[ normalIndex-1 ].x;
     vertices[i * multiplier + 6] = temp_normals[ normalIndex-1 ].y;
     vertices[i * multiplier + 7] = temp_normals[ normalIndex-1 ].z;

     if (isNormalMap) {
       if ((float)i /3 == floor((float)i/3)) {
         unsigned int vertexIndexTang = vertexIndices[i];
         glm::vec3 v0 = glm::vec3(temp_vertices[ vertexIndexTang-1 ]);
         glm::vec3 v1;
         glm::vec3 v2;
         if (i < vertexIndices.size() - 3) {
           vertexIndexTang = vertexIndices[i + 1];
           v1 = glm::vec3(temp_vertices[ vertexIndexTang-1 ]);
           vertexIndexTang = vertexIndices[i + 2];
           v2 = glm::vec3(temp_vertices[ vertexIndexTang-1 ]);
         } else {
           v1 = glm::vec3(1,1,1);
           v2 = glm::vec3(1,1,1);
         }
         unsigned int normalIndex = normalIndices[i];
         glm::vec3 normal = glm::vec3(temp_normals[ normalIndex-1 ]);

         unsigned int uvIndexTang = uvIndices[i];
         glm::vec2 uv0 = glm::vec2(temp_textures[ uvIndexTang-1 ]);
         glm::vec2 uv1;
         glm::vec2 uv2;
         if (i < vertexIndices.size() - 3) {
           uvIndexTang = uvIndices[i + 1];
           uv1 = glm::vec2(temp_textures[ uvIndexTang-1 ]);
           uvIndexTang = uvIndices[i + 2];
           uv2 = glm::vec2(temp_textures[ uvIndexTang-1 ]);
         } else {
           uv1 = glm::vec2(1,1);
           uv2 = glm::vec2(1,1);
         }

         glm::vec3 deltaPos;
         if(v0 == v1) {
           deltaPos = v2 - v0;
         } else {
           deltaPos = v1 - v0;
         }

         glm::vec2 deltaUV1 = uv1-uv0;
         glm::vec2 deltaUV2 = uv2-uv0;

         glm::vec3 tangent;
         glm::vec3 bitangent;

         if(deltaUV1.s != 0)
             tangent = deltaPos / deltaUV1.s;
         else
             tangent = deltaPos / 1.0f;

         tangent = glm::normalize(tangent - glm::dot(normal,tangent)*normal) ;

         bitangent = glm::normalize(glm::cross(tangent, normal));

         vertices[i * multiplier + 8] = tangent.x;
         vertices[i * multiplier + 9] = tangent.y;
         vertices[i * multiplier + 10] = tangent.z;

         vertices[i * multiplier + 11] = bitangent.x;
         vertices[i * multiplier + 12] = bitangent.y;
         vertices[i * multiplier + 13] = bitangent.z;

         if (i < vertexIndices.size() - 3) {
           vertices[i * multiplier + 8 + multiplier] = tangent.x;
           vertices[i * multiplier + 9 + multiplier] = tangent.y;
           vertices[i * multiplier + 10 + multiplier] = tangent.z;
           vertices[i * multiplier + 8 + multiplier + multiplier] = tangent.x;
           vertices[i * multiplier + 9 + multiplier + multiplier] = tangent.y;
           vertices[i * multiplier + 10 + multiplier + multiplier] = tangent.z;

           vertices[i * multiplier + 11 + multiplier] = bitangent.x;
           vertices[i * multiplier + 12 + multiplier] = bitangent.y;
           vertices[i * multiplier + 13 + multiplier] = bitangent.z;
           vertices[i * multiplier + 11 + multiplier + multiplier] = bitangent.x;
           vertices[i * multiplier + 12 + multiplier + multiplier] = bitangent.y;
           vertices[i * multiplier + 13 + multiplier + multiplier] = bitangent.z;
         }
       }
     }
   }
   MeshData meshData;
   meshData.min = min;
   meshData.max = max;
   meshData.size = vertexIndices.size() * multiplier * sizeof(GLfloat);
   meshData.vertices = vertices;
   return meshData;
}
