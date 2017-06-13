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
#include "Demos/Scene.h"
#include "Demos/Scene0.h"
#include "Demos/Scene1.h"
#include "Maths/Time.h"
#include "ResourceManager.h"

class Display
{
    public:
        Display();
        virtual ~Display();
        void initGlfw();
        void initGlew();
        GLFWwindow* getWindow();
    private:
      GLFWwindow* window;
      Input* input;
      Renderer* renderer;
      Shader* shader;
      Shader* shaderNormals;
      Shader* shaderExplode;
      Camera camera;
      Scene* scene;
      Scene0* scene0;
      Scene1* scene1;
      Time* dtime;
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
        unsigned int fullscreen  = 1;
        unsigned int vsync       = 1;
        unsigned int cursor      = 1;
        unsigned int stereo      = 1;
        unsigned int debug       = 1;
        unsigned int robust      = 1;
      };
      WINDOWINFO windowinfo;
};

#endif // DISPLAY_H
