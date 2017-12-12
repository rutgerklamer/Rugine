#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <vector>

#include "Engine/Superscene.h"
#include "Engine/Input.h"
#include "Engine/ResourceManager.h"
#include "Engine/Shader.h"

class SceneManager
{
    public:
      /**
          *  Constructor
          */
        SceneManager(Input* input, ResourceManager* rm, Shader* s);
        /**
            *  Destructor
            */
        virtual ~SceneManager();
        /**
            *  //TODO Use this or remove it!
            */
        void nextScene();
        void prevScene();
        void checkState();
        std::vector<Superscene*> scenes;
        int currentscene;
    private:
      Input* input;
      ResourceManager* resourcemanager;
      Shader* shader;
};

#endif // SCENEMANAGER_H
