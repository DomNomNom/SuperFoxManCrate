#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "rocketLauncher.hpp"

#define GUN_COOLDOWN 500  // in millis
#define ROCKET_SPEED 0.1

RocketLauncher::RocketLauncher(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex, int dmg) : Gun(b, p, bulletTex, dmg) { }

void RocketLauncher::shoot() {
  if (coolDown.GetElapsedTime() > GUN_COOLDOWN) {
    coolDown.Reset();
    bullets.push_back( Bullet(
      shooter.pos.x, 
      shooter.pos.y, 
      (shooter.facingLeft)? -ROCKET_SPEED : ROCKET_SPEED, 
      0, 
      bulletTexture,
      damadge
    ));
    trigger = false;
  }
}

void RocketLauncher::update() {
  if (trigger) shoot(); // duh!
}
