#include <SFML/Graphics.hpp>

#include "collisionObject.hpp"

class Physics;

class Enemy : public CollisionObject {
  int health;
  bool angry;
  float speed;
public:
  sf::Sprite visual;
  bool dead;
  
  Enemy(float x, float y, int hp, const sf::Texture &pic);
  
  void update(float dt, const Physics &phys);
  
  void hurt(int dmg);
  
  void anger();
};
