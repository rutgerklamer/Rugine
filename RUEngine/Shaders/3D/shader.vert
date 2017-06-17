#version 410 core

layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;
layout (location = 3) in vec3 Tangents;
layout (location = 4) in vec3 BitTangent;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec2 texCoords;
out vec3 worldPos;
out vec3 normals;
out mat3 TBN;

void main(void)
{
  mat3 normalMatrix = mat3(model);
  normalMatrix = transpose(normalMatrix);
  normals = normalize(Normals * normalMatrix);
  worldPos = vec3(model*vec4(Vertices,1)).xyz;

  vec3 T = normalize(vec3(model * vec4(Tangents,   0.0)));
  vec3 B = normalize(vec3(model * vec4(BitTangent, 0.0)));
  vec3 N = normalize(vec3(model * vec4(Normals,    0.0)));
  TBN = mat3(T, B, N);

  gl_Position = proj* view * model * vec4(Vertices,1);
  texCoords = TexCoords;
}
