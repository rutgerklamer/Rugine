#include "Scene2.h"

Scene2::Scene2(Input* input) : Superscene(input)
{
      std::cout << "Scene2 initialized" << std::endl;
      //Create a mesh
      mesh = new Terrain();
      mesh->LoadTerrain();
    //  mesh->setColor(glm::vec3(1,1,1));
      mesh->setTexture(tex::loadTexture("Assets/dust.jpg"));
      this->addChild(mesh);

      ball = new Entity();
      ball->LoadObject("Assets/untitled.obj", false);
      //Set a texture to it
      ball->setTexture(tex::loadTexture("Assets/szclcdi.png"));
      ball->position = glm::vec3(10,100,10);
      ball->scale = glm::vec3(1,1,1);
      this->addChild(ball);

      light = new Light();
      light->position = glm::vec3(40,10,40);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(1,1,1));
      light->setStrength(500.5f);
      light->setSpecularStrength(0.2f);
     // light->setExtinction(0.0f);
      this->addLight(light);

      setGamma(0.8f);
      setExposure(0.7f);
      for (unsigned int i = 0; i < 256; i++) {
        for (unsigned int j = 0; j < 256; j++) {
          terrainHeightNorm+= mesh->GetTerrainHeight(i,j);
        }
      }
      terrainHeightNorm = terrainHeightNorm / (256*256);
      skybox = new Skybox("Assets/sandtrap_rt.tga", "Assets/sandtrap_lf.tga", "Assets/sandtrap_up.tga", "Assets/sandtrap_dn.tga", "Assets/sandtrap_bk.tga", "Assets/sandtrap_ft.tga");
      this->addSkybox(skybox);
}

Scene2::~Scene2()
{
  delete mesh;
  delete light;
}

void Scene2::Update(float deltaTime)
{
  input->getCamera()->setPosition(glm::vec3(input->getCamera()->getPosition().x, mesh->GetTerrainHeight(input->getCamera()->getPosition().x, input->getCamera()->getPosition().z), input->getCamera()->getPosition().z));
  float up, down, right, left, leftup, leftdown, rightup, rightdown;
  up = mesh->GetTerrainHeight(ball->position.x, ball->position.z + 0.3f);
  down = mesh->GetTerrainHeight(ball->position.x, ball->position.z - 0.3f);
  left = mesh->GetTerrainHeight(ball->position.x - 0.3f, ball->position.z);
  right = mesh->GetTerrainHeight(ball->position.x + 0.3f, ball->position.z);
  leftup = mesh->GetTerrainHeight(ball->position.x - 0.3f, ball->position.z + 0.3f);
  leftdown = mesh->GetTerrainHeight(ball->position.x - 0.3f, ball->position.z - 0.3f);
  rightup = mesh->GetTerrainHeight(ball->position.x + 0.3f, ball->position.z + 0.3f);
  rightdown = mesh->GetTerrainHeight(ball->position.x + 0.3f, ball->position.z - 0.3f);
  glm::vec2 calcvel = glm::vec2(0,0);
  calcvel += glm::vec2(0,0.3) * (terrainHeightNorm + up);
  calcvel += glm::vec2(0,-0.3) * (terrainHeightNorm + down);
  calcvel += glm::vec2(-0.3,0) * (terrainHeightNorm + left);
  calcvel += glm::vec2(0.3,0) * (terrainHeightNorm + right);
  calcvel += glm::vec2(-0.3,0.3) * ((terrainHeightNorm - leftup) );
  calcvel += glm::vec2(-0.3,-0.3) * ((terrainHeightNorm - leftdown) );
  calcvel += glm::vec2(0.3,0.3) * ((terrainHeightNorm - rightup) );
  calcvel += glm::vec2(0.3,-0.3) * ((terrainHeightNorm - rightdown) );
  ball->velocity.x += calcvel.x * 0.3f;
  ball->velocity.z += calcvel.y * 0.3f;
  ball->position.y = mesh->GetTerrainHeight(ball->position.x, ball->position.z) - 42;
  ball->update(deltaTime);
}
