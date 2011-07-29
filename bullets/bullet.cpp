#include "../collisionObject.hpp"
#include "bullet.hpp"

Bullet::Bullet(float x, float y, float v_x, float v_y, sf::Image &texture) : CollisionObject(x, y, 4, 4), dead(false)  {
  vel.x = v_x;
  vel.y = v_y;
  visual.SetImage(texture);
}

void Bullet::update(float dt) {
  pos += vel * dt;
  visual.SetPosition(pos.x, pos.y);
}

