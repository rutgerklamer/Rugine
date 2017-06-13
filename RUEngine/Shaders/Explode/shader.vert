#version 410 core

layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out VS_OUT {
  vec2 texCoords;
    vec3 normal;
} vs_out;

void main(void)
{
  gl_Position = proj * view * model * vec4(Vertices, 1.0);
  mat3 normalMatrix = mat3(transpose(inverse(view * model)));
  vs_out.normal = normalize(vec3(proj* vec4(normalMatrix * Normals, 1.0)));
  vs_out.texCoords = TexCoords;
}
