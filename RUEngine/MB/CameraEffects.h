#ifndef CAMERAEFFECTS_H
#define CAMERAEFFECTS_H

#include "Engine/Entity.h"
#include "Engine/Camera.h"
#include "Maths/Time.h"

class CameraEffects : public Entity
{
public:
    /**
        * Constructor
        * Takes in a Camera* c, this is the camera we want to pull the effects on
        * Takes in Entity* p, This is the player we need for checking
        */
    CameraEffects(Camera* c, Entity* p);
    /**
        * Destructor
        */
    ~CameraEffects();
    /** 
        * Update, part of Rugine
        * Takes in float deltaTime, you probably want to use this
        */
    virtual void update(float deltaTime);
    /** 
        * Pull of a transition to 3D
        */
    void transition3D();
    /** 
        * Pull of a transition to 2D
        */
    void transition2D();
    /**
        * Check if the level is loaded
        */
    void levelLoaded();
    /** 
        * Check if the transaction is finished and we can load a new level
        */
    bool loadLevel();
    /** 
        * Check if the transaction is finished and we can play
        */
    bool getCanPlay();
    /** 
        * Get the height of the camera
        */
    float getCamHeight();
private:
  Camera* cam;
  Entity* player;
  glm::vec4 orthoCameraViewMain;
  glm::vec4 orthoCameraView;
  float camPosY3D;
  bool is3D;
  bool nextLevel;
  glm::vec2 front;
  bool canLoad;
  bool showMap;
  bool canPlay;
};

#endif
