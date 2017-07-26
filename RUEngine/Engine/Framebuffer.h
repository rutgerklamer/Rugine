#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glfw3.h>

#include "Engine/Shader.h"

class Framebuffer
{
    public:
      /**
          *  Constructor
          */
        Framebuffer(const char* vertexPath, const char* fragmentPath);
        /**
            *  Destructor
            */
        virtual ~Framebuffer();
        /**
            *  Setup a custom framebuffer
            */
        void initFramebuffer();

        Shader* shader;
        GLuint fbo;
        GLuint rbo;
        GLuint framebufferTexture;
    private:
};

#endif // FRAMEBUFFER_H
