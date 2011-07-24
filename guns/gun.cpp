#include <SFML/Graphics.hpp>

#include "../physics.hpp"
//#include "../bullets/bullet.hpp"
#include "../collisionObject.hpp"
#include "gun.hpp"

Gun::Gun(Physics &p) : phys(p) {

}

void Gun::checkKeys() {
//  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space)) phys.addBullet(new CollisionObject(0,0,0,0));
}
