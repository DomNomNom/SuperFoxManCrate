#ifndef BULLET_H
#define BULLET_H

#include "../vector2.hpp"

#include "../collisionObject.hpp"

class Bullet : public CollisionObject  {
  bool upsideDown;
  vector2<float> acc;
public:
  bool dead;
  bool explosive;
  bool deadOnSlow;
  int damadge;
  
  Bullet(float x, float y, float vel_x, float vel_y, vector2<float> &acceleration, const sf::Texture &tex, int dmg, bool explosion);
  void update(float dt);
};

#endif
