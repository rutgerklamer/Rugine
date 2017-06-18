#ifndef SCENE3_H
#define SCENE3_H

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

class Scene3 : public Superscene
{
    public:
        Scene3(Input* ip);
        virtual ~Scene3();
        void Update(float deltaTime);
    private:
      Entity* mesh;
      Light* light;
};

#endif // SCENE3_H
