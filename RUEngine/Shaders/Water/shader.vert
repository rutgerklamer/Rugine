#version 410 core
layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec2 texCoords;
out vec3 normals;

void main(void)
{
  mat3 normalMatrix = mat3(model);
  normalMatrix = transpose(normalMatrix);
  normals = normalize(Normals * normalMatrix);

  gl_Position = proj* view * model * vec4(Vertices,1);
  texCoords = TexCoords;
}
