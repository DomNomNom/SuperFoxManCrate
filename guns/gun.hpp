#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <vector>


class Bullet;
class Player;

class Gun {
protected:
  const Player &shooter;
  const sf::Image &bulletTexture;
  std::vector<Bullet> &bullets;
  sf::Clock coolDown;
  int damadge;
  virtual void shoot();
public:
  bool trigger;
  Gun(std::vector<Bullet> &b, Player &p, const sf::Image &bulletTex, int dmg);
  virtual void update();
};

#endif
