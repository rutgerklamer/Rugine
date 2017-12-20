#include "CameraEffects.h"

CameraEffects::CameraEffects(Camera* c, Entity* p) : Entity()
{
  cam = c;
  cam->setMouseMovement(false);
  cam->setProjCam();
  orthoCameraViewMain = cam->getOrthoSettings();
  orthoCameraView = orthoCameraViewMain/100.0f;
  camPosY3D = 7.5f;
  player = p;
  is3D = true;
  front = glm::vec2(0.0f,90.0f);
  canLoad = false;
  showMap = false;
  canPlay = false;
  nextLevel = false;
}

CameraEffects::~CameraEffects()
{

}

bool CameraEffects::getCanPlay()
{
  return canPlay;
}

float CameraEffects::getCamHeight()
{
  return camPosY3D;
}

void CameraEffects::update(float deltaTime)
{
  if (!showMap && camPosY3D < 160.0f ) {
    camPosY3D *= 1.01f;
  } else if (is3D) {
    showMap = true;
  }
  if (showMap) {
    if (front.y > -89.0f) {
      front.y-=1.0f;
    }
    if (front.x < 180.0f) {
      front.x+=1.0f;
    } else if (front.y <= -89.0f) {
      is3D = false;
    }
  }

  if (!is3D && camPosY3D > 10.0f) {
    camPosY3D /= 1.1f;
  } else if (!is3D) {
    cam->setOrthoCam();
    if (orthoCameraView.y < orthoCameraViewMain.y) {
      camPosY3D = 10.0f;
      orthoCameraView *= 1.1f;
    } else {
      canPlay = true;
    }
  }
  if (is3D) {
      if (orthoCameraView.y > 0.5f) {
      nextLevel = false;
      orthoCameraView /= 1.005f;
    } else {
      nextLevel = true;
    }
  }
  cam->setYawPitch(front);
  cam->setOrthoSettings(orthoCameraView);
  cam->setPosition(glm::vec3(player->getPosition() - (this->cam->getFront()*camPosY3D) ));
}

void CameraEffects::transition3D()
{
  canLoad = false;
  orthoCameraView = orthoCameraViewMain;
  is3D = true;
}
void CameraEffects::transition2D()
{
  is3D = false;
}

void CameraEffects::levelLoaded()
{
  canLoad = false;
}

bool CameraEffects::loadLevel()
{
  return nextLevel;
}
