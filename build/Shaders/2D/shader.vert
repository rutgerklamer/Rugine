#version 410 core

layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec2 TexCoords;

uniform mat4 model;
out vec2 texCoords;

void main(void)
{
  texCoords = TexCoords;
  gl_Position = model * vec4(Vertices,1);
}
