#include <SFML/Graphics.hpp>

#include "collisionObject.hpp"

class Enemy : public CollisionObject {
  int health;
  bool angry;
  float speed;
public:
  sf::Sprite visual;
  bool dead;
  
  Enemy(float x, float y, int hp, const sf::Texture &pic);
  
  void update(float dt);
  
  bool collidesWith(CollisionObject &o);
  
  void hurt(int dmg);
  
  void anger();
};
