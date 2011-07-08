#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <SFML/System/Vector2.hpp>

class CollisionObject{
protected:
  sf::Vector2<float> pos;
  sf::Vector2<float> vel;
  float wd;
  float ht;
public:
  virtual bool collideWith(CollisionObject o);
};
  
#endif
