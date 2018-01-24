#include "SceneManager.h"

SceneManager::SceneManager(Input* input, ResourceManager* rm, Shader* s)
{
  currentscene = 0;
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
    scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
    resourcemanager->removeLights(shader);
  }
}

void SceneManager::prevScene()
{
  if (currentscene > 0) {
    currentscene--;
    scenes[currentscene]->input->setCamera(scenes[currentscene]->camera);
    resourcemanager->removeLights(shader);
  }
}

void SceneManager::destroyScene()
{
  glfwSetWindowShouldClose(window, GL_TRUE);
  Superscene* temp = scenes[currentscene];
  scenes.erase(scenes.begin() + currentscene);
  delete temp;
  if (currentscene == scenes.size()) {
    currentscene--;
  }
}

void SceneManager::setWindow(GLFWwindow* _window)
{
	this->window = _window;
}

void SceneManager::checkState()
{
  if (scenes[currentscene]->sceneState == Superscene::PREV) {
    prevScene();
  }
  std::cout << scenes[currentscene]->sceneState << std::endl;
  if (scenes[currentscene]->sceneState == Superscene::NEXT) {
    nextScene();
  }
  if (scenes[currentscene]->sceneState == Superscene::DESTROY) {
    destroyScene();
  }
}
