#include <vector>


class Bullet;
class Player;

class Gun {
  Player &shooter;
  std::vector<Bullet> &bullets;
public:
  Gun(std::vector<Bullet> &b, Player &p);
  void checkKeys();
};
