#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include "Input.h"
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Maths/Time.h"
#include "ResourceManager.h"
#include "SceneManager.h"

class Display
{
    public:
      /**
              *  Constructor.
              */
        Display();
        /**
                *  Destructor.
                */
        virtual ~Display();
        /**
                *  Initialize glfw.
                */
        void initGlfw();
        /**
                *  Initialize glew (The OpenGL Extension Wrangler Library)
                */
        void initGlew();
        /**
                *  unlimited loop till we close the glfwWindow.
                */
        void gameLoop();
        /**
                *  Add a scene to the vector off scenes so we can run them.
                */
        void addScene(Superscene* scene);
        /**
                *  return the window we created
                */
        GLFWwindow* getWindow();
        Input* input;
    private:
      GLFWwindow* window;
      Renderer* renderer;
      Shader* shader;
      Shader* shaderNormals;
      Shader* shaderExplode;
      Shader* shaderSkybox;
      Shader* shaderReflection;
      Camera camera;
      Time* dtime;
      SceneManager* scenemanager;
      ResourceManager* resourcemanager;
      int currentscene;
      std::vector<Superscene*> scenes;
      struct WINDOWINFO
      {
        std::string windowName = "RUEngine 2.0";
        int windowWidth = 1024;
        int windowHeight = 720;
        int majorVersion = 3;
        int minorVersion = 3;
      };
      WINDOWINFO windowinfo;
};

#endif // DISPLAY_H
