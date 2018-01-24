#include "Scene1.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iterator>

Scene1::Scene1(Input* input) : Superscene(input)
{
      rt = new RailTrack();
      t = 0.0f;
      skybox = new Skybox("Assets/posx.jpg", "Assets/negx.jpg", "Assets/posy.jpg", "Assets/negy.jpg", "Assets/posz.jpg", "Assets/negz.jpg");
      this->addSkybox(skybox);
      //Create a mesh
      time.timer.start();
      mesh = new Entity();
      mesh->LoadObject("Assets/untitled.obj", false);
      mesh->scale  = glm::vec3(5.3,5.3,5.3);
      mesh->setColor(glm::vec3(0,0,1));
      mesh->reflective = true;
      this->addChild(mesh);
      camEffects = new CameraEffects(camera, mesh);
      this->addChild(camEffects);

      setGamma(0.5f);
      setExposure(0.3f);

      bullet = new Bullet(glm::vec3(1,1,1), Bullet::PLAYER);

      wall = new Wall();
      this->addChild(wall);
      wall->position = glm::vec3(100.0f,0,20.0f);
      wall->scale = glm::vec3(20,1,1);
      walls.push_back(wall);

      wall = new Wall();
      this->addChild(wall);
      wall->position = glm::vec3(100.0f,0,22.5f);
      wall->scale = glm::vec3(1,1,17.5f);
      walls.push_back(wall);

      wall = new Wall();
      this->addChild(wall);
      wall->position = glm::vec3(15.0f,0,10.0f);
      wall->scale = glm::vec3(50,1,1);
      walls.push_back(wall);

      wall = new Wall();
      this->addChild(wall);
      wall->position = glm::vec3(125.0f,0,-20.0f);
      wall->scale = glm::vec3(1,1,15);
      walls.push_back(wall);

      wall = new Wall();
      this->addChild(wall);
      wall->position = glm::vec3(132.5f,0,-12.5f);
      wall->scale = glm::vec3(15,1,1);
      walls.push_back(wall);

      mirror = new Mirror(20.0f,-20.0f,false, glm::vec3(100.0f,0.0f,65.0f));
      mirror->position = glm::vec3(100.0f,0.0f,65.0f);
      this->addChild(mirror);
      mirrors.push_back(mirror);

      mirror = new Mirror(25.0f,-25.0f,true, glm::vec3(160.0f,0.0f,25.0f));
      mirror->position = glm::vec3(180.0f,0.0f,25.0f);
      this->addChild(mirror);
      mirrors.push_back(mirror);

      enemy = new Enemy(mesh);
      enemy->LoadObject("Assets/untitled.obj", false);
      enemy->scale  = glm::vec3(5.3,5.3,5.3);
      enemy->setColor(glm::vec3(1,0,0));
      enemy->position = glm::vec3(132.5f,0,-22.5f);
      enemy->reflective = true;
      this->addChild(enemy);
      enemies.push_back(enemy);

      enemy = new Enemy(mesh);
      enemy->LoadObject("Assets/untitled.obj", false);
      enemy->scale  = glm::vec3(5.3,5.3,5.3);
      enemy->setColor(glm::vec3(1,0,0));
      enemy->position = glm::vec3(95.0,0,25.0f);
      enemy->reflective = true;
      this->addChild(enemy);
      enemies.push_back(enemy);

	  rt->path.points = { {0,0}, {-40,0}, {75,0}, {100,0}, {125,0}, {125,30},{100,50}, {75,30},{75,0}, {125,0}, {150,0}, {175,0}, {200,0}, {225,0}, {0,0}, {0,0} };

      for (unsigned int i = 0; i < rt->path.points.size()-1 ; i++) {
        speeds.push_back(glm::length(glm::vec2(rt->path.points[i].x,rt->path.points[i].y) - glm::vec2(rt->path.points[i+1].x,rt->path.points[i+1].y)));
      }
      int largestInt = 0;
      for (unsigned int i = 0; i < speeds.size(); i++) {
        if (speeds[i] > largestInt) {
          largestInt = speeds[i];
        }
      }
      for (unsigned int i = 0; i < speeds.size(); i++) {
        speeds[i] = largestInt + largestInt - speeds[i];
      }

      for(unsigned int i = 1; i < rt->path.points.size()-2;i++) {
        Entity* point = new Entity();
        point->LoadObject("Assets/untitled.obj", false);
        point->setColor(glm::vec3(1,1,1));
        point->scale = glm::vec3(2,2,2);
        point->position = glm::vec3(rt->path.points[i].x, 0, rt->path.points[i].y);
        this->addChild(point);
      }

      for (float j = 0.0f; j < rt->path.points.size()-4 ; j+= 0.025f)
      {
        Entity* point = new Entity();
        point->LoadObject("Assets/untitled.obj", false);
        point->setColor(glm::vec3(1,0,0));
        point->reflective = true;
        point->position = glm::vec3(rt->path.GetSplinePoint(j, false).x, 0, rt->path.GetSplinePoint(j, false).y);
        this->addChild(point);
      }
}

Scene1::~Scene1()
{

}

void Scene1::Update(float deltaTime)
{
  if (deltaTime < 1.0f && deltaTime > -1.0f && camEffects->getCanPlay()) {
      t+=(speeds[floor(t)] / 500.0f) * deltaTime;
    }
      if (t >= rt->path.points.size()-4) {
      camEffects->transition3D();
      t = rt->path.points.size()-4;
    }
    if (camEffects->loadLevel() && t >= rt->path.points.size()-4) {
      sceneState = Superscene::NEXT;
    }
			mesh->position = glm::vec3(rt->path.GetSplinePoint(t, false).x, 0, rt->path.GetSplinePoint(t, false).y);
      RailTrack::sPoint2D g1 = rt->path.GetSplineGradient(t, true);
      float r = atan2(-g1.y, g1.x);
        glm::vec2 v = this->input->getMousePosition() - glm::vec2(1024/2,720/2);
        mesh->eularAngles = glm::vec3(0,-atan2(v.y, v.x),0);
        if (input->isMouseDown(0)) {
          bullet = new Bullet(glm::normalize(glm::rotateY(glm::vec3(-1,0,-1),-atan2(v.y, v.x) - (3.1415f/4.0f))) * 100.0f, Bullet::PLAYER);
          bullets.push_back(bullet);
          bullet->position = mesh->position;
          this->addChild(bullet);
      }

      for (unsigned int i = 0; i < enemies.size();i++) {
        std::vector<Bullet*>::iterator it = enemies[i]->bullets.begin();
        while(it != enemies[i]->bullets.end()) {
              bullets.push_back(*it);
              this->addChild(*it);
              it = enemies[i]->bullets.erase(it);
          }
      }
      collisionManager();
}

void Scene1::spawnExplosion(glm::vec3 position)
{
  for (unsigned int i = 0; i < 500; i++) {
    bullet = new Bullet(glm::vec3(sin(i) * 30.0f, 0 , cos(i)*30.0f), Bullet::PLAYER);
    bullets.push_back(bullet);
    bullet->setColor(glm::vec3(i/50.0f,0,0));
    bullet->position = position;
    this->addChild(bullet);
  }
}

void Scene1::collisionManager()
{
  for (unsigned int j = 0; j < walls.size(); j++)
  {
    std::vector<Bullet*>::iterator it = bullets.begin();
    while(it != bullets.end()) {
    if (Collision::intersectAABB(*it, walls[j])) {
        this->removeChild(*it);
        delete (*it);
        it = bullets.erase(it);
    } else {
      ++it;
    }
  }
  }

  std::vector<Bullet*>::iterator it = bullets.begin();
  while(it != bullets.end()) {

    std::vector<Enemy*>::iterator eit = enemies.begin();
    while (eit != enemies.end()) {
      if (Collision::intersectAABB(*it, *eit) && (*it)->origin == Bullet::PLAYER) {
        this->removeChild(*it);
        delete *it;
        it = bullets.erase(it);
        this->removeChild(*eit);
        delete *eit;
        eit = enemies.erase(eit);
      } else {
        eit++;
      }

    }
    if (Collision::intersectAABB(*it, mesh) && (*it)->origin == Bullet::ENEMY) {
        this->removeChild(*it);
        delete (*it);
        it = bullets.erase(it);
        mesh->setColor(glm::vec3(0,1,0));
    } else if ((*it)->time.timer.seconds() > 4.4f) {
      this->removeChild(*it);
      delete *it;
      it = bullets.erase(it);
    } else {
      ++it;
    }
    }

  for (unsigned int i = 0; i < bullets.size(); i++) {
    for (unsigned int j = 0; j < mirrors.size(); j++) {
    if (Collision::intersectAABB((bullets[i]), mirrors[j])) {
      mirrors[j]->setColor(glm::vec3(1,0,0));
      if (mirrors[j]->checkZ()) {
        (bullets[i])->mirrorDirX();
      } else {
        (bullets[i])->mirrorDirZ();
      }
    } else {
      mirrors[j]->setColor(glm::vec3(0,0,1));
    }
  }
  }

}
