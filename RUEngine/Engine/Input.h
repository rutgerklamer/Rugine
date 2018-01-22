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
          * Constructor
          */
        Input();
        /**
            * Destructor
            */
        virtual ~Input();
        /**
            * Called by glfw, We handle the input by setting the array of keys,
            * To true or false according to the action
            */
        static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
        /**
            * Called by glfw, We handle the input by setting the array of mouse button keys,
            * To true or false according to the action
            */
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        /**
            * Called by glfw, We handle the input by calculating difference between lastY and lastX,
            */
        static void mouseCallBack(GLFWwindow* window, double xPos, double yPos);
        /**
            * Return the position of the mouse in the window
            */
        glm::vec2 getMousePosition();
        /**
            * Return the scale of the window
            */
        glm::vec2 getWindowSize();
        /**
            * Set the pointer of the camera of the scene to the pointer in input
            * Takes in a camera pointer, this is the camera you want to set
            */
        void setCamera(Camera* camera);
         /**
            * Update loop
            * Takes in a float deltaTime, you probably want to use this
            */
        void Update(float deltaTime);
        /**
            * Get the camera
            */
        Camera* getCamera();
        /**
            * Move the camera
            * Takes in deltaTime
            * //TODO Remove
            */
        void doMovement(float deltaTime);
        /**
            * Check if a ket is down or not,
            * Takes in the keycode of the key
            */
        bool isDown(int key);
        /**
            * Set a key to true or false,
            * Takes in the key and a bool to set it to true or false
            */
        void setKey(int key, bool active);
        /**
            * Check if a ket is down or not,
            * Takes in the keycode of the key
            */
        bool isMouseDown(int key);
        /**
            * Set a key to true or false,
            * Takes in the key and a bool to set it to true or false
            */
        void setMouseKey(int key, bool active);
        /**
            * Set the pointer of window to the same as Display
            * Takes in the window we created in Display
            */
        void setWindow(GLFWwindow* window);
        /**
            * Get the mouse velocity, For example for motion blur
            */
        glm::vec2 getMouseVelocity();
         /**
            * Returns if a mouseKey is has just bee pressed
            * Takes in the key you want to check
            */
        bool getMouseKeyDown(int key);
        /**
            * Returns if a mouseKey is has just bee released
            * Takes in the key you want to check
            */
        bool getMouseKeyUp(int key);
         /**
            * Returns if a keyboardKey is has just bee pressed
            * Takes in the key you want to check
            */
        bool getKeyDown(int key);
        /**
            * Returns if a keyboardKey is has just bee released
            * Takes in the key you want to check
            */
        bool getKeyUp(int key);
    private:
      glm::vec2 lastMouse;
      glm::vec2 currentMouse;
      static bool keys[1024];
      static bool keysDown[1024];
      static bool keysUp[1024];
      static bool mouseKeys[7];
      static bool mouseKeysDown[7];
      static bool mouseKeysUp[7];
      static bool firstMouse;
      static float lastX;
      static float lastY;
      static float currentX;
      static float currentY;
      static Camera* camera;
      GLFWwindow* window;
};

#endif // INPUT_H
