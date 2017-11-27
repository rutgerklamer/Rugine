#include "Input.h"

Camera* Input::camera;

bool Input::keys[1024];
bool Input::keysDown[1024];
bool Input::keysUp[1024];
bool Input::mouseKeys[7];
bool Input::mouseKeysDown[7];
bool Input::mouseKeysUp[7];
bool Input::firstMouse = true;

float Input::lastX;
float Input::lastY;
float Input::currentX;
float Input::currentY;

Input::Input()
{
  std::cout << "Input initialized" << std::endl;
}

Input::~Input()
{
  delete camera;
}

Camera* Input::getCamera()
{
  return this->camera;
}

void Input::setWindow(GLFWwindow* window)
{
  this->window = window;
}

bool Input::isDown(int key)
{
  return keys[key];
}

bool Input::isMouseDown(int key)
{
  return mouseKeys[key];
}

void Input::Update(float deltaTime)
{
  for (unsigned int i = 0; i < 1024; i++) {
    keysDown[i] = false;
    keysUp[i] = false;
  }
  for (unsigned int i = 0; i < 7; i++) {
    mouseKeysDown[i] = false;
    mouseKeysUp[i] = false;
  }
}

bool Input::getMouseKeyDown(int key)
{
  return mouseKeysDown[key];
}
bool Input::getMouseKeyUp(int key)
{
  return mouseKeysUp[key];
}
bool Input::getKeyDown(int key)
{
  return keysDown[key];
}
bool Input::getKeyUp(int key)
{
  return keysUp[key];
}

void Input::setMouseKey(int key, bool active)
{
  mouseKeys[key] = active;
}

void Input::setKey(int key, bool active)
{
  keys[key] = active;
}

glm::vec2 Input::getMouseVelocity()
{
  glm::vec2 lastMouse = glm::vec2(lastX, lastY);
  lastX = currentX;
  lastY = currentY;
  return lastMouse - glm::vec2(currentX, currentY);
}
void Input::setCamera(Camera* camera)
{
  this->camera = camera;
}

glm::vec2 Input::getWindowSize()
{
  int width;
  int height;
  glfwGetWindowSize(window, &width, &height);
  return glm::vec2(width, height);
}

glm::vec2 Input::getMousePosition()
{
  double dx, dy;
  glfwGetCursorPos(window, &dx, &dy);

  float x = dx;
  float y = dy;

  glm::vec2 mousepos;
  mousepos.x = x;
  mousepos.y = y;
  currentMouse = mousepos;
  return mousepos;
}

void Input::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key >= 0 && key < 1024) {
      if (GLFW_PRESS == action) {
          keys[key] = true;
          keysDown[key] = true;
      }
      else if (GLFW_RELEASE == action) {
          keys[key] = false;
          keysUp[key] = true;
      }
  }
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action) {
        mouseKeys[button] = true;
        mouseKeysDown[button] = true;
    }
    else {
        mouseKeys[button] = false;
        mouseKeysUp[button] = true;
    }
}

void Input::mouseCallBack(GLFWwindow* window, double xPos, double yPos)
{
  if (firstMouse) {
      lastX = xPos;
      lastY = yPos;
      firstMouse = false;
  }
  lastX = currentX;
  lastY = currentY;
  GLfloat xOffset = xPos - currentX;
  GLfloat yOffset = currentY - yPos;

  currentX = xPos;
  currentY = yPos;
  camera->processMouseMovement(xOffset, yOffset);
}

void Input::doMovement(float deltaTime)
{
  if (keys[GLFW_KEY_TAB]) {
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  if(keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
  {
  	camera->processKeyboard(FORWARD, deltaTime);
  }
  if(keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
  {
  	camera->processKeyboard(BACKWARD, deltaTime);
  }
  if(keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
  {
  	camera->processKeyboard(LEFT, deltaTime);
  }
  if(keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
  {
  	camera->processKeyboard(RIGHT, deltaTime);
  }
}
