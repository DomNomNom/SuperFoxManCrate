#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "gun.hpp"

#define GUN_COOLDOWN 100  // in millis
#define BULLET_SPEED 0.2

Gun::Gun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex) : bullets(b), shooter(p), bulletTexture(bulletTex) { }

void Gun::checkKeys() { 
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space) ) shoot();
}

void Gun::shoot() {
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
