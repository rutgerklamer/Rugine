#ifndef STARTMENU_H
#define STARTMENU_H

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
#include "Maths/Collision.h"

class StartMenu : public Superscene
{
    public:
        StartMenu(Input* ip);
        virtual ~StartMenu();
        void Update(float deltaTime);
    private:
      Entity* start, exit;
      Entity* hud;
      Entity* hud2;  
};

#endif // STARTMENU_H
