
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
      mesh->make2D();
      mesh->scale  = glm::vec3(0.2f,0.2f,1.0f);
      mesh->setColor(glm::vec3(1,1,1));
      this->addChild(mesh);



      setGamma(0.5f);
      setExposure(0.3f);

      bullet = new Bullet(glm::vec3(1,1,1));

      //addFramebuffer("Shaders/Framebuffer/Pixelization/shader.vert", "Shaders/Framebuffer/Pixelization/shader.frag");

        rt->path.points = { {100,200}, {100, 100}, {200,500}, {200,140}, {250,300}, {400,150}, {100,420}, {420,500}, {400,420}, {200,500}, {500,240}, {20,50}, {15,25}};

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
        point->make2D();
        point->setColor(glm::vec3(0,0,1));
        point->scale = glm::vec3(0.01f,0.01f,1.0f);
        point->position = glm::vec3(rt->path.points[i].x, rt->path.points[i].y , 0.0f);
        this->addChild(point);
      }
      for (unsigned int i = 0; i < rt->path.points.size(); i++ ) {
        if (i%2) {
          mirror = new Mirror(10.0f*i,-10.0f*i,false, glm::vec3(rt->path.GetSplinePoint(i, true).x,0,rt->path.GetSplinePoint(i, true).y));
        } else {
          mirror = new Mirror(10.0f*i,-10.0f*i,true, glm::vec3(rt->path.GetSplinePoint(i, true).x,0,rt->path.GetSplinePoint(i, true).y));
        }
        mirror->position = glm::vec3(rt->path.GetSplinePoint(i, true).x ,rt->path.GetSplinePoint(i, true).y,0);
        this->addChild(mirror);
        mirrors.push_back(mirror);
      }

      for (float j = 0.0f; j < rt->path.points.size(); j+= 0.025f)
      {
        Entity* point = new Entity();
        point->make2D();
        point->setColor(glm::vec3(0,0,1));
        point->scale = glm::vec3(0.005f,0.005f,1.0f);
        point->position = glm::vec3(rt->path.GetSplinePoint(j, true).x, rt->path.GetSplinePoint(j, true).y , 0.0f);
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
      t+=(speeds[floor(t)] / 3000.0f) * deltaTime;
    }
      if (t > rt->path.points.size()) {
      t = 0.0f;
    } else if (t < 0) {
      t = rt->path.points.size() - 0.001f;
    }
			mesh->position = (glm::vec3(rt->path.GetSplinePoint(t, true).x, rt->path.GetSplinePoint(t, true).y, 0));
      RailTrack::sPoint2D g1 = rt->path.GetSplineGradient(t, true);
      float r = atan2(-g1.y, g1.x);
      glm::vec2 v = (this->input->getMousePosition() - glm::vec2(mesh->position.x,mesh->position.y));
      if (input->isMouseDown(0)) {
        bullet = new Bullet(glm::vec3(v.x,v.y,0.0f));
        bullets.push_back(bullet);
        bullet->position = mesh->position;
        this->addChild(bullet);
      }
        for (unsigned int j = 0; j < mirrors.size(); j++) {
            if (Collision::intersectAABB(mesh, mirrors[j])) {
              mirrors[j]->setColor(glm::vec3(0,1,0));
              mesh->setColor(glm::vec3(0,1,0));
            } else {
              mirrors[j]->setColor(glm::vec3(0,0,1));
              mesh->setColor(glm::vec3(0,0,1));
      }
    }
      mesh->eularAngles = glm::vec3(0,0,-atan2(v.y, v.x));
}
