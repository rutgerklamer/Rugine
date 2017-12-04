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
#include "RailTrack.h"
#include "Bullet.h"
#include "Maths/Collision.h"
#include "Mirror.h"

class Scene : public Superscene
{
    public:
        Scene(Input* ip);
        virtual ~Scene();
        void Update(float deltaTime);



    private:
      RailTrack* rt;
      Entity* mesh;
      Entity* GUI;
      Light* light;
      Bullet* bullet;
      Mirror* mirror;
      float t;
      std::vector<Bullet*> bullets;
      std::vector<Mirror*> mirrors;
      std::vector<float> speeds;
};

#endif // SCENE_H