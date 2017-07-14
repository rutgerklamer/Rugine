
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    mat3 normalMatrix = mat3(model);
    normalMatrix = transpose(normalMatrix);
    Normal = normalize(aNormal * normalMatrix);
    Position = vec3(model * vec4(aPos, 1.0));
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}
