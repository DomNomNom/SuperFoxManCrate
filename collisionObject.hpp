#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

//#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

class CollisionObject{
protected:
  sf::Rect<float> box;
  //sf::Vector2<float> pos;
  //sf::Vector2<float> vel;
  //float wd;
  //float ht;
public:
  CollisionObject(float x, float y, float wd, float ht);
  virtual bool collidesWith(CollisionObject &o);
  bool collidesWith(sf::Rect<float> &r);
};
  
#endif
