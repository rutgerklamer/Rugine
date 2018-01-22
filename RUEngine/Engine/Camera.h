#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
*  States in which the camera can move.
*/
enum CameraMovement
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

/**
* Define preset variables.
*/
const GLfloat YAW = -90.f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 4.0f;
const GLfloat SENSITIVITY = 0.05f;
const GLfloat ZOOM = 45.0f;

class Camera
{
    public:
        /**
            *  Either set the it automatically or set it manual
            *  /see Camera::Camera()
            */
        Camera(glm::vec3 position = glm::vec3( 0.01f, 0.01f, 0.01f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW,
        GLfloat pitch = PITCH): front(glm::vec3(0.0f,0.0f,-1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
        {
          this->position = position;
          this->worldUp = up;
          this->yaw = yaw;
          this->pitch = pitch;
          this->updateCameraVector();
          mouseMovement = true;
          orthographic = false;
          orthoSettings = glm::vec4(-1024.0f/8.0f,1024.0f/8.0f,-720.0f/8.0f,720.0f/8.0f);
        }
        /**
                * set everything Manually
                * takes in a float, this is the X position in 3D space
                * takes in a float, this is the Y position in 3D space
                * takes in a float, this is the Z position in 3D space
                * takes in a float, this is where you want the upX to be
                * takes in a float, this is where you want the upY to be
                * takes in a float, this is where you want the upZ to be
                * takes in a float, this is the yaw you want to start with
                * takes in a float, this is the pitch you want to start with
                */
        Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
        {
          this->position = glm::vec3(posX, posY, posZ);
          this->worldUp = glm::vec3(upX, upY, upZ);
          this->yaw = yaw;
          this->pitch = pitch;
          this->updateCameraVector();
          mouseMovement = true;
          orthographic = false;
          orthoSettings = glm::vec4(-1024.0f/8.0f,1024.0f/8.0f,-720.0f/8.0f,720.0f/8.0f);
        }
        /**
                *  Destructor
                */
        virtual ~Camera()
        {

        }
        /**
                *  Return the view matrix
                */
        glm::mat4 getViewMatrix()
        {
          return glm::lookAt(this->position, this->position + this->front, this->up);
        }
        /**
                *  return the projection or ortho matrix, depending on the orthographic state.
                */
        glm::mat4 getProjectionOrthoMatrix()
        {
          if (orthographic) {
            return glm::ortho(orthoSettings.x, orthoSettings.y, orthoSettings.z, orthoSettings.w ,0.1f,1000.0f);
          } else {
            return glm::perspective(this->getZoom(), (GLfloat) 1024 / (GLfloat) 720, 0.1f, 1000.0f);
          }
        }
       /**
                * return the projection matrix, We need this because soethimes we want the
                * projection matrix when orthographic is true;
                */
        glm::mat4 getProjectionMatrix()
        {
            return glm::perspective(this->getZoom(), (GLfloat) 1024 / (GLfloat) 720, 0.1f, 1000.0f);
        }
        /**
                * return the position in 3D space
                */
        glm::vec3 getPosition()
        {
          return this->position;
        }
        /**
                * Set the orthographic settings
                * takes in a vector 3, size left, size up, size right, size down
                */
        void setOrthoSettings(glm::vec4 settings)
        {
          orthoSettings = settings;
        }
        /**
                *  return the orthographic settings
                */
        glm::vec4 getOrthoSettings()
        {
          return orthoSettings;
        }
        /**
                *  set the position in 3D space
                *  takes in a vector3 of a 3D position
                */
        void setPosition(glm::vec3 pos)
        {
          this->position = pos;
        }

        /**
                *  return yaw
                */
        float getYaw(){
          return this->yaw;
        }
        /**
                *  return pitch
                */
        float getPitch(){
          return this->pitch;
        }
        /**
                *  return front/forward vector of the camera
                */
        glm::vec3 getFront()
        {
          return glm::vec3(front);
        }
        /**
                *  return the right/side vector of the camera
                */
        glm::vec3 getRight()
        {
          return glm::vec3(right);
        }
        /**
                *  return the up.
                */
        glm::vec3 getUp()
        {
          return this->up;
        }
        /**
                *  handle keyboard input to move the camera
                *  Takes in an enum of CameraMovement
                */
        void processKeyboard(CameraMovement direction, GLfloat deltaTime)
        {
          GLfloat velocity = this->movementSpeed * deltaTime;
          if (FORWARD == direction)
          {
            this->position += this->front * 6.0f * velocity;
          }
          if (BACKWARD == direction)
          {
            this->position -= this->front * 6.0f * velocity;
          }
          if (LEFT == direction)
          {
            this->position -= this->right * 6.0f * velocity;
          }
          if (RIGHT == direction)
          {
            this->position += this->right * 6.0f * velocity;
          }
        }
        /**
                *  change the yaw and pitch of the camera according to mouse movement
                *  Takes in the X and Y offset of the mouse calculated by,
                *  /see Input::processMouseMovement()
                */
        void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
        {
          if (mouseMovement) {
          xOffset *= 0.05;
          yOffset *= 0.05;
          yOff += yOffset;
          xOff += xOffset;
          this->yaw += xOffset;
          this->pitch += yOffset;

          if (constrainPitch)
          {
            if (this->pitch >= 89.0f)
            {
              this->pitch = 89.0f;
              yOff = 89.0f;
            }
             else if (this->pitch <= -89.0f)
            {
              this->pitch = -89.0f;
              yOff = -89.0f;
            }
          }
          this->updateCameraVector();
        }
        }
        void setMouseMovement(bool m) {
          mouseMovement = m;
        }
        /**
                *  set the zoom(FOV) of the camera
                *  Takes in the difference calculated by
                *  /see Input::processMouseScroll()
                */
        void processMouseScroll(GLfloat yOffset)
        {
          if (this->zoom >= 1.0f && this->zoom <= 45.0f)
          {
            this->zoom -= yOffset;
          }
          if (this->zoom <= 1.0f)
          {
            this->zoom = 1.0f;
          }
          if (this->zoom >= 45.0f)
          {
            this->zoom = 45.0f;
          }
        }
        /**
                *  return the zoom(FOV) of the camera
                */
        GLfloat getZoom()
        {
          return this->zoom;
        }

        void setYawPitch(glm::vec2 yp)
        {
          this->yaw = yp.x;
          this->pitch = yp.y;
        }
        /**
                *  calculate the new front of the camera according to
                *  The pitch and yaw
                */
        void updateCameraVector()
        {
          glm::vec3 front;
          front.x = cos(glm::radians(this->yaw)) * cos(glm::radians (this->pitch));
          front.y = sin(glm::radians(this->pitch));
          front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

          this->front = glm::normalize(front);

          this->right = glm::normalize(glm::cross(this->front, this->worldUp));
          this->up = glm::normalize(glm::cross(this->right, this->front));
        }
        /**
                *  Invert the pitch, Usefull for reflections of water etc
                */

        void invertPitch()
        {
            this->pitch = -pitch;
        }
        /**
                *  Make the camera projection orthographic
                */
        void setOrthoCam()
        {
          orthographic = true;
        }
         /**
                *  Make the camera projection normal
                */
        void setProjCam()
        {
          orthographic = false;
        }

    protected:
    private:
      glm::vec3 position;
      glm::vec3 front;
      glm::vec3 up;
      glm::vec3 right;
      glm::vec3 worldUp;

      glm::vec4 orthoSettings;

      GLfloat yaw;
      GLfloat pitch;
      GLfloat movementSpeed;
      GLfloat mouseSensitivity;
      GLfloat zoom;
      bool orthographic;

      bool mouseMovement;

      float xOff,
            yOff;

};

#endif // CAMERA_H
