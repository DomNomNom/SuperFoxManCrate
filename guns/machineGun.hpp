#include <SFML/Graphics.hpp>
#include <vector>

#include "gun.hpp"

class Bullet;
class Player;

class MachineGun : public Gun {
  void shoot();
public:
  MachineGun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex, int dmg);
  void update();
};
