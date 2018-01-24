#include "Enemy.h"

Enemy::Enemy(Entity* entity) : Entity()
{
  // Start a timer so dont spawn a bullet every frame
  time.timer.start();
  // Set the target (player)
  player = entity;
}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime) {
  if (time.timer.seconds() > 0.1f) {
    // Make a new bullet and set the direction + origin
    Bullet* bullet = new Bullet(glm::normalize(player->position - this->position) * 100.0f, Bullet::ENEMY);
    // the bullet should spawn at the center of this entity
    bullet->position = this->position;
    // Push the bullet to the list of bullets
    bullets.push_back(bullet);
    // set the timer to 0 seconds again
    time.timer.start();
  }
  // Get the normalizer difference between this entity and the player
  glm::vec3 v = glm::normalize(player->position - this->position);
  // So we can give it the right rotation
  this->eularAngles = glm::vec3(0,-atan2(v.z, v.x),0);

}
