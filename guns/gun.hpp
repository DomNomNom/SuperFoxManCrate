#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <vector>


class Bullet;
class Player;

class Gun {
protected:
  Player &shooter;
  sf::Image &bulletTexture;
  sf::Clock coolDown;
  std::vector<Bullet> &bullets;
  int damadge;
  virtual void shoot();
public:
  bool trigger;
  Gun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex, int dmg);
  virtual void update();
};

#endif
