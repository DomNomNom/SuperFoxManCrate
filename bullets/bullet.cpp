#include "../collisionObject.hpp"
#include "bullet.hpp"

Bullet::Bullet(float x, float y, float v_x, float v_y, sf::Image &texture) : CollisionObject(x, y, 4, 4), dead(false), damadge(1)  {
  vel.x = v_x;
  vel.y = v_y;
  visual.SetImage(texture);
}

void Bullet::update(float dt) {
  pos += vel * dt;
  visual.SetPosition(pos.x, pos.y);
}

bool Bullet::collidesWith(CollisionObject &o) {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.y, o.pos.y + o.sz.y);
  // If the intersection is valid (positive non zero area), then there is an intersection
  if ((left < right) && (top < bottom)) return true;
  else return false;
}
