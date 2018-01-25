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
#include "Wall.h"
#include "Enemy.h"
#include "CameraEffects.h"
#include "Maths/Time.h"

class Scene : public Superscene
{
    public:
        /** 
           * Scene, part of Rugine
           * Takes in Input* ip, This is sent to the Superscene
           */
        Scene(Input* ip);
        /**
           * Destructor
           */
        virtual ~Scene();
        /** 
           * Update, part of Rugine
           * Takes in float deltaTime, you probably want to use this
           */
        void Update(float deltaTime);
        /**
            * Checks for collisions in the game and reacts to it
            */
        void collisionManager();
        /**
            * Spawn an explosion of blocks
            * Takes in glm::vec3 position, This is the position where you want to spawn the explosion
            */
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
	  Time deathTimer;
};

#endif // SCENE_H
