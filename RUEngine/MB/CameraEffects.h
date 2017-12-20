#ifndef CAMERAEFFECTS_H
#define CAMERAEFFECTS_H

#include "Engine/Entity.h"
#include "Engine/Camera.h"
#include "Maths/Time.h"

class CameraEffects : public Entity
{
public:
    CameraEffects(Camera* c, Entity* p);
    ~CameraEffects();

    virtual void update(float deltaTime);
    void transition3D();
    void transition2D();
    void levelLoaded();
    bool loadLevel();
    bool getCanPlay();
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
