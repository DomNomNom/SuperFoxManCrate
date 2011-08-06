#include <SFML/Graphics.hpp>
#include <vector>

#include "gun.hpp"

class Bullet;
class Player;

class RocketLauncher : public Gun {
  void shoot();
public:
  RocketLauncher(std::vector<Bullet> &b, Player &p, const sf::Image &bulletTex, int coolTime, int dmg, int burst, float var_x, float var_y);
  void update();
};
