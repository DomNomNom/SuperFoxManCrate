#include <stdlib.h>  // for rand()
#include "physics.hpp"
#include "utils.hpp"
#include "enemy.hpp"

#define ENEMY_GRAVITY 0.0015
#define ENEMY_WALKSPEED 0.05
#define ENEMY_ANGER_SPEED 0.1

Enemy::Enemy(float x, float y, int hp, const sf::Texture &pic) 
 : CollisionObject(x, y, pic.GetWidth(), pic.GetHeight()), 
 speed(ENEMY_WALKSPEED), 
 visual(pic),
 health(hp), 
 dead(false),
 angry(false) {
  vel.x = (rand()%2*2-1) * speed; // either left or right walking
  visual.SetPosition(pos.x, pos.y);
  visual.FlipX(vel.x<0);
}

void Enemy::update(float dt, const Physics &phys) {
  vel.y += ENEMY_GRAVITY * dt;
  
  // check X-direction
  pos.x += vel.x * dt;
  bool movedX = false;
  float changeX = phys.testX(*this);
  while (changeX!=0) {  // as long as there are collisions with the level, keep checking
    pos.x += changeX;
    movedX = true;
    changeX = phys.testX(*this);
  }
  changeX = phys.testBoundsX(*this);
  if (changeX != 0) {
    pos.x += changeX;
    movedX = true;
  }
  if (movedX) vel.x *= -1;
  
  // check Y-direction
  pos.y += vel.y * dt;
  for (float changeY = phys.testY(*this); changeY!=0; changeY = phys.testY(*this)) {
    pos.y += phys.testY(*this); 
    vel.y = 0;
  }
  if (phys.testBoundsY(*this) < 0) {  // when fallen into the pit
    anger();
    dead = true;  // indicate death to reset
  }
  
  visual.SetPosition(pos.x, pos.y);
  visual.FlipX(vel.x<0);
  visual.SetScale(1, 1);
}

void Enemy::hurt(int dmg) {
  health -= dmg;
  if (health <= 0) dead = true;
}

void Enemy::anger() {
  vel.x /= std::abs(vel.x);
  speed = ENEMY_ANGER_SPEED;
  vel.x *= speed;
  visual.SetColor(sf::Color::Red);
  angry = true;
}
