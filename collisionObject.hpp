#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class CollisionObject {
public:
  sf::Vector2<float> pos;
  sf::Vector2<float> vel;
  sf::Vector2<float> sz;
  sf::Sprite visual;
  
  CollisionObject(float x, float y, const sf::Texture &tex);
  
  virtual void update(float dt);
  virtual void updateVisual();
  virtual void rotate(float angle); // note: the rotation is absolute, not relative to it's previouse angle.
  virtual float testX(const CollisionObject &o) const;
  virtual float testY(const CollisionObject &o) const;
  virtual bool collidesWith(const CollisionObject &o) const;  
};
  
#endif
