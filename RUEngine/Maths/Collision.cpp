#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::intersectAABB(Entity* e1, Entity* e2)
{
   glm::vec3 e1min = e1->position + e1->meshData.min * e1->scale;
   glm::vec3 e2min = e2->position + e2->meshData.min * e2->scale;
   glm::vec3 e1max = e1->position + e1->meshData.max * e1->scale;
   glm::vec3 e2max = e2->position + e2->meshData.max * e2->scale;

  int intersectionCount = 0;
  if (e1->position.x < e2->position.x) {
    if ( glm::vec4(e1max ,1 ).x >  (glm::vec4(e2min,1 ).x )) {
      intersectionCount++;
    }
  } else if ( glm::vec4(e1min,1 ).x <  glm::vec4(e2max,1 ).x) {
    intersectionCount++;
  }
  if (e1->position.y < e2->position.y) {
    if ( glm::vec4(e1max,1 ).y > glm::vec4(e2min,1 ).y) {
      intersectionCount++;
    }
  } else if (glm::vec4(e1min,1 ).y < glm::vec4(e2max,1 ).y) {
    intersectionCount++;
  }
  if (e1->position.z < e2->position.z) {
    if ( glm::vec4(e1max,1 ).z > glm::vec4(e2min,1 ).z) {
      intersectionCount++;
    }
  } else if ( glm::vec4(e1min,1 ).z <  glm::vec4(e2max,1 ).z) {
    intersectionCount++;
  }
  if (intersectionCount > 2) {
  return true;
  } else {
    return false;
  }
}
