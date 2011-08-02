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
public:
  bool trigger;  
  Gun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex);
  void shoot();
  void update();
  //void pullTrigger();
  //void releaseTrigger();
};

#endif
