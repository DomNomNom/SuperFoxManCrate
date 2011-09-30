#include <stdlib.h>  // for rand()
#include "physics.hpp"
#include "enemy.hpp"

#define ENEMY_gravity 0.0015
#define ENEMY_WALKSPEED 0.05
#define ENEMY_ANGER_SPEED 0.1

Enemy::Enemy(float x, float y, int hp, const sf::Texture &tex) 
 : CollisionObject(x, y, tex), 
 speed(ENEMY_WALKSPEED),
 health(hp), 
 dead(false),
 angry(false) {
 vel.x = (rand()%2*2-1) * speed; // either left or right walking
 facingLeft = (vel.x<0);
 visual.FlipX(facingLeft);
}

void Enemy::update(float dt, const Physics &phys) {
  vel += phys.gravity * dt;
  if (facingLeft) vel.setX(-speed, phys.gravAngle%180);
  else            vel.setX( speed, phys.gravAngle%180);
  
  // check X-direction
  pos.x += vel.x * dt;
  bool hitWall = false;
  float changeX = phys.testX(*this);
  while (changeX!=0) {  // as long as there are collisions with the level, keep checking
    pos.x += changeX;
    if (phys.gravAngle%180 == 0) hitWall = true;
    else vel.setY(0, phys.gravAngle);
    changeX = phys.testX(*this);
  }
  changeX = phys.testBoundsX(*this);
  if (changeX != 0) {
    pos.x += changeX;
    hitWall = true;
  }
  
  // check Y-direction
  pos.y += vel.y * dt;
  for (float changeY = phys.testY(*this); changeY!=0; changeY = phys.testY(*this)) {
    pos.y += phys.testY(*this); 
    if (phys.gravAngle%180 == 0) vel.setY(0, phys.gravAngle);
    else hitWall = true;
  }
  if (phys.testBoundsY(*this) < 0) {  // when fallen into the pit
    anger();
    dead = true;  // indicate death to reset
  }
  
  if (hitWall) {
    vel.setX(-1*vel.getX(phys.gravAngle), phys.gravAngle);
    facingLeft = !facingLeft;
  }
  
  visual.FlipX(facingLeft);
  rotate(phys.gravAngle);
  updateVisual();
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
