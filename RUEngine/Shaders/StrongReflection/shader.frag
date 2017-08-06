#version 410 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec2 texCoords;

uniform vec3 camPos;
uniform vec3 Color;
uniform samplerCube skybox;
uniform sampler2D Texture;

void main()
{
  vec3 I = normalize(Position - camPos);
  vec3 R = reflect(I, normalize(Normal));
  if (Color.r + Color.g + Color.b == 0)
  {
    FragColor = mix(texture(Texture, texCoords),vec4(texture(skybox, R).rgb, 1.0),0.8);
  } else {
    FragColor = mix(vec4(vec3(Color.r, Color.g, Color.b),1),vec4(texture(skybox, R).rgb, 1.0),0.8);
  }
  FragColor = mix(vec4(vec3(Color.r, Color.g, Color.b),1),vec4(texture(skybox, R).rgb, 1.0),0.8);
}
