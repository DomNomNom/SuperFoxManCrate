#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "stdlib.h"
#include "machineGun.hpp"

#define BULLET_SPEED 0.2

MachineGun::MachineGun(std::vector<Bullet> &b, Player &p, const sf::Image &bulletTex, int coolTime, int dmg, int burst, float var_x, float var_y)
 : Gun(b, p, bulletTex, coolTime, dmg, burst, var_x, var_y) { }


void MachineGun::shoot() {
  if (coolDown.GetElapsedTime() > coolingTime) {
    coolDown.Reset();
    bullets.push_back( Bullet(
      shooter.pos.x, 
      shooter.pos.y, 
      (shooter.facingLeft)? -BULLET_SPEED : BULLET_SPEED, 
      inaccuracy_y*(float)rand()/(float)RAND_MAX - inaccuracy_y/2, 
      bulletTexture,
      damadge
    ));
  }
}

void MachineGun::update() {
  if (trigger) shoot(); // duh!
}
