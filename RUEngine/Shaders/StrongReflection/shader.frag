#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 camPos;
uniform samplerCube skybox;

void main()
{
float ratioR = 1.00 / 1.05;
float ratioG = 1.00 / 1.08;
float ratioB = 1.00 / 1.02;

vec3 I = normalize(Position - camPos);

vec3 RedRefractionVector = refract(I * 2.0, normalize(Normal), ratioR / (length(I) * 1.01));
vec3 GreenRefractionVector = refract(I * 2.0, normalize(Normal), ratioG / (length(I) * 1.02));
vec3 BlueRefractionVector = refract(I * 2.0, normalize(Normal), ratioB / (length(I) * 1.02));

FragColor.r = vec4(texture(skybox, RedRefractionVector).rgb, 1.0).r;
FragColor.g = vec4(texture(skybox, GreenRefractionVector).rgb, 1.0).g;
FragColor.b = vec4(texture(skybox, BlueRefractionVector).rgb, 1.0).b;
FragColor.a = 1;

}
