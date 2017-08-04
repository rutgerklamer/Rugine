#ifndef SCENE0_H
#define SCENE0_H

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
class Scene0 : public Superscene
{
    public:
        Scene0(Input* input);
        virtual ~Scene0();
        void Update(float deltaTime);
    private:
      Entity* mesh;
      Light* light;
      Water* water;
};

#endif // SCENE0_H
