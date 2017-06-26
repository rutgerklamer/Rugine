#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <vector>

#include "Engine/Superscene.h"
#include "Engine/Input.h"

class SceneManager
{
    public:
      /**
          *  Constructor
          */
        SceneManager(Input* input);
        /**
            *  Destructor
            */
        virtual ~SceneManager();
        /**
            *  //TODO Use this or remove it!
            */
        void checkUpdate();
        std::vector<Superscene*> scenes;
    private:
      Input* input;
};

#endif // SCENEMANAGER_H
