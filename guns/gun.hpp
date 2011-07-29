#include <SFML/Graphics.hpp>
#include <vector>


class Bullet;
class Player;

class Gun {
  Player &shooter;
  sf::Image &bulletTexture;
  std::vector<Bullet> &bullets;
public:
  Gun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex);
  void checkKeys();
};
