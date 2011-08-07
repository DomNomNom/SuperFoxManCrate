#include <iostream>
#include "collisionObject.hpp"
#include "bullets/bullet.hpp"
#include "level.hpp"
#include "player.hpp"
#include "physics.hpp"
#include "enemy.hpp"
#include "utils.hpp"

Physics::Physics(Player &play, Level &level, std::vector<Bullet> &b, std::vector<Enemy> &e) : p(play), l(level), bullets(b), enemies(e) { }


void Physics::update(float dt) {
  // update stuff
  p.update(dt);
  for (int i=0; i<enemies.size(); ++i) enemies[i].update(dt);
  for (int i=0; i<bullets.size(); ++i) bullets[i].update(dt);
  
  
  // collide stuff
  l.collidesWith(p);                   // level - player
  for (int i=0; i<enemies.size(); ++i) // level - enemy 
    l.collidesWith(enemies[i]);  
  for (int i=0; i<bullets.size(); ++i) {  // level - bullet
    if (l.collidesWith(bullets[i]) || outsideBounds(bullets[i])) {
      if (bullets[i].explosive) ;// TODO: explode
      bullets.erase(bullets.begin() + i);
    }
  }
  
  for (int i=0; i<enemies.size(); ++i) { // player - enemy
    if (p.collidesWith(enemies[i])) {
      p.dead = true;
      break;
    }
  }
  
  
  // check for bullet death and remove
  for (int i=0; i<bullets.size(); ++i) {
    if (bullets[i].dead) {
      enemies.erase(enemies.begin() + i); /// WTF man, WTF?!?!
      --i;
    }
  } 
  
  for (int b=0; b<bullets.size(); ++b) { // bullet - enemy
    for (int e=0; e<enemies.size(); ++e) {
      if (bullets[b].collidesWith(enemies[e]) ) {
        enemies[e].hurt(bullets[b].damadge);
        if (enemies[e].dead) enemies.erase(enemies.begin() + e);
        bullets.erase(bullets.begin() + b);
        --b;
        break;
      }
    }
  }
}

bool Physics::outsideBounds(CollisionObject &o) {
  if (
    o.pos.x < 0 ||
    o.pos.y < 0 ||
    o.pos.x+o.sz.x > WIDTH  ||
    o.pos.y+o.sz.y > HEIGHT 
  ) return true;
  return false;
}
