#include <SFML/Graphics.hpp>

#include "collisionObject.hpp"

class Enemy : public CollisionObject {
  int health;
public:
  sf::Sprite tile;
  bool dead;
  
  Enemy(float x, float y, int hp, sf::Image &pic);
  
  void update(float dt);
  
  bool collidesWith(CollisionObject &o);
  
  void hurt(int dmg);
};
