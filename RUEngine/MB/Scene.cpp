#include "Scene.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iterator>

Scene::Scene(Input* input) : Superscene(input)
{
      rt = new RailTrack();
      camera->setMouseMovement(false );
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

      mirror = new Entity();
      mirror->LoadObject("Assets/untitled.obj", false);
      mirror->scale  = glm::vec3(15,5,25);
      mirror->setColor(glm::vec3(0,0,1));
      mirror->position = glm::vec3(12,3,0);
      mirror->eularAngles = glm::vec3(0,60,0);

      mirror->reflective = true;
      this->addChild(mirror);

      setGamma(0.5f);
      setExposure(0.3f);

      bullet = new Bullet(glm::vec3(1,1,1));

      //addFramebuffer("Shaders/Framebuffer/Pixelization/shader.vert", "Shaders/Framebuffer/Pixelization/shader.frag");

        rt->path.points = { {10,-20}, {10, 10}, {-20,50}, {-15,25}};

      for (unsigned int i = 0; i < rt->path.points.size() ; i++) {
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
      for(unsigned int i = 0; i < rt->path.points.size();i++) {
        Entity* point = new Entity();
        point->LoadObject("Assets/untitled.obj", false);
        point->setColor(glm::vec3(1,1,1));
        point->scale = glm::vec3(2,2,2);
        point->position = glm::vec3(rt->path.points[i].x, 0, rt->path.points[i].y);
        this->addChild(point);
      }
      for (float j = 0.0f; j < rt->path.points.size(); j+= 0.025f)
      {
        Entity* point = new Entity();
        point->LoadObject("Assets/untitled.obj", false);
        point->setColor(glm::vec3(1,0,0));
        point->reflective = true;

        point->position = glm::vec3(rt->path.GetSplinePoint(j, true).x, 0, rt->path.GetSplinePoint(j, true).y);
        this->addChild(point);
      }

}

Scene::~Scene()
{
  delete mesh;
  delete light;
}

void Scene::Update(float deltaTime)
{
  if (deltaTime < 1.0f && deltaTime > -1.0f) {
      t+=(speeds[floor(t)] / 1000.0f) * deltaTime;
    }
      if (t > rt->path.points.size()) {
      t = 0.0f;
    } else if (t < 0) {
      t = rt->path.points.size() - 0.001f;
    }
			mesh->position = glm::vec3(rt->path.GetSplinePoint(t, true).x, 0, rt->path.GetSplinePoint(t, true).y);
      RailTrack::sPoint2D g1 = rt->path.GetSplineGradient(t, true);
      float r = atan2(-g1.y, g1.x);
      glm::vec2 v = this->input->getMousePosition() - glm::vec2(1024/2,720/2);
      if (input->isMouseDown(0)) {
        bullet = new Bullet(glm::normalize(glm::rotateY(glm::vec3(v.x/2.0f,0,v.y/2.0f),-3.1415f/2.0f)) * 150.0f);
        bullets.push_back(bullet);
        bullet->position = mesh->position;
        this->addChild(bullet);
      }

      for (unsigned int i = 0; i < bullets.size(); i++) {
        if (Collision::intersectAABB(bullets[i], mirror)) {
          mirror->setColor(glm::vec3(1,0,0));
          bullets[i]->mirrorDir();
        } else {
          mirror->setColor(glm::vec3(0,0,1));
        }
      }
      if (Collision::intersectAABB(mesh, mirror)) {
        mirror->setColor(glm::vec3(1,0,0));
      } else {
        mirror->setColor(glm::vec3(0,0,1));
      }
      std::cout << mesh->eularAngles.y << std::endl;
      mesh->eularAngles = glm::vec3(0,-atan2(v.y, v.x),0);
      camera->setYawPitch(glm::vec2(30.0f, -45.0f));

      this->camera->setPosition(glm::vec3(mesh->getPosition() - (this->camera->getFront()*120.0f) ));
}
