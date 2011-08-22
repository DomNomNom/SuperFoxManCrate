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
  bool explosive;
  bool deadOnSlow;
  int damadge;
  sf::Sprite visual;
  
  // TODO: acceleration
  Bullet(float x, float y, float vel_x, float vel_y, sf::Vector2<float> &acceleration, const sf::Texture &tex, int dmg, bool explosion);
  void update(float dt);
  bool collidesWith(CollisionObject &o);
};

#endif
