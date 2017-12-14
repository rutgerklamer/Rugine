#include "Enemy.h"

Enemy::Enemy(Entity* entity) : Entity()
{
  time.timer.start();
  player = entity;
}

Enemy::~Enemy()
{

}

void Enemy::update(float deltaTime) {
  if (time.timer.seconds() > 0.1f) {
    Bullet* bullet = new Bullet(glm::normalize(player->position - this->position) * 100.0f, Bullet::ENEMY);
    bullet->position = this->position;
    bullets.push_back(bullet);
    time.timer.start();
  }
  glm::vec3 v = glm::normalize(player->position - this->position);
  this->eularAngles = glm::vec3(0,-atan2(v.z, v.x),0);

}
