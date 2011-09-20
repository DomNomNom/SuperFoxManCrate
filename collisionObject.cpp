#include <iostream>
#include <algorithm>  // for min and max
#include "collisionObject.hpp"

CollisionObject::CollisionObject(float x, float y, const sf::Texture &tex) : pos(x, y), visual(tex), vel(0, 0), sz(tex.GetWidth(), tex.GetHeight()) {
  updateVisual();
}

void CollisionObject::update(float dt) {
  pos += vel * dt;
  updateVisual();
}

void CollisionObject::updateVisual() {
  visual.SetPosition(pos.x, pos.y);
  visual.SetScale(1, 1);
}

void CollisionObject::rotate(float angle) {
  angle *= -1;
  visual.SetOrigin(0, 0);
  visual.SetRotation(angle);
  visual.SetOrigin( // make it seem as if rotating around the centre of the object
    sz.x/2 - (sqrt(2))*(sz.x/2)*sin((angle+45)*2*M_PI/360.0), 
    sz.y/2 - (sqrt(2))*(sz.y/2)*cos((angle+45)*2*M_PI/360.0)
  );
}

float CollisionObject::testX(const CollisionObject &o) const {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.y, o.pos.y + o.sz.y);
  if ((left < right) && (top < bottom)) {  // If the intersection is valid (positive non zero area), then there is an intersection
    if (o.vel.x < 0)      return (pos.x + sz.x) - o.pos.x;  // if moving left,  push right
    else if (o.vel.x > 0) return (pos.x-o.sz.x) - o.pos.x;  // if moving right, push left
    else return -0.1;                                       // if not moving at all, PANIC!?
  }
  else return 0;
}

float CollisionObject::testY(const CollisionObject &o) const {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.y, o.pos.y + o.sz.y);
  if ((left < right) && (top < bottom)) {  // If the intersection is valid (positive non zero area), then there is an intersection
    if (o.vel.y < 0)      return (pos.y + sz.y) - o.pos.y;  // if moving left,  push right
    else if (o.vel.y > 0) return (pos.y-o.sz.y) - o.pos.y;  // if moving right, push left
    else return -0.1;                                       // if not moving at all, PANIC!?
  }
  else return 0;
}

bool CollisionObject::collidesWith(const CollisionObject &o) const {
  return (testX(o) != 0);
}


