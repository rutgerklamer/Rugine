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

void Superscene::addChild(Mesh* mesh)
{
  meshes.push_back(mesh);
}

void Superscene::addLight(Mesh* light)
{
  meshes.push_back(light);
  lights.push_back(light);
}

void Superscene::Update(float deltaTime)
{

}
