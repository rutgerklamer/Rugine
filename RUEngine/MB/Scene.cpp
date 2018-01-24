
#include "Scene.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iterator>

Scene::Scene(Input* input) : Superscene(input)
{
			// Make a new Railtrack
      rt = new RailTrack();
			// Railtrack uses a integer to determine where you are on the railtrack,
			// We want to start in the beginning so setting t to 0.0f
      t = 0.0f;
			// Add a skybox else the scene will be a boringly black
      skybox = new Skybox("Assets/posx.jpg", "Assets/negx.jpg", "Assets/posy.jpg", "Assets/negy.jpg", "Assets/posz.jpg", "Assets/negz.jpg");
      // Add the skybox as a child (rendertarget)
			this->addSkybox(skybox);
			// Start the timer
      time.timer.start();
	
			// Make a entity
      mesh = new Entity();
			// Load a obj to the entity, set the normalmap to false, we don't want one
      mesh->LoadObject("Assets/untitled.obj", false);
			// Give the entity a nice scale
      mesh->scale  = glm::vec3(5.3,5.3,5.3);
			// Give the mesh a color
      mesh->setColor(glm::vec3(0,0,1));
			// Make the mesh reflective
      mesh->reflective = true;
		  // Add the entity as a child (rendertarget)
      this->addChild(mesh);
	
			// Make a cameffects
      camEffects = new CameraEffects(camera, mesh);
			// Add cameffects as a child so it's update get's called
      this->addChild(camEffects);
			
			// Make a wall
      wall = new Wall();
      this->addChild(wall);
      wall->position = glm::vec3(25.0f,0,60.0f);
      wall->scale = glm::vec3(40,1,1);
			// Add it to the list of walls
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

			// Make a mirror, give it a max, min a facing direction and a position
      mirror = new Mirror(10.0f,-10.0f,false, glm::vec3(60.0f,0.0f,100.0f));
      mirror->position = glm::vec3(60.0f,0.0f,100.0f);
      this->addChild(mirror);
			// Add it to the list of mirrors
      mirrors.push_back(mirror);

      mirror = new Mirror(10.0f,-10.0f,true, glm::vec3(-10.0f,0.0f,100.0f));
      mirror->position = glm::vec3(-10.0f,0.0f,100.0f);
      this->addChild(mirror);
      mirrors.push_back(mirror);

			// make a enemy and give it the player
      enemy = new Enemy(mesh);
      enemy->LoadObject("Assets/untitled.obj", false);
      enemy->scale  = glm::vec3(5.3,5.3,5.3);
      enemy->setColor(glm::vec3(1,0,0));
      enemy->position = glm::vec3(30,0,80);
      enemy->reflective = true;
      this->addChild(enemy);
			// Add it to the list of enemies
      enemies.push_back(enemy);

      Enemy* e = new Enemy(mesh);
      e->LoadObject("Assets/untitled.obj", false);
      e->scale  = glm::vec3(5.3,5.3,5.3);
      e->setColor(glm::vec3(1,0,0));
      e->position = glm::vec3(20.0f,0.0f,130.0f);
      e->reflective = true;
      this->addChild(e);
      enemies.push_back(e);

			// TODO remove this, not needed for reflective shaders
      setGamma(0.5f);
      setExposure(0.3f);
			
			// TODO remove this 
      bullet = new Bullet(glm::vec3(1,1,1), Bullet::PLAYER);


      //addFramebuffer("Shaders/Framebuffer/Pixelization/shader.vert", "Shaders/Framebuffer/Pixelization/shader.frag");
			
			// Give the path some points
	  rt->path.points = { {0,0}, {0,50}, {70,50}, {70,80}, {50,80}, {50,70}, {0,70}, {0,150}, {50,150}, {50,180}, {0,0}, {0,0} };
		
      for (unsigned int i = 0; i < rt->path.points.size()-1 ; i++) {
				// We need to put the the distance between the current and next point in a vector
				// Because the RailTrack class uses time for the position on the track,
				// If the distance between two points is extremely large the player would go super fast
				// And if the distance between to points is extremely low, the player would go super slow
        speeds.push_back(glm::length(glm::vec2(rt->path.points[i].x,rt->path.points[i].y) - glm::vec2(rt->path.points[i+1].x,rt->path.points[i+1].y)));
      }
			// Get the largest int in the speeds vector
      int largestInt = 0;
      for (unsigned int i = 0; i < speeds.size(); i++) {
        if (speeds[i] > largestInt) {
          largestInt = speeds[i];
        }
      }
      for (unsigned int i = 0; i < speeds.size(); i++) {
				// Try and make the speeds the same for every point
        speeds[i] = largestInt + largestInt - speeds[i];
      }

      for(unsigned int i = 1; i < rt->path.points.size()-2;i++) {
				// Set white points along the defined points in path
        Entity* point = new Entity();
        point->LoadObject("Assets/untitled.obj", false);
        point->setColor(glm::vec3(1,1,1));
        point->scale = glm::vec3(2,2,2);
        point->position = glm::vec3(rt->path.points[i].x, 0, rt->path.points[i].y);
        this->addChild(point);
      }

      for (float j = 0.0f; j < rt->path.points.size()-4 ; j+= 0.025f)
      {
				// Set red points between all the points to simulate a path
        Entity* point = new Entity();
        point->LoadObject("Assets/untitled.obj", false);
        point->setColor(glm::vec3(1,0,0));
        point->reflective = true;
        point->position = glm::vec3(rt->path.GetSplinePoint(j, false).x, 0, rt->path.GetSplinePoint(j, false).y);
        this->addChild(point);
      }
}

Scene::~Scene()
{
	// cleanup
}

void Scene::Update(float deltaTime)
{
	// We don't want to add deltaTime if itS too large ( this can happen if loading a large OBJ or texture )
  if (deltaTime < 1.0f && deltaTime > -1.0f && camEffects->getCanPlay()) {
			// Adjust the deltaTime to fix the speeds of the current point
      t+=(speeds[floor(t)] / 500.0f) * deltaTime;
    }
    if (t >= rt->path.points.size()-4) {
				// At the end make a transition to 3D
    		camEffects->transition3D();
				// Stay at this point
    		t = rt->path.points.size()-4;
    }
    if (camEffects->loadLevel() && t >= rt->path.points.size()-4) {
			// Switch to next level is camera is done and player still is at the end of the level
      sceneState = Superscene::NEXT;
    }
			// Set the player on the correct point on track
			mesh->position = glm::vec3(rt->path.GetSplinePoint(t, false).x, 0, rt->path.GetSplinePoint(t, false).y);
     // RailTrack::sPoint2D g1 = rt->path.GetSplineGradient(t, true);
     // float r = atan2(-g1.y, g1.x);
				// Get the angle between the mouse position and the center of the screen
        glm::vec2 v = this->input->getMousePosition() - glm::vec2(1024/2,720/2);
				// Set the rotation by using atan2
        mesh->eularAngles = glm::vec3(0,-atan2(v.y, v.x),0);
        if (input->isMouseDown(0)) {
					// If we press the mouse, shoot a bullet in that direction from the center of the player
          bullet = new Bullet(glm::normalize(glm::rotateY(glm::vec3(-1,0,-1),-atan2(v.y, v.x) - (3.1415f/4.0f))) * 100.0f, Bullet::PLAYER);
          bullets.push_back(bullet);
          bullet->position = mesh->position;
          this->addChild(bullet);
      }

      for (unsigned int i = 0; i < enemies.size();i++) {
				// Get all the bullets from the list of bullets from all entities
				// TODO Inprove this
        std::vector<Bullet*>::iterator it = enemies[i]->bullets.begin();
        while(it != enemies[i]->bullets.end()) {
              bullets.push_back(*it);
              this->addChild(*it);
              it = enemies[i]->bullets.erase(it);
          }
      }
			// Lastly check for all collisions
      collisionManager();
}

void Scene::spawnExplosion(glm::vec3 position)
{
  for (unsigned int i = 0; i < 500; i++) {
		// Spawn bullets in 360 around the player ( x and z axis only )
    bullet = new Bullet(glm::vec3(sin(i) * 30.0f, 0 , cos(i)*30.0f), Bullet::PLAYER);
    bullets.push_back(bullet);
    bullet->setColor(glm::vec3(i/50.0f,0,0));
    bullet->position = position;
    this->addChild(bullet);
  }
}

void Scene::collisionManager()
{
	// Check if a bullet collides with a wall and delete the bullet if so
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

	// If a bullet with the origin of the player hits a enemy, delete that enemy
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
		
		// If a bullet with the origin of a enemy hits the player, change spawn particle explosion, disable our players rendering and close the app after timer has expired
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

	// If a bullet hits a mirror, Check if the mirrors orientation and change the direction of the bullet 
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
