#version 410 core

layout (location = 0) in vec3 Vertices;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 Normals;
layout (location = 3) in vec3 Tangents;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
uniform vec4 planeYPosition;

out VS_OUT {
    vec3 normals;
} vs_out;


void main(void)
{
    gl_ClipDistance[0] = dot(model*vec4(Vertices,1), planeYPosition);
    gl_Position = proj* view * model * vec4(Vertices,1);

    vec3 n = normalize((model* vec4(Normals,0)).xyz);
    vec3 t = normalize((model* vec4(Tangents,0)).xyz);

    t = normalize(t-dot(t,n) * n);
    vec3 b = cross(t,n);
    mat3 toTangentSpace = mat3(t,b,n);

    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    vs_out.normals = normalize(vec3(proj * vec4(normalMatrix * Normals, 1.0)));
}
