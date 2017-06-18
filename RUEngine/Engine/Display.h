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
        Display();
        virtual ~Display();
        void initGlfw();
        void initGlew();
        void gameLoop();
        void addScene(Superscene* scene);
        GLFWwindow* getWindow();
        Input* input;
    private:
      GLFWwindow* window;
      Renderer* renderer;
      Shader* shader;
      Shader* shaderNormals;
      Shader* shaderExplode;
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
