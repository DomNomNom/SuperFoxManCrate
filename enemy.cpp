#include <stdlib.h>  // for rand()

#include "utils.hpp"
#include "enemy.hpp"

#define ENEMY_GRAVITY 0.0015
#define ENEMY_WALKSPEED 0.05
#define ENEMY_ANGER_SPEED 0.1

Enemy::Enemy(float x, float y, int hp, const sf::Image &pic) 
 : CollisionObject(x, y, pic.GetWidth(), pic.GetHeight()), 
 speed(ENEMY_WALKSPEED), 
 visual(pic),
 health(hp), 
 dead(false),
 angry(false) {
  vel.x = (rand()%2*2-1) * speed; // either left or right walking
  update(0);
}

void Enemy::update(float dt) {
  vel.y += ENEMY_GRAVITY * dt;
  pos += vel * dt;
  
  if (pos.x > WIDTH -TILE_SIZE) { pos.x = WIDTH -TILE_SIZE;  vel.x=-speed; }
  if (pos.y > HEIGHT-TILE_SIZE) { dead=true; anger(); }
  if (pos.x < 0) { pos.x=0; vel.x=speed; }
  if (pos.y < 0) { pos.y=0; vel.y=0; }

  visual.SetPosition(pos.x, pos.y);
  visual.FlipX(vel.x<0);
  visual.SetScale(1, 1);
}

bool Enemy::collidesWith(CollisionObject &o) {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.x, o.pos.y + o.sz.y);
  // If the intersection is valid (positive non zero area), then there is an intersection
  if ((left < right) && (top < bottom)) {
    if (vel.y > 0) {
      pos.y = o.pos.y - sz.y;
      vel.y = 0;
    }
    else {
      pos.y = o.pos.y + o.sz.y;
      vel.y = 0;
    }
    return true;
  }
  else return false;
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
