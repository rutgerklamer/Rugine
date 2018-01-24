#include "Terrain.h"

Terrain::Terrain() : Entity()
{
  size = 10.0f;
}

Terrain::~Terrain()
{

}

void Terrain::Update(float deltaTime)
{

}

std::string Terrain::GetName()
{
  return name;
}

void Terrain::LoadTerrain()
{
  int count=0;

  int numCellsWide=256;
  int numCellsHigh=256;
  glm::vec3 maxBounds( numCellsWide / 10 * size);
  glm::vec3 minBounds( 0.0f);
  glm::vec3 pos(minBounds.x, 0, minBounds.z);
  int numVertsX=numCellsWide+1;
  int numVertsZ=numCellsHigh+1;
  int count2 = numVertsX * numVertsZ;
  float stepX=(maxBounds.x-minBounds.x)/numCellsWide;
  float stepZ=(maxBounds.z-minBounds.z)/numCellsHigh;
  GLfloat* vertices = new GLfloat[count2* 8];
  GLuint* indices = new GLuint[6*(numVertsX-1)*(numVertsZ-1)];
  int overallMin = -1.0f;
  int overallMax = 1.0f;

  int count22;
  int sizeoff;
  for (int z=0;z<numVertsZ;z++)
  {
      pos.x=minBounds.x;
      for (int x=0;x<numVertsX;x++)
      {
                  float height = generateHeight(x,z);
                  heights[x][z] = height;
                  vertices[count*8] = pos.x;
                  vertices[count*8 + 1] = height - 42;
                  vertices[count*8 + 2] = pos.z;
                  vertices[count*8 + 3] = (float)x/((float)numCellsWide - 1);
                  vertices[count*8 + 4] = (float)z/((float)numCellsHigh - 1);
                  vertices[count*8 + 5] = 0;
				          vertices[count*8 + 6] = 1;
				          vertices[count*8 + 7] = 0;
                  pos.x+=stepX;
                  count++;
                  sizeoff++;
      }
      pos.z+=stepZ;
  }
  count=0;
  int vIndex=0;
  for (int z=0;z<numVertsZ - 1;z++)
  {
      for (int x=0;x<numVertsX - 1;x++)
      {
          indices[count++]=vIndex;
          indices[count++]=vIndex+numVertsX;
          indices[count++]=vIndex+numVertsX+1;
          indices[count++]=vIndex;
          indices[count++]=vIndex+numVertsX+1;
          indices[count++]=vIndex+1;

          vIndex++;
       }
       vIndex++;
  }

  meshData.size = count2* 8 * 4;
  meshData.indsize = 6*(numVertsX-1)*(numVertsZ-1) * 8 ;

  meshData.indices = indices;
  meshData.vertices = vertices;
  bind();

}

glm::vec3 Terrain::GetNormal(float x, float z)
{
  float heightL = generateHeight(x+1,z);
  float heightR = generateHeight(x-1,z);
  float heightD = generateHeight(x,z-1);
  float heightU = generateHeight(x,z+1);
  glm::vec3 normal = glm::normalize(glm::vec3(heightL - heightR, 2.0f, heightD-heightU ));
  return normal;
}

float Terrain::GetTerrainHeight(float wX, float wZ)
{
  float terrainX = wX - position.x;
  float terrainZ = wZ - position.z;
  int heightLength = sizeof(heights) / sizeof(heights[0]);
  float gridSquare = (256 / 10 * size) / ((float)heightLength - 1);

  int gridX = (int)floor((terrainX / gridSquare));
  int gridZ = (int)floor((terrainZ / gridSquare));
  if (gridX >= heightLength || gridZ >= heightLength || gridX < 0 || gridZ < 0) {
    return 0;
  }
  float xCoord = (fmod(terrainX,gridSquare))/gridSquare;
  float zCoord = (fmod(terrainZ,gridSquare))/gridSquare;
  float height;
  if (xCoord <= (1-zCoord)) {
    height = barryCentric(glm::vec3(0, heights[gridX][gridZ], 0), glm::vec3(1,
    							heights[gridX + 1][gridZ], 0), glm::vec3(0,
    							heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
  } else {
    height = barryCentric(glm::vec3(1, heights[gridX + 1][gridZ], 0), glm::vec3(1,
    							heights[gridX + 1][gridZ + 1], 1), glm::vec3(0,
    							heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
  }
  return height + 10;
}

glm::vec2 Terrain::GetTerrainGrid(float wX, float wZ)
{
  float terrainX = wX - position.x;
  float terrainZ = wZ - position.z;
  int heightLength = sizeof(heights) / sizeof(heights[0]);
  float gridSquare = (256 / 10 * 100.0f) / ((float)heightLength - 1);

  int gridX = (int)floor((terrainX / gridSquare));
  int gridZ = (int)floor((terrainZ / gridSquare));

  float xCoord = (fmod(terrainX,gridSquare))/gridSquare;
  float zCoord = (fmod(terrainZ,gridSquare))/gridSquare;
  return glm::vec2(gridX + xCoord, gridZ + zCoord);
}

 float Terrain::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
 {
		float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}

float Terrain::generateHeight(float x, float z)
{
  return  Internoise(x / 15.0f, z / 15.0f) / 5000000.0f;
}

float Terrain::getSmooth(float x, float z)
{
  float corners = (GetRandom(x-1,z-1) + GetRandom(x+1,z-1) + GetRandom(x-1,z+1) + GetRandom(x+1,z+1))/16.0f;
  float sides = (GetRandom(x-1,z) + GetRandom(x+1,z) + GetRandom(x,z-1) + GetRandom(x,z+1))/8.0f;
  float center = GetRandom(x,z)/4.0f;
  return corners+sides+center;
}

float Terrain::Internoise(float x, float z)
{
  int intX = (int) x;
  int intZ = (int) z;
  float fracX = x - intX;
  float fracZ = z - intZ;

  float v1 = getSmooth(intX, intZ);
  float v2 = getSmooth(intX + 1, intZ);
  float v3 = getSmooth(intX, intZ + 1);
  float v4 = getSmooth(intX + 1, intZ + 1);

  float i1 = Interpolate(v1, v2, fracX);
  float i2 = Interpolate(v3, v4, fracX);

  return Interpolate(i1, i2, fracZ);
}

float Terrain::Interpolate(float a, float b, float blend)
{
  double theta = blend * 3.1416f;
  float f = (1.0f - cos(theta)) * 0.5f;
  return a * (1.0f - f) + b * f;
}

float Terrain::GetRandom(float x, float z)
{
  srand( x * 4 *z  * 2 );
  return rand() ;
}
