
#version 330 core
layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec2 Coords;
layout (location = 2) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 planeYPosition;

void main()
{
    TexCoords = Coords;
    mat3 normalMatrix = mat3(model);
    normalMatrix = transpose(normalMatrix);
    Normal = normalize(aNormal * normalMatrix);
    Position = vec3(model * vec4(Vertices, 1.0));
    gl_Position = proj * view * model * vec4(Vertices, 1.0);
}
