#include "collisionObject.hpp"

class Physics;

class Enemy : public CollisionObject {
  int health;
  bool angry;
  bool facingLeft;
  float speed;
public:
  bool dead;
  
  Enemy(float x, float y, int hp, const sf::Texture &tex);
  
  void update(float dt, const Physics &phys);
  
  void hurt(int dmg);
  
  void anger();
};
