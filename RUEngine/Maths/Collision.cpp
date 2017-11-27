#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::intersectAABB(Entity* e1, Entity* e2)
{
  int intersectionCount = 0;
  if (e1->position.x < e2->position.x) {
    if (e1->position.x + glm::vec3(glm::rotateY(e1->meshData.max * e1->scale, glm::radians(e1->eularAngles.y))).x > e2->position.x - (glm::vec3(glm::rotateY(e2->meshData.max * e2->scale, glm::radians(e1->eularAngles.y))).x )) {
      intersectionCount++;
    }
  } else if (e1->position.x - glm::vec3(glm::rotateY(e1->meshData.max * e1->scale, glm::radians(e1->eularAngles.y))).x < e2->position.x + glm::vec3(glm::rotateY(e2->meshData.max * e2->scale, glm::radians(e2->eularAngles.y))).x) {
    intersectionCount++;
  }
  if (e1->position.y < e2->position.y) {
    if (e1->position.y + glm::vec3(glm::rotateY(e1->meshData.max * e1->scale, glm::radians(e1->eularAngles.y))).y > e2->position.y - glm::vec3(glm::rotateY(e2->meshData.max * e2->scale, glm::radians(e2->eularAngles.y))).y) {
      intersectionCount++;
    }
  } else if (e1->position.y - glm::vec3(glm::rotateY(e1->meshData.max * e1->scale, glm::radians(e1->eularAngles.y))).y < e2->position.y + glm::vec3(glm::rotateY(e2->meshData.max * e2->scale, glm::radians(e2->eularAngles.y))).y) {
    intersectionCount++;
  }
  if (e1->position.z < e2->position.z) {
    if (e1->position.z + glm::vec3(glm::rotateY(e1->meshData.max * e1->scale, glm::radians(e1->eularAngles.y))).z > e2->position.z - glm::vec3(glm::rotateY(e2->meshData.max * e2->scale, glm::radians(e2->eularAngles.y))).z) {
      intersectionCount++;
    }
  } else if (e1->position.z - glm::vec3(glm::rotateY(e1->meshData.max * e1->scale, glm::radians(e1->eularAngles.y))).z < e2->position.z + glm::vec3(glm::rotateY(e2->meshData.max * e2->scale, glm::radians(e2->eularAngles.y))).z) {
    intersectionCount++;
  }
  if (intersectionCount > 2) {
  return true;
  } else {
    return false;
  }
}
