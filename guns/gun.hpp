#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>


class Bullet;
class Player;

class Gun {
protected:
  const Player &shooter;
  const sf::Image &bulletTexture;
  std::vector<Bullet> &bullets;
  sf::Clock coolDown;
  
  sf::Vector2<float> vel;
  sf::Vector2<float> inaccuracy;
  sf::Vector2<float> acc;
  
  int coolingTime;
  int damadge;
  int burstCount;
  bool automatic;
  bool explosiveAmmo;
  bool inverted;
  void shoot();
public:
  bool trigger;
  Gun(
    std::vector<Bullet> &b, 
    Player &p, 
    const sf::Image &bulletTex, 
    int coolTime, 
    int dmg, 
    int burst, 
    float vel_x, float vel_y,
    float var_x, float var_y, 
    float acc_x, float acc_y,
    bool autoFire, 
    bool explosive
  );
  void update();
};

#endif
