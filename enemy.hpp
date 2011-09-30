#include "collisionObject.hpp"

class Physics;

class Enemy : public CollisionObject {
  int health;
  bool angry;
  bool facingLeft;
  bool hitWall;
  float speed;
  
  // helper functions for update()
  void canGoX(float dt, const Physics &phys);  
  void canGoY(float dt, const Physics &phys);

public:
  bool dead;
  
  Enemy(float x, float y, int hp, const sf::Texture &tex);
  
  void update(float dt, const Physics &phys);
  
  void hurt(int dmg);
  
  void anger(const Physics &phys);
};
