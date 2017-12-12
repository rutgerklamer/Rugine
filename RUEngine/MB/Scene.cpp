
#include "Scene.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iterator>


Scene::Scene(Input* input) : Superscene(input)
{
      rt = new RailTrack();
      camera->setMouseMovement(false );
      camera->setOrthoCam();
      t = 0.0f;
      skybox = new Skybox("Assets/posx.jpg", "Assets/negx.jpg", "Assets/posy.jpg", "Assets/negy.jpg", "Assets/posz.jpg", "Assets/negz.jpg");
      this->addSkybox(skybox);
      //Create a mesh

      mesh = new Entity();
      mesh->LoadObject("Assets/untitled.obj", false);
      mesh->scale  = glm::vec3(5.3,5.3,5.3);
      mesh->setColor(glm::vec3(0,0,1));
      mesh->reflective = true;
      this->addChild(mesh);

      wall = new Wall();
      this->addChild(wall);
      wall->position = glm::vec3(25.0f,0,60.0f);
      wall->scale = glm::vec3(40,1,1);
      walls.push_back(wall);

      wall = new Wall();
      this->addChild(wall);
      wall->scale = glm::vec3(1,1,10);
      wall->position = glm::vec3(60.0f,0,70.0f);
      walls.push_back(wall);

      wall = new Wall();
      this->addChild(wall);
      wall->scale = glm::vec3(1,1,100);
      wall->position = glm::vec3(-10.0f,0,160.0f);
      walls.push_back(wall);

      wall = new Wall();
      this->addChild(wall);
      wall->scale = glm::vec3(50,1,1);
      wall->position = glm::vec3(-10.0f,0,160.0f);
      walls.push_back(wall);


      wall = new Wall();
      this->addChild(wall);
      wall->scale = glm::vec3(50,1,1);
      wall->position = glm::vec3(50.0f,0,100.0f);
      walls.push_back(wall);

      mirror = new Mirror(10.0f,-10.0f,false, glm::vec3(60.0f,0.0f,100.0f));
      mirror->position = glm::vec3(60.0f,0.0f,100.0f);
      this->addChild(mirror);
      mirrors.push_back(mirror);

      mirror = new Mirror(10.0f,-10.0f,true, glm::vec3(-10.0f,0.0f,100.0f));
      mirror->position = glm::vec3(-10.0f,0.0f,100.0f);
      this->addChild(mirror);
      mirrors.push_back(mirror);

      enemy = new Enemy(mesh);
      enemy->LoadObject("Assets/untitled.obj", false);
      enemy->scale  = glm::vec3(5.3,5.3,5.3);
      enemy->setColor(glm::vec3(1,0,0));
      enemy->position = glm::vec3(30,0,80);
      enemy->reflective = true;
      this->addChild(enemy);
      enemies.push_back(enemy);

      Enemy* e = new Enemy(mesh);
      e->LoadObject("Assets/untitled.obj", false);
      e->scale  = glm::vec3(5.3,5.3,5.3);
      e->setColor(glm::vec3(1,0,0));
      e->position = glm::vec3(20.0f,0.0f,130.0f);
      e->reflective = true;
      this->addChild(e);
      enemies.push_back(e);

      setGamma(0.5f);
      setExposure(0.3f);

      bullet = new Bullet(glm::vec3(1,1,1), Bullet::PLAYER);

      orthoCameraView = camera->getOrthoSettings();

      //addFramebuffer("Shaders/Framebuffer/Pixelization/shader.vert", "Shaders/Framebuffer/Pixelization/shader.frag");

        rt->path.points = { {0,0}, {0,50}, {70,50}, {70,80}, {50,80}, {50,70}, {0,70}, {0,150}, {50,150}, {50,180}};

      for (unsigned int i = 0; i < rt->path.points.size()+1 ; i++) {
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


      std::cout << rt->path.points.size() << std::endl;
      for(unsigned int i = 1; i < rt->path.points.size();i++) {
        Entity* point = new Entity();
        point->LoadObject("Assets/untitled.obj", false);
        point->setColor(glm::vec3(1,1,1));
        point->scale = glm::vec3(2,2,2);
        point->position = glm::vec3(rt->path.points[i].x, 0, rt->path.points[i].y);
        this->addChild(point);
      }

      for (float j = 0.0f; j < rt->path.points.size()-2 ; j+= 0.025f)
      {
        Entity* point = new Entity();
        point->LoadObject("Assets/untitled.obj", false);
        point->setColor(glm::vec3(1,0,0));
        point->reflective = true;
        point->position = glm::vec3(rt->path.GetSplinePoint(j, false).x, 0, rt->path.GetSplinePoint(j, false).y);
        this->addChild(point);
      }

      camPosY3D = 10.0f;
}

Scene::~Scene()
{
  delete mesh;
  delete light;
}

void Scene::Update(float deltaTime)
{
  if (deltaTime < 1.0f && deltaTime > -1.0f) {
      t+=(speeds[floor(t)] / 500.0f) * deltaTime;
    }
      if (t >= rt->path.points.size()-2) {
      t = rt->path.points.size()-2  ;
    } else if (t < 0) {
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

      camera->setYawPitch(glm::vec2(0.0f,-90.0f));
      camera->setOrthoSettings(orthoCameraView);
      camera->setOrthoCam();
      this->camera->setPosition(glm::vec3(mesh->getPosition() - (this->camera->getFront()*160.0f) ));
}

void Scene::collisionManager()
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
