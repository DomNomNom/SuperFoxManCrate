#include "collisionObject.hpp"

CollisionObject::CollisionObject(float x, float y, float wd, float ht) : box(x, y, wd, ht) { }

bool CollisionObject::collidesWith(CollisionObject &o) {
  return o.collidesWith(box);
}

bool CollisionObject::collidesWith(sf::Rect<float> &r) {
  return box.Intersects(r);
}
