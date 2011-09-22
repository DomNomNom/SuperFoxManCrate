#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include <SFML/System/Vector2.hpp>

class Player;
class Level;
class CollisionObject;
class Bullet;
class Explosion;
class Enemy;
class Box;

class Physics {
  Player &p;
  Level &l;
  std::vector<Bullet> &bullets;
  std::vector<Enemy> &enemies;
  std::vector<Explosion> &explosions;
  Box &box;
  bool outsideBounds(const CollisionObject &o) const;
public:
  sf::Vector2<float> gravity;
  int gravAngle;

  Physics(Player &play, Level &l, std::vector<Bullet> &b, std::vector<Explosion> &x, std::vector<Enemy> &e, Box &bx);

  void update(float dt);
  void rotateGravity(int angle);
  bool collidesWithWorld(const CollisionObject &o) const;
  float testX(const CollisionObject &o) const;
  float testY(const CollisionObject &o) const;
  float testBoundsX(const CollisionObject &o) const;
  float testBoundsY(const CollisionObject &o) const;
};

#endif
