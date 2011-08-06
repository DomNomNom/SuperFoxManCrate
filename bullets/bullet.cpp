#include "bullet.hpp"

Bullet::Bullet(float x, float y, float v_x, float v_y, float a_x, float a_y, const sf::Image &tex, int dmg)
 :  CollisionObject(x, y, tex.GetWidth(), tex.GetHeight()), 
 dead(false),
 upsideDown(false),
 damadge(dmg) {
  vel.x = v_x;
  vel.y = v_y;
  acc.x = a_x;
  acc.y = a_y;
  visual.SetImage(tex);
  visual.FlipX(vel.x<0);
  update(0);
}

void Bullet::update(float dt) {
  vel += acc * dt;
  pos += vel * dt;
  visual.SetPosition(pos.x, pos.y);
  
  visual.FlipY((int(pos.x)%2)==0);  // cheap animation
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
