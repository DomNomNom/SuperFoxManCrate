#ifndef GUN_H
#define GUN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>


class Bullet;
class Player;

class Gun {
  const Player &shooter;
  const sf::Texture &bulletSprite;
  sf::Sound shotSound;
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
