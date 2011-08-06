#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "../collisionObject.hpp"

class Bullet : public CollisionObject  {
  bool upsideDown;
  sf::Vector2<float> acc;
public:
  bool dead;
  int damadge;
  sf::Sprite visual;
  
  // TODO: acceleration
  Bullet(float x, float y, float v_x, float v_y, float a_x, float a_y, const sf::Image &tex, int dmg);
  void update(float dt);
  bool collidesWith(CollisionObject &o);
};

#endif
