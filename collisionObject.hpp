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

  // functions regarding rotation with vectors
  void add(sf::Vector2<float> &vector, float dX, float dY, int angle);
  void set(sf::Vector2<float> &vector, float x, float y, int angle);
  void setX(sf::Vector2<float> &vector, float x, int angle);
  void setY(sf::Vector2<float> &vector, float x, int angle);
  float getX(const sf::Vector2<float> &vector, int angle);
  float getY(const sf::Vector2<float> &vector, int angle);
};
  
#endif
