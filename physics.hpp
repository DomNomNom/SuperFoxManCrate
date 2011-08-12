#include <vector>

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
  bool outsideBounds(CollisionObject &o);
public:
  Physics(Player &play, Level &l, std::vector<Bullet> &b, std::vector<Explosion> &x, std::vector<Enemy> &e, Box &bx);
  void update(float dt);
};
