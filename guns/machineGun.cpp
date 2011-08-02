#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "machineGun.hpp"

#define GUN_COOLDOWN 50  // in millis
#define BULLET_SPEED 0.2

MachineGun::MachineGun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex, int dmg) : Gun(b, p, bulletTex, dmg) { }


void MachineGun::shoot() {
  if (coolDown.GetElapsedTime() > GUN_COOLDOWN) {
    coolDown.Reset();
    bullets.push_back( Bullet(
      shooter.pos.x, 
      shooter.pos.y, 
      (shooter.facingLeft)? -BULLET_SPEED : BULLET_SPEED, 
      0, 
      bulletTexture,
      damadge
    ));
  }
}

void MachineGun::update() {
  if (trigger) shoot(); // duh!
}
