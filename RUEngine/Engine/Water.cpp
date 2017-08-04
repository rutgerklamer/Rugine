#include "Water.h"


Water::Water(glm::vec2 s, glm::vec3 p)
{
  waterSize = s;
  waterPosition = p;
  entity = new Entity();
  entity->LoadObject("Assets/waterQuad.obj", false);
  entity->position = p;
  entity->scale = glm::vec3(s.x, 0, s.y);
  top = new Framebuffer("Shaders/Framebuffer/shader.vert", "Shaders/Framebuffer/shader.frag");
  bottom = new Framebuffer("Shaders/Framebuffer/shader.vert", "Shaders/Framebuffer/shader.frag");
  DUDVmap = tex::loadTexture("Assets/dudvMap.jpg");
}

Water::~Water()
{
  delete top;
  delete bottom;
  delete entity;
}
