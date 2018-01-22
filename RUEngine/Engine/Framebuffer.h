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
          * Constructor
          * Takes in a const char*, this is the path where the vertex shader for this framebuffer is located //TODO Give default value
          * Takes in a const char*, this is the path where the fragment shader for this framebuffer is located //TODO Give default value?
          */
        Framebuffer(const char* vertexPath, const char* fragmentPath);
        /**
            * Destructor
            */
        virtual ~Framebuffer();
        /**
            * Setup a custom framebuffer
            */
        void initFramebuffer();

        Shader* shader;
        GLuint fbo;
        GLuint rbo;
        GLuint framebufferTexture;
        GLuint watermark;
    private:
};

#endif // FRAMEBUFFER_H
