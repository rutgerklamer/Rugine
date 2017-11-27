#version 330 core
layout (location = 0) in vec3 Vertices;

out vec3 TexCoords;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords = Vertices;
    vec4 pos = proj * view * vec4(Vertices, 1.0);
    gl_Position = pos.xyww;
}
