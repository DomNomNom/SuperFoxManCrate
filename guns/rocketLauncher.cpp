#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "rocketLauncher.hpp"

#define ROCKET_SPEED 0.11

RocketLauncher::RocketLauncher(std::vector<Bullet> &b, Player &p, const sf::Image &bulletTex, int coolTime, int dmg, int burst, float var_x, float var_y) 
  : Gun(b, p, bulletTex, coolTime, dmg, burst, var_x, var_y) { }

void RocketLauncher::shoot() {
  if (coolDown.GetElapsedTime() > coolingTime) {
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
