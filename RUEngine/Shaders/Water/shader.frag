#version 410 core

out vec4 color;
in vec2 texCoords;
in vec4 clipSpace;

uniform sampler2D WaterReflection;
uniform sampler2D WaterRefraction;

void main(void)
{
  vec2 ndc = clipSpace.xy/clipSpace.w * 0.5 + 0.5;

  vec2 reflactionCoords = vec2(ndc.x, 1 - ndc.y);
  vec2 refractionCoords = vec2(ndc.x, ndc.y);

  vec4 reflectionTexture = texture2D(WaterReflection, reflactionCoords);
  vec4 refractionTexture = texture2D(WaterRefraction, refractionCoords);

  color = mix(reflectionTexture, refractionTexture, 0.5);
}
