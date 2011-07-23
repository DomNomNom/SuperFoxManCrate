#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <SFML/System/Vector2.hpp>

class CollisionObject{
public:
  sf::Vector2<float> pos;
  sf::Vector2<float> vel;
  sf::Vector2<float> sz;
  CollisionObject(float x, float y, float wd, float ht);
  virtual void update(float dt);
  virtual bool collidesWith(CollisionObject &o);
};
  
#endif
