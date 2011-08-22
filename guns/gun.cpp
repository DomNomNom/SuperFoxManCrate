#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "gun.hpp"


Gun::Gun(
  std::vector<Bullet> &b, 
  Player &p, 
  const sf::Texture &bulletTex, 
  int coolTime, 
  int dmg, 
  int burst, 
  float vel_x, float vel_y,
  float var_x, float var_y, 
  float acc_x, float acc_y,
  bool autoFire, 
  bool explosive
 ) 
 : bullets(b), 
   shooter(p), 
   bulletSprite(bulletTex), 
   coolingTime(coolTime),
   damadge(dmg),
   burstCount(burst),
   vel(vel_x, vel_y),
   inaccuracy(var_x, var_y),
   acc(acc_x, acc_y),
   automatic(autoFire),
   trigger(false),
   explosiveAmmo(explosive),
   inverted(true)
{ }

void Gun::shoot() {
  if (coolDown.GetElapsedTime() > coolingTime) {
    coolDown.Reset();
    if (shooter.facingLeft == inverted) {
      vel.x *= -1;  // note: logical XOr
      acc.x *= -1;
      inverted = !inverted;
    }
    for (int i=0; i<burstCount; ++i) {
      bullets.push_back( Bullet(
        shooter.pos.x, 
        shooter.pos.y, 
        vel.x + inaccuracy.x*(float)rand()/(float)RAND_MAX - inaccuracy.x/2,
        vel.y + inaccuracy.y*(float)rand()/(float)RAND_MAX - inaccuracy.y/2, 
        acc,
        bulletSprite,
        damadge,
        explosiveAmmo
      ));
    }
    trigger = automatic;
  }
}

void Gun::update() {
  if (trigger) shoot(); // duh!
}


