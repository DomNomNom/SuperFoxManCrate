#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "../vector2.hpp"


class Bullet;
class Player;

class Gun {
  const Player &shooter;
  const sf::Texture &bulletSprite;
  sf::Sound shotSound;
  std::vector<Bullet> &bullets;
  sf::Clock coolDown;
  
  vector2<float> vel;
  vector2<float> inaccuracy;
  vector2<float> acc;
  
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
    const Player &p, 
    const sf::SoundBuffer &gunSound,
    const sf::Texture &bulletTex, 
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
