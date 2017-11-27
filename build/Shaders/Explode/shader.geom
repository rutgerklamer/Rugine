#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

in VS_OUT {
    vec2 texCoords;
    vec3 normal;
} gs_in[];

out vec2 texCoords;

const float MAGNITUDE = 2.1;
uniform float time;

vec4 explode(vec4 position, vec3 normal)
{
    vec3 direction = normal * ((sin(time) + 1.0)) * MAGNITUDE;
    return position + vec4(direction, 0.0);
}

void GenerateExplosion(int index)
{
  vec3 normal = gs_in[index].normal;
  texCoords = gs_in[index].texCoords;
  gl_Position = explode(gl_in[index].gl_Position, normal);
  EmitVertex();
}

void main()
{
    GenerateExplosion(0); // first vertex normal
    GenerateExplosion(1); // second vertex normal
    GenerateExplosion(2); // third vertex normal
}
