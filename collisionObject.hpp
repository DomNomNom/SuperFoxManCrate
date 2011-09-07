#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <SFML/System/Vector2.hpp>

struct CollisionObject {
  sf::Vector2<float> pos;
  sf::Vector2<float> vel;
  sf::Vector2<float> sz;
  CollisionObject(float x, float y, float wd, float ht);
  virtual void update(float dt);
  virtual float testX(const CollisionObject &o) const;
  virtual float testY(const CollisionObject &o) const;
  virtual bool collidesWith(const CollisionObject &o) const;
};
  
#endif
