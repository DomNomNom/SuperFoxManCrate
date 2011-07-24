#include <SFML/Graphics.hpp>

#include "collisionObject.hpp"

class Enemy : public CollisionObject {
public:
  sf::Sprite tile;
  bool dead;
  
  Enemy(float x, float y, sf::Image &pic);
  
  void update(float dt);
  
  bool collidesWith(CollisionObject &o);
};
