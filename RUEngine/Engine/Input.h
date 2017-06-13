#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include "glfw3.h"
#include "math.h"

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Input
{
    public:
        Input();
        virtual ~Input();
        static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void mouseCallBack(GLFWwindow* window, double xPos, double yPos);
        glm::vec2 getMousePosition(GLFWwindow* window);
        void setCamera(Camera* camera);
        void doMovement(float deltaTime);
        bool isDown(int key);
        void setKey(int key, bool active);
        bool isMouseDown(int key);
        void setMouseKey(int key, bool active);
    private:
      static bool keys[1024];
      static bool mouseKeys[7];
      static bool firstMouse;
      static int lastX;
      static int lastY;
      static Camera* camera;

};

#endif // INPUT_H
