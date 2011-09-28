#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <SFML/Graphics.hpp>
#include "vector2.hpp"

class CollisionObject {
public:
  vector2<float> pos;
  vector2<float> vel;
  vector2<float> sz;
  sf::Sprite visual;
  
  CollisionObject(float x, float y, const sf::Texture &tex);
  
  virtual void update(float dt);
  virtual void updateVisual();
  virtual void rotate(float angle); // note: the rotation is absolute, not relative to it's previouse angle.
  virtual float testX(const CollisionObject &o) const;
  virtual float testY(const CollisionObject &o) const;
  virtual bool collidesWith(const CollisionObject &o) const;  

  // functions regarding rotation with vectors
  void add(vector2<float> &vector, float dX, float dY, int angle);
  void set(vector2<float> &vector, float x, float y, int angle);
  void setX(vector2<float> &vector, float x, int angle);
  void setY(vector2<float> &vector, float x, int angle);
  float getX(const vector2<float> &vector, int angle);
  float getY(const vector2<float> &vector, int angle);
};
  
#endif
