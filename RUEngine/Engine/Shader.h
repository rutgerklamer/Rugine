#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>

class Shader
{
public:
    GLuint shaderProgram;
    /**
        * Constructor
        * Takes in 5 paths in this order: Vertex Shader,
        Fragment Shader,
        Geometry Shader,
        Tessellation Control Shader,
        Tessellation Evaluation Shader, 
        Geometry Shader
        */
    Shader(const char* vertexPath = "Shaders/shader.vert", const char* fragmentPath = "Shaders/shader.frag", const char* tessellationControlPath = "Shaders/shader.tcs", const char* tessellationEvaluationPath = "Shaders/shader.tes", const char* geometryPath = "Shaders/shader.geom");
    /**
        * Destructor
        */
    ~Shader();
    /**
        * Returns a string of a loaded shaderfile
        * Takes in a shaderpath
        */
    std::string readShader(const char* shaderPath);
    GLuint vao;

    void Use();
};

#endif
