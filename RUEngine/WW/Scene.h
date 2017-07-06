#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <GL/glew.h>
#include <vector>
#include "glfw3.h"

#include "Engine/Camera.h"
#include "Engine/Mesh.h"
#include "Engine/Entity.h"
#include "Engine/Superscene.h"
#include "Engine/Texture.h"
#include "Engine/Light.h"
#include "Maths/Time.h"

class Scene : public Superscene
{
    public:
        Scene(Input* ip);
        virtual ~Scene();
        void Update(float deltaTime);
        void readFile(const char* filename);
    private:
      enum States
      {
        OFF,HEAD,TAIL,WIRE
      };
      struct Cell {
        Entity* entity;
        States state;
      };
      Entity* mesh;
      Light* light;
      std::vector<std::vector<Cell>> cells;
      int rows;
      Time* timer = new Time();
      GLuint red;
      GLuint blue;
      GLuint yellow;
      GLuint grey;
      std::vector<std::string> finishedGrid;
};

#endif // SCENE_H
