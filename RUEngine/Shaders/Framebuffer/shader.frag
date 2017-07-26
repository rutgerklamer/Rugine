#version 410 core

out vec4 color;

in vec2 texCoords;

uniform sampler2D Texture;

void main(void)
{
  color = texture2D(Texture, texCoords);
}
