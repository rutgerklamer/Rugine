#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "glfw3.h"

#include "Engine/Superscene.h"
#include "Engine/Input.h"
#include "Engine/ResourceManager.h"
#include "Engine/Shader.h"

class SceneManager
{
    public:
      /**
          * Constructor
          */
        SceneManager(Input* input, ResourceManager* rm, Shader* s);
        /**
            * Destructor
            */
        virtual ~SceneManager();
        /**
            * Switch to next scene in the scenes list
            */
        void nextScene();
        /**
            * Switch to previous scene in the scenes list
            */
        void prevScene();
        /**
            * Delete the current scene
            */
        void destroyScene();
         /**
            * Update loop called to check what the state of the current scene is
            */
        void checkState();
		/**
			* Set the pointer of window to the same as Display
			* Takes in the window we created in Display
			*/
		void setWindow(GLFWwindow* _window);
        std::vector<Superscene*> scenes;
        int currentscene;
    private:
      Input* input;
      ResourceManager* resourcemanager;
      Shader* shader;
	  GLFWwindow* window;
};

#endif // SCENEMANAGER_H
