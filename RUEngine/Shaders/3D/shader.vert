#version 410 core

layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;
layout (location = 3) in vec3 Tangents;
layout (location = 4) in vec3 BitTangent;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
uniform vec4 planeYPosition;

out vec2 texCoords;
out vec3 worldPos;
out vec3 normals;
out mat3 TBN;
out mat4 MV;
out mat4 V;

void main(void)
{
  mat3 normalMatrix = mat3(model);
  normalMatrix = transpose(normalMatrix);
  normals = normalize(Normals * normalMatrix);
  worldPos = vec3(model*vec4(Vertices,1)).xyz;
  MV = model * view;
  V = view;
  vec4 N = MV * normalize(vec4(normals,0));
  vec4 T = MV * normalize(vec4(Tangents,0));
  vec4 B = MV * normalize(vec4(BitTangent,0));
  TBN = transpose( mat3(vec3(T), vec3(B), vec3(N)));

  gl_ClipDistance[0] = dot(model*vec4(Vertices,1), planeYPosition);
  gl_Position = proj* view * model * vec4(Vertices,1);
  texCoords = TexCoords;
}
