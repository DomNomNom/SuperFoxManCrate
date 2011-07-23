#include <SFML/Graphics.hpp>

#include "collisionObject.hpp"

class Enemy : CollisionObject {
public:
  Enemy(float x, float y, sf::Image &pic);
  
  void update(float dt);
  
  sf::Sprite tile;
};
