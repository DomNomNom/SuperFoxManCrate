#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <vector>


class Bullet;
class Player;

class Gun {
protected:
public:
  Player &shooter;
  sf::Image &bulletTexture;
  sf::Clock coolDown;
  std::vector<Bullet> &bullets;
  virtual void shoot();
  bool trigger;  
  Gun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex);
  void update();
  //void pullTrigger();
  //void releaseTrigger();
};

#endif
