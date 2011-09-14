#include <iostream>
#include "collisionObject.hpp"
#include "bullets/bullet.hpp"
#include "bullets/explosion.hpp"
#include "level.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "box.hpp"
#include "utils.hpp"
#include "physics.hpp"

Physics::Physics(Player &play, Level &level, std::vector<Bullet> &b, std::vector<Explosion> &x, std::vector<Enemy> &e, Box &bx) : 
  p(play), 
  l(level), 
  bullets(b), 
  explosions(x), 
  enemies(e),
  box(bx),
  gravity(0, 0.0007)
{ }


void Physics::update(float dt) {
  // update stuff
  p.update(dt, *this);
  box.update(dt, *this);
  for (int i=0; i<enemies.size(); ++i) enemies[i].update(dt, *this);
  for (int i=0; i<bullets.size(); ++i) bullets[i].update(dt);
  for (int i=0; i<explosions.size(); ++i) explosions[i].update(dt);
  
  // collide stuff
  for (int i=0; i<bullets.size(); ++i) {  // level - bullet
    if (l.collidesWith(bullets[i]) || outsideBounds(bullets[i])) {
      if (bullets[i].explosive) explosions.push_back(Explosion(bullets[i].pos.x, bullets[i].pos.y));
      bullets.erase(bullets.begin() + i);
    }
  }
  for (int i=0; i<enemies.size(); ++i) { // player - enemy
    if (p.collidesWith(enemies[i])) {
      p.dead = true;
      break;
    }
  }
  for (int b=0; b<explosions.size(); ++b) // explosion - enemy
    for (int e=0; e<enemies.size(); ++e)
      if (explosions[b].collidesWith(enemies[e]))
        enemies.erase(enemies.begin() + e);
  
  for (int i=0; i<bullets.size(); ++i) {  // check bullet death
    if (bullets[i].dead) {
      bullets.erase(bullets.begin() + i);
      --i;
    }
  } 
  for (int i=0; i<explosions.size(); ++i) { // check explosion death
    if (explosions[i].dead) {
      explosions.erase(explosions.begin() + i);
      --i;
    }
  }
  
        
  for (int b=0; b<bullets.size(); ++b) { // bullet - enemy
    for (int e=0; e<enemies.size(); ++e) {
      if (bullets[b].collidesWith(enemies[e]) ) {
        if (bullets[b].explosive) explosions.push_back(Explosion(bullets[b].pos.x, bullets[b].pos.y));
        enemies[e].hurt(bullets[b].damadge);
        if (enemies[e].dead) enemies.erase(enemies.begin() + e);
        bullets.erase(bullets.begin() + b);
        --b;
        break;
      }
    }
  }

}


bool Physics::collidesWithWorld(const CollisionObject &o) const {
  if (outsideBounds(o))  return true;
  if (l.collidesWith(o)) return true;
  return false;
}

float Physics::testX(const CollisionObject &o) const {
  return l.testX(o);  // test with level
}
float Physics::testY(const CollisionObject &o) const {
  return l.testY(o);  // test with level
}

float Physics::testBoundsX(const CollisionObject &o) const {
  if (o.pos.x < 0) return - o.pos.x;
  else if (o.pos.x + o.sz.x > WIDTH) return WIDTH - o.pos.x - o.sz.x;
  else return 0;
}
float Physics::testBoundsY(const CollisionObject &o) const {
  if (o.pos.y < 0) return - o.pos.y;
  else if (o.pos.y + o.sz.y > HEIGHT) return HEIGHT - o.pos.y - o.sz.y;  
  return 0;
}

bool Physics::outsideBounds(const CollisionObject &o) const {
  if (
    o.pos.x < 0 ||
    o.pos.y < 0 ||
    o.pos.x+o.sz.x > WIDTH  ||
    o.pos.y+o.sz.y > HEIGHT 
  ) return true;
  return false;
}

