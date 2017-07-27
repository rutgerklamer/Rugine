#version 410 core
out vec4 color;
const float offset = 1.0 / 300.0;
in vec2 texCoords;
uniform sampler2D Texture;

void main(void)
{
float Pixels = 1024.0;
        float dx = 10.0 * (1.0 / Pixels);
        float dy = 10.0 * (1.0 / Pixels);
        vec2 Coord = vec2(dx * floor(texCoords.x / dx),
                          dy * floor(texCoords.y / dy));
color = texture(Texture, Coord);
}
