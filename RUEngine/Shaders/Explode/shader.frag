#version 410 core

out vec4 color;
in vec2 texCoords;

uniform sampler2D texture;

void main(void)
{
    vec4 texture = texture2D(texture, texCoords);
    color = vec4(texture.rgb, 1);
}
