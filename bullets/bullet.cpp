#include "bullet.hpp"

Bullet::Bullet(float x, float y, float vel_x, float vel_y, sf::Vector2<float> &acceleration, const sf::Image &tex, int dmg, bool explosion) : 
 CollisionObject(x, y, tex.GetWidth(), tex.GetHeight()), 
 dead(false),
 upsideDown(false),
 damadge(dmg),
 explosive(explosion),
 acc(acceleration) {
  vel.x = vel_x;
  vel.y = vel_y;
  visual.SetImage(tex);
  visual.FlipX((vel.x+acc.x)<0);
  update(0);
}

void Bullet::update(float dt) {
  vel += acc * dt;
  pos += vel * dt;
  visual.SetPosition(pos.x, pos.y);
  
  upsideDown = !upsideDown;
  visual.FlipY(upsideDown);  // cheap animation
  visual.SetScale(1, 1);
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
