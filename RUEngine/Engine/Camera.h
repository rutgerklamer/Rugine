#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraMovement
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const GLfloat YAW = -90.f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 4.0f;
const GLfloat SENSITIVITY = 0.05f;
const GLfloat ZOOM = 45.0f;

class Camera
{
    public:
        Camera(glm::vec3 position = glm::vec3( 0.01f, 0.01f, 0.01f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW,
        GLfloat pitch = PITCH): front(glm::vec3(0.0f,0.0f,-1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
        {
          this->position = position;
          this->worldUp = up;
          this->yaw = yaw;
          this->pitch = pitch;
          this->updateCameraVector();
        }

        Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
        {
          this->position = glm::vec3(posX, posY, posZ);
          this->worldUp = glm::vec3(upX, upY, upZ);
          this->yaw = yaw;
          this->pitch = pitch;
          this->updateCameraVector();
        }

        virtual ~Camera()
        {

        }

        glm::mat4 getViewMatrix()
        {
          //Return the view matrix
          return glm::lookAt(this->position, this->position + this->front, this->up);
        }

        glm::mat4 getProjectionMatrix()
        {
          return glm::perspective(this->getZoom(), (GLfloat) 1024 / (GLfloat) 720, 0.1f, 1000.0f);
        }
        glm::vec3 getPosition()
        {
          //return position
          return this->position;
        }

        void setPosition(glm::vec3 pos)
        {
          //Set position
          this->position = pos;
        }

        float getYaw(){
          return this->yaw;
        }
        float getPitch(){
          return this->pitch;
        }
        glm::vec3 getFront()
        {
          //Get front
          return glm::vec3(front);
        }
        glm::vec3 getRight()
        {
          //Get right vector
          return glm::vec3(right);
        }

        glm::vec3 getUp()
        {
          //get up vector
          return this->up;
        }

        void processKeyboard(CameraMovement direction, GLfloat deltaTime)
        {
          //Move
          GLfloat velocity = this->movementSpeed * deltaTime;
          if (FORWARD == direction)
          {
            this->position += this->front * 3.0f * velocity;
          }
          if (BACKWARD == direction)
          {
            this->position -= this->front * 3.0f * velocity;
          }
          if (LEFT == direction)
          {
            this->position -= this->right * 3.0f * velocity;
          }
          if (RIGHT == direction)
          {
            this->position += this->right * 3.0f * velocity;
          }
        }

        void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
        {
          //change pitch and yaw
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
        void processMouseScroll(GLfloat yOffset)
        {
          //Enable scrolling
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
        GLfloat getZoom()
        {
          return this->zoom;
        }
        void invertPitch()
        {
            this->pitch = -this->pitch;
        }

    protected:
    private:
      glm::vec3 position;
      glm::vec3 front;
      glm::vec3 up;
      glm::vec3 right;
      glm::vec3 worldUp;

      GLfloat yaw;
      GLfloat pitch;
      GLfloat movementSpeed;
      GLfloat mouseSensitivity;
      GLfloat zoom;

      float xOff,
            yOff;

      void updateCameraVector()
      {
        //Calculate the right, front and up vectors
        glm::vec3 front;
        front.x = cos(glm::radians(this->yaw)) * cos(glm::radians (this->pitch));
        front.y = sin(glm::radians(this->pitch));
        front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

        this->front = glm::normalize(front);

        this->right = glm::normalize(glm::cross(this->front, this->worldUp));
        this->up = glm::normalize(glm::cross(this->right, this->front));
      }
};

#endif // CAMERA_H
