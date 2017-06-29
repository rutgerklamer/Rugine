#include "SceneManager.h"

SceneManager::SceneManager(Input* input)
{
  // currentscene = 0;
  this->input = input;
  std::cout << "SceneManager initialized" << std::endl;
}

SceneManager::~SceneManager()
{
  delete input;
}

void SceneManager::checkUpdate()
{
  if (input->isDown(93) && currentscene < scenes.size() - 1) {
    currentscene++;
    input->setKey(93, false);
    scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
    //resourcemanager->removeLights(shader);
  }
  if (input->isDown(91) && currentscene > 0) {
    currentscene--;
    input->setKey(91, false);
    scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
  //  resourcemanager->removeLights(shader);
  }
}
