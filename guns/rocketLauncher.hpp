#include <SFML/Graphics.hpp>
#include <vector>

#include "gun.hpp"

class Bullet;
class Player;

class RocketLauncher : public Gun {
  void shoot();
public:
  RocketLauncher(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex, int dmg);
  void update();
};
