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
        bool GenerateMazeHard();
    private:
      enum Dir
      {
        N, W ,S, E
      };
      struct Cell {
        Entity* entity;
        glm::vec3 solvedColor;
        bool visited = false;
        bool listed = false;
      };
      Entity* mesh;
      Light* light;
      std::vector<std::vector<Cell>> cells;
      glm::vec2 walkerPos;
      glm::vec2 start;
      glm::vec2 end;
      int rows;
      int amount;
      std::vector<Cell> visitedStack;
      Time* timer = new Time();
      bool generateDone;
      bool done;
      void Paint(Dir dir);
};

#endif // SCENE_H
