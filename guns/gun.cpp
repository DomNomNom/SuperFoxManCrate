#include <SFML/Graphics.hpp>

//#include "../physics.hpp"
#include "../player.hpp"
#include "../bullets/bullet.hpp"
#include "gun.hpp"

Gun::Gun(std::vector<Bullet> &b, Player &p) : bullets(b), shooter(p) { }

void Gun::checkKeys() { 
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space)) bullets.push_back(Bullet(shooter.pos.x, shooter.pos.y,0,0));
}
