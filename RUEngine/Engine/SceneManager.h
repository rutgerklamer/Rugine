#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <vector>

#include "Engine/Superscene.h"
#include "Engine/Input.h"

class SceneManager
{
    public:
        SceneManager(Input* input);
        virtual ~SceneManager();
        void checkUpdate();
        std::vector<Superscene*> scenes;
    private:
      Input* input;
};

#endif // SCENEMANAGER_H
