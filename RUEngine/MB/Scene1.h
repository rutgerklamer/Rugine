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
#include "Engine/Light.h"
#include "Maths/Time.h"
#include "RailTrack.h"
#include "Bullet.h"
#include "Maths/Collision.h"
#include "Mirror.h"
#include "Wall.h"
#include "Enemy.h"
#include "CameraEffects.h"
#include "Maths/Time.h"

class Scene1 : public Superscene
{
    public:
        Scene1(Input* ip);
        virtual ~Scene1();
        void Update(float deltaTime);
        void collisionManager();
        void spawnExplosion(glm::vec3 position);
    private:
      Mirror* mirror;
      RailTrack* rt;
      Entity* mesh;
      Light* light;
      Bullet* bullet;
      Wall* wall;
      CameraEffects* camEffects;
      Enemy* enemy;
      float t;
      std::vector<Bullet*> bullets;
      std::vector<Mirror*> mirrors;
      std::vector<Wall*> walls;
      std::vector<Enemy*> enemies;
      std::vector<float> speeds;
      Time time;

};

#endif // SCENE1_H
