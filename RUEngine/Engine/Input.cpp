#include "Input.h"

Camera* Input::camera;

bool Input::keys[1024];
bool Input::mouseKeys[7];
bool Input::firstMouse = true;

int Input::lastX;
int Input::lastY;

Input::Input()
{
  std::cout << "Input initialized" << std::endl;
}

Input::~Input()
{
  delete camera;
}

bool Input::isDown(int key)
{
  return keys[key];
}

bool Input::isMouseDown(int key)
{
  return mouseKeys[key];
}

void Input::setMouseKey(int key, bool active)
{
  mouseKeys[key] = active;
}

void Input::setKey(int key, bool active)
{
  keys[key] = active;
}

void Input::setCamera(Camera* camera)
{
  this->camera = camera;
}


glm::vec2 Input::getMousePosition(GLFWwindow* window)
{
  double dx, dy;
  glfwGetCursorPos(window, &dx, &dy);

  int x = static_cast<int>(floor(dx));
  int y = static_cast<int>(floor(dy));

  glm::vec2 mousepos;
  mousepos.x = x;
  mousepos.y = y;


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
      }
      else if (GLFW_RELEASE == action) {
          keys[key] = false;
      }
  }
}

void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action) {
        mouseKeys[button] = true;
    }
    else {
        mouseKeys[button] = false;
    }
}

void Input::mouseCallBack(GLFWwindow* window, double xPos, double yPos)
{
  if (firstMouse) {
      lastX = xPos;
      lastY = yPos;
      firstMouse = false;
  }
  GLfloat xOffset = xPos - lastX;
  GLfloat yOffset = lastY - yPos;

  lastX = xPos;
  lastY = yPos;

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
