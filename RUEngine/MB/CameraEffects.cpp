#include "CameraEffects.h"

CameraEffects::CameraEffects(Camera* c, Entity* p) : Entity()
{
  // Set the camera
  cam = c;
  // You should not be able to move the cam with your mouse so we disable it
  cam->setMouseMovement(false);
  // The camera should use a projection matrix in the beginning
  cam->setProjCam();
  // Store the original orthographic settings of the camera
  orthoCameraViewMain = cam->getOrthoSettings();
  // Make the camera view really small so you donT notice the effect of it changing from projection to orthographic
  orthoCameraView = orthoCameraViewMain/100.0f;
  // Set the camera right above the object
  camPosY3D = 7.5f;
  // Set the player
  player = p;
  // The camera should start in 3D (Projection)
  is3D = true;
  // Set the front direction of the camera
  front = glm::vec2(0.0f,90.0f);
  // set some vars
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
  // Return the height of the cam
  return camPosY3D;
}

void CameraEffects::update(float deltaTime)

{
  // If the camera is right above the player and the map isnT shown
  if (!showMap && camPosY3D < 160.0f ) {
    // Make the camera go up
    camPosY3D *= 1.01f;
  } else if (is3D) {
    // Else the map is shown since the camera is >= 160.0f units above the player
    showMap = true;
  }
  if (showMap) {
    //Make the camera rotate by changing the y axis of the front direction
    if (front.y > -89.0f) {
      front.y-=1.0f;
    }
     //Make the camera rotate by changing the x axis of the front direction
    if (front.x < 180.0f) {
      front.x+=1.0f;
    } else if (front.y <= -89.0f) {
      // If the frontX and frontY has both rotated the maximum amount we can change to orthographic again, so is3D should be false
      is3D = false;
    }
  }

  // If the camera shouldT be 3D anymore and it is still a large amount of units above the player
  if (!is3D && camPosY3D > 10.0f) {
    // Lower the camera
    camPosY3D /= 1.1f;
  } else if (!is3D) {
    // If the camera is right above the player we can change to 2D orthographic view again 
    cam->setOrthoCam();
    if (orthoCameraView.y < orthoCameraViewMain.y) {
      //Change the view size of the orthographic view
      camPosY3D = 10.0f;
      orthoCameraView *= 1.1f;
    } else {
      // If itS the original size again we can play the game since the camera is at the right position
      canPlay = true;
    }
  }
  // When player is at the end of the track we set is3D to true again
  if (is3D) {
    // Make the view size of the orthographic projection small again so we donT notice the change between 2D and 3D
      if (orthoCameraView.y > 0.5f) {
      nextLevel = false;
      orthoCameraView /= 1.005f;
    } else {
      nextLevel = true;
    }
  }
  // We keep setting the front direction of the camera
  cam->setYawPitch(front);
  // We keep setting the settings of the orthographic view
  cam->setOrthoSettings(orthoCameraView);
  // We keep setting the position of the camera to the position of the player minus the front * camPosY3D,
  // so the camera always stays in a invisible ball around the player
  cam->setPosition(glm::vec3(player->getPosition() - (this->cam->getFront()*camPosY3D) ));
}

void CameraEffects::transition3D()
{
  // When transitioning to 3D we canT load the next level
  canLoad = false;
  // Set the orthographic settings again
  orthoCameraView = orthoCameraViewMain;
  // Transit to 3D
  is3D = true;
}
void CameraEffects::transition2D()
{
  // Transit to 2D
  is3D = false;
}

void CameraEffects::levelLoaded()
{
  // Can load next
  canLoad = false;
}

bool CameraEffects::loadLevel()
{
  // We can switch to the next level
  return nextLevel;
}
