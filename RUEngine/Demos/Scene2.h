#ifndef SCENE2_H
#define SCENE2_H

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
#include "Engine/Water.h"
#include "Engine/Terrain.h"

class Scene2 : public Superscene
{
    public:
        Scene2(Input* ip);
        virtual ~Scene2();
        void Update(float deltaTime);
    private:
      Terrain* mesh;
      Entity* ball;
      Light* light;
      Water* water;
      float terrainHeightNorm;
};

#endif // SCENE2_H
