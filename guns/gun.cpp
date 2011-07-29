#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "gun.hpp"

Gun::Gun(std::vector<Bullet> &b, Player &p, sf::Image &bulletTex) : bullets(b), shooter(p), bulletTexture(bulletTex) { }

void Gun::checkKeys() { 
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space)) bullets.push_back( Bullet(
    shooter.pos.x, 
    shooter.pos.y, 
    (shooter.facingLeft)? -0.2 : 0.2, 
    0, 
    bulletTexture
  ));
}
