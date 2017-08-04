#version 410 core

out vec4 color;
in vec2 texCoords;
in vec4 clipSpace;

uniform sampler2D WaterReflection;
uniform sampler2D WaterRefraction;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform float time;

void main(void)
{
  vec2 ndc = clipSpace.xy/clipSpace.w * 0.5 + 0.5;

  vec2 reflactionCoords = vec2(ndc.x, 1 - ndc.y);
  vec2 refractionCoords = vec2(ndc.x, ndc.y);

  vec2 distortion1 = (texture2D(dudvMap, vec2(texCoords.x + (time * 0.01), texCoords.y + (time * -0.02))).rg * 2.0 -1.0) * 0.01;
  vec2 distortion2 = (texture2D(dudvMap, vec2(texCoords.x - (time * 0.03), texCoords.y - (time * 0.01))).rg * 2.0 -1.0) * 0.0092;

  reflactionCoords += distortion1;
  refractionCoords += distortion1;
  reflactionCoords += distortion2;
  refractionCoords += distortion2;

  refractionCoords = clamp(refractionCoords, 0.001, 0.99);


  reflactionCoords = clamp(reflactionCoords, 0.001, 0.99);

  vec4 reflectionTexture = texture2D(WaterReflection, reflactionCoords);
  vec4 refractionTexture = texture2D(WaterRefraction, refractionCoords);

  color = mix(reflectionTexture, refractionTexture, 0.5);
}
