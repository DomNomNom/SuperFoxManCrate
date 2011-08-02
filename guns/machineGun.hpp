#include <SFML/Graphics.hpp>
#include <vector>

#include "gun.hpp"

class Bullet;
class Player;

class MachineGun : protected Gun {
  /*Player &shooter;
  sf::Image &bulletTexture;
  sf::Clock coolDown;
  std::vector<Bullet> &bullets;
  void shoot(); */
public:
  MachineGun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex);
  void shoot();
  void update();

  //bool trigger;
  //void pullTrigger();
  //void releaseTrigger();
};
