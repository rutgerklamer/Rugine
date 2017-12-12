#include "SceneManager.h"

SceneManager::SceneManager(Input* input, ResourceManager* rm, Shader* s)
{
  // currentscene = 0;
  this->input = input;
  this->resourcemanager = rm;
  this->shader = s;
  std::cout << "SceneManager initialized" << std::endl;
}

SceneManager::~SceneManager()
{
  delete input;
}


void SceneManager::nextScene()
{
  if (currentscene < scenes.size() - 1) {
    currentscene++;
    input->setKey(93, false);
    scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
    resourcemanager->removeLights(shader);
  }
}

void SceneManager::prevScene()
{
  if (currentscene > 0) {
    currentscene--;
    input->setKey(91, false);
    scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
    resourcemanager->removeLights(shader);
  }
}

void SceneManager::checkState()
{
  if (scenes[currentscene]->sceneState == Superscene::PREV) {
    prevScene();
  }
  if (scenes[currentscene]->sceneState == Superscene::NEXT) {
    nextScene();
  }
}
