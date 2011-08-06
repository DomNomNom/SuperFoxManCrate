#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "gun.hpp"

#define GUN_COOLDOWN 50  // in millis
#define BULLET_SPEED 0.2

Gun::Gun(std::vector<Bullet> &b, Player &p, const sf::Image &bulletTex, int dmg, int burst, float var_x, float var_y) 
 : bullets(b), 
 shooter(p), 
 bulletTexture(bulletTex), 
 damadge(dmg),
 burstCount(burst),
 inaccuracy_x(var_x),
 inaccuracy_y(var_y),
 trigger(false) { }


void Gun::shoot() {
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
    trigger = false;
  }
}

void Gun::update() {
  if (trigger) shoot(); // duh!
}
