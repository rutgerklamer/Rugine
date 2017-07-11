#ifndef SCENE1_H
#define SCENE1_H

#include <iostream>
#include <GL/glew.h>
#include <vector>
#include "glfw3.h"

#include "Engine/Camera.h"
#include "Engine/Mesh.h"
#include "Engine/Entity.h"
#include "Engine/Superscene.h"
#include "Engine/Texture.h"
#include "Maths/Time.h"
#include "Engine/Light.h"
class Scene1 : public Superscene
{
    public:
        Scene1(Input* ip);
        virtual ~Scene1();
        void Update(float deltaTime);
    private:
      Entity* mesh;
      Light* light;
      Light* light2;
};

#endif // SCENE1_H
