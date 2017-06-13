#include "Superscene.h"

Superscene::Superscene(Input* input)
{
  this->input = input;
  camera = new Camera();
  std::cout << "Superscene initialized" << std::endl;
}

Superscene::~Superscene()
{
  delete input;
  delete camera;
}

void Superscene::addChild(Entity* mesh)
{
  entities.push_back(mesh);
}

void Superscene::addLight(Light* light)
{
  entities.push_back(light);
  lights.push_back(light);
}

void Superscene::Update(float deltaTime)
{

}
