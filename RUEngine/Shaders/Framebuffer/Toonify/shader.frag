#version 410 core
out vec4 color;
const float offset = 1.0 / 300.0;
in vec2 texCoords;
uniform sampler2D Texture;

void main()
{
  vec3 c = texture2D(Texture, texCoords).rgb;
  float gamma = 0.8;
  float numColors = 14.0;
  c = pow(c, vec3(gamma, gamma, gamma));
  c = c * numColors;
  c = floor(c);
  c = c / numColors;
  c = pow(c, vec3(1.0/gamma));
color = vec4(c,1.0);
}
