#include <vector>

class Player;
class Level;
class CollisionObject;
class Bullet;
class Enemy;

class Physics {
  Player &p;
  Level &l;
  std::vector<Bullet> &bullets;
  std::vector<Enemy> &enemies;
  bool outsideBounds(CollisionObject &o);
public:
  Physics(Player &play, Level &l, std::vector<Bullet> &b, std::vector<Enemy> &e);
  void update(float dt);
};
