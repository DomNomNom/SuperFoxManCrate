#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "machineGun.hpp"

#define GUN_COOLDOWN 10  // in millis
#define BULLET_SPEED 0.2

MachineGun::MachineGun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex) : Gun(b, p, bulletTex) { }

//void MachineGun::pullTrigger() { shoot(); }
//void MachineGun::releaseTrigger () { }

void MachineGun::shoot() {
  if (coolDown.GetElapsedTime() > GUN_COOLDOWN) {
    coolDown.Reset();
    bullets.push_back( Bullet(
      shooter.pos.x, 
      shooter.pos.y, 
      (shooter.facingLeft)? -BULLET_SPEED : BULLET_SPEED, 
      0, 
      bulletTexture
    ));
  }
}

void MachineGun::update() {
  if (trigger) shoot(); // duh!
}
