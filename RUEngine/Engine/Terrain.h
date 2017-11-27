#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <typeinfo>

#include "Entity.h"

class Terrain : public Entity
{
public:
    Terrain();
    ~Terrain();
    void Update(float deltaTime);
    std::string GetName();
    void LoadTerrain();
    glm::vec2 GetTerrainGrid(float wX, float wZ);
    float GetRandom(float x, float z);
    float generateHeight(float x, float z);
    float getSmooth(float x, float z);
    float Interpolate(float a, float b, float blend);
    float Internoise(float x, float z);
    float GetTerrainHeight(float wX, float wZ);
    float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
    glm::vec3 GetNormal(float x, float z);

    int numCellsWide,
        numCellsHigh;
float heights[257][257];
float size;

    std::string name;
};

#endif
