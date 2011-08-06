#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "gun.hpp"

#define BULLET_SPEED 0.2

Gun::Gun(std::vector<Bullet> &b, Player &p, const sf::Image &bulletTex, int coolTime, int dmg, int burst, float var_x, float var_y) 
 : bullets(b), 
 shooter(p), 
 bulletTexture(bulletTex), 
 coolingTime(coolTime),
 damadge(dmg),
 burstCount(burst),
 inaccuracy_x(var_x),
 inaccuracy_y(var_y),
 trigger(false) { }


void Gun::shoot() {
  if (coolDown.GetElapsedTime() > coolingTime) {
    coolDown.Reset();
    float vel_x = BULLET_SPEED;
    float vel_y = 0;
    if (shooter.facingLeft) vel_x *= -1;
    for (int i=0; i<burstCount; ++i) {
      bullets.push_back( Bullet(
        shooter.pos.x, 
        shooter.pos.y, 
        vel_x + inaccuracy_x*(float)rand()/(float)RAND_MAX - inaccuracy_x/2,
        vel_y + inaccuracy_y*(float)rand()/(float)RAND_MAX - inaccuracy_y/2, 
        bulletTexture,
        damadge
      ));
    }
    trigger = false;
  }
}

void Gun::update() {
  if (trigger) shoot(); // duh!
}
