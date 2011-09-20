#include "bullet.hpp"

#define MINIMUM_VEL 0.0005*dt

Bullet::Bullet(float x, float y, float vel_x, float vel_y, sf::Vector2<float> &acceleration, const sf::Texture &tex, int dmg, bool explosion) : 
 CollisionObject(x, y, tex), 
 dead(false),
 upsideDown(false),
 damadge(dmg),
 explosive(explosion),
 acc(acceleration),
 deadOnSlow(true) {
  vel.x = vel_x;
  vel.y = vel_y;
  visual.FlipX(vel.x<0);
}

void Bullet::update(float dt) {
  vel += acc * dt;
  pos += vel * dt;
  visual.SetPosition(pos.x, pos.y);
  
  if (deadOnSlow && vel.x < MINIMUM_VEL  && vel.x > -MINIMUM_VEL) dead = true;
  
  upsideDown = !upsideDown;
  visual.FlipY(upsideDown);  // cheap animation
  updateVisual();
}
