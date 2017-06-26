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
      /**
          *  Constructor
          */
        Input();
        /**
            *  Destructor
            */
        virtual ~Input();
        /**
            *  called by glfw, We handle the input by setting the array of keys,
            *  To true or false according to the action.
            */
        static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
        /**
            *  called by glfw, We handle the input by setting the array of mouse button keys,
            *  To true or false according to the action.
            */
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        /**
            *  called by glfw, We handle the input by calculating difference between lastY and lastX,
            */
        static void mouseCallBack(GLFWwindow* window, double xPos, double yPos);
        /**
            *  return the position of the mouse in the window.
            *  takes in the GLFWwindow, so we can call glfwGetCursorPos.
            */
        glm::vec2 getMousePosition(GLFWwindow* window);
        /**
            *  set the pointer of the camera of the scene to the pointer in input.
            */
        void setCamera(Camera* camera);
        /**
            *  Move the camera.
            *  Takes in deltaTime.
            */
        void doMovement(float deltaTime);
        /**
            *  Check if a ket is down or not,
            *  Takes in the keycode of the key.
            */
        bool isDown(int key);
        /**
            *  set a key to true or false,
            *  takes in the key and a bool to set it to true or false.
            */
        void setKey(int key, bool active);
        /**
            *  Check if a ket is down or not,
            *  Takes in the keycode of the key.
            */
        bool isMouseDown(int key);
        /**
            *  set a key to true or false,
            *  takes in the key and a bool to set it to true or false.
            */
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
