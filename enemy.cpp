#include "enemy.hpp"
#include "utils.hpp"

#define ENEMY_WALKSPEED 0.05

Enemy::Enemy(float x, float y, sf::Image &pic) : CollisionObject(x, y, TILE_SIZE, TILE_SIZE), tile(pic) {
  vel.x = ENEMY_WALKSPEED;
  dead = false;
}

void Enemy::update(float dt) {
  vel.y += GRAVITY * dt;
  pos += vel * dt;
  
  if (pos.x > WIDTH -TILE_SIZE) { pos.x = WIDTH -TILE_SIZE;  vel.x=-ENEMY_WALKSPEED; }
  if (pos.y > HEIGHT-TILE_SIZE) { dead=true; }
  if (pos.x < 0) { pos.x=0; vel.x=ENEMY_WALKSPEED; }
  if (pos.y < 0) { pos.y=0; vel.y=0; }

  tile.SetPosition(pos.x, pos.y);
  tile.FlipX(vel.x<0);
}

bool Enemy::collidesWith(CollisionObject &o) {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + TILE_SIZE, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + TILE_SIZE, o.pos.y + o.sz.y);
  // If the intersection is valid (positive non zero area), then there is an intersection
  if ((left < right) && (top < bottom)) {
    if (vel.y > 0) {
      pos.y = o.pos.y - TILE_SIZE;
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
