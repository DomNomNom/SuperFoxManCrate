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
  int coolingTime;
  int damadge;
  int burstCount;
  float inaccuracy_x;
  float inaccuracy_y;
  bool automatic;
  virtual void shoot();
public:
  bool trigger;
  Gun(std::vector<Bullet> &b, Player &p, const sf::Image &bulletTex, int coolTime, int dmg, int burst, float var_x, float var_y, bool autoFire);
  virtual void update();
};

#endif
