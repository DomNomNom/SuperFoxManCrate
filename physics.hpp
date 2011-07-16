#include <vector>

class Player;
class Level;
class CollisionObject;


class Physics {
  Player &p;
  Level &l;
  std::vector<CollisionObject*> bullets;
  std::vector<CollisionObject*> enemies;
public:
  Physics(Player &play, Level &l);
  void update(float dt);
  //void addPlatform(CollisionObject *platform);
  void addEnemy(CollisionObject *enemy);
  void addBullet(CollisionObject *bullet);
};
