#version 410 core
layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec2 texCoords;
out vec3 normals;
out vec4 clipSpace;


void main(void)
{
  mat3 normalMatrix = mat3(model);
  normalMatrix = transpose(normalMatrix);
  normals = normalize(Normals * normalMatrix);
  clipSpace = proj* view * model * vec4(Vertices,1);
  gl_Position = clipSpace;
  texCoords = vec2(Vertices.x/2.0+0.5, Vertices.z/2.0+0.5) * 10.0;
}
