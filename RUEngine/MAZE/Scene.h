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
    private:
      enum States
      {
        ON,OFF
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
};

#endif // SCENE_H
