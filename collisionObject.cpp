
#include <algorithm>  // for min and max
#include "collisionObject.hpp"

CollisionObject::CollisionObject(float x, float y, float wd, float ht) : pos(x, y), vel(0, 0), sz(wd, ht) { }

bool CollisionObject::collidesWith(CollisionObject &o) {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.y, o.pos.y + o.sz.y);
  // If the intersection is valid (positive non zero area), then there is an intersection
  if ((left < right) && (top < bottom)) return true;
  else return false;
}

