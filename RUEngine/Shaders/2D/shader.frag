#version 410 core

out vec4 color;

in vec2 texCoords;

uniform sampler2D texture;
uniform vec3 Color;

void main() {
  if (Color.r + Color.g + Color.b == 0) {
    color = texture2D(texture, vec2(texCoords.x, 1.0 - texCoords.y));
  } else {
    color = vec4(vec3(Color.r, Color.g, Color.b),1);
  }
}
