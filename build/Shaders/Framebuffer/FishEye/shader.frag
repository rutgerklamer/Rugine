#version 410 core

out vec4 color;

const float offset = 1.0 / 300.0;

in vec2 texCoords;

uniform sampler2D Texture;
const float PI = 3.1415926535;

void main(void)
{
vec4 c;
float aperture = 178.0;
float apertureHalf = 0.5 * aperture * (PI / 180.0);
float maxFactor = sin(apertureHalf);

vec2 uv;
vec2 xy = 2.0 * texCoords.xy - 1.0;
float d = length(xy);
if (d < (2.0-maxFactor))
{
  d = length(xy * maxFactor);
  float z = sqrt(1.0 - d * d);
  float r = atan(d, z) / PI;
  float phi = atan(xy.y, xy.x);

  uv.x = r * cos(phi) + 0.5;
  uv.y = r * sin(phi) + 0.5;
  c = texture2D(Texture, uv);
}
else
{
  c = vec4(0.4,0.2,0.0,1);
}
  color = c;
}
