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
    Shader(const char* vertexPath = "Shaders/shader.vert", const char* fragmentPath = "Shaders/shader.frag", const char* tessellationControlPath = "Shaders/shader.tcs", const char* tessellationEvaluationPath = "Shaders/shader.tes", const char* geometryPath = "Shaders/shader.geom");
    ~Shader();
    std::string readShader(const char* shaderPath);
    GLuint vao;

    void Use();
};

#endif
