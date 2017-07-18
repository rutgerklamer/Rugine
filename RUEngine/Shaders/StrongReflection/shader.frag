#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

uniform vec3 camPos;
uniform samplerCube skybox;
uniform sampler2D Texture;

void main()
{
vec3 I = normalize(Position - camPos);
vec3 R = reflect(I, normalize(Normal));
FragColor = mix(texture2D(Texture, TexCoords),vec4(texture(skybox, R).rgb, 1.0),0.2);

}
