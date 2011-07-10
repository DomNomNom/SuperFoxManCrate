#include <vector>

class Player;
class CollisionObject;


class Physics {
  Player &p;
  std::vector<CollisionObject*> level;
  std::vector<CollisionObject*> bullets;
  std::vector<CollisionObject*> enemies;
public:
  Physics(Player &play);
  void update(float dt);
  void addPlatform(CollisionObject *platform);
  void addEnemy(CollisionObject *enemy);
  void addBullet(CollisionObject *bullet);
};
