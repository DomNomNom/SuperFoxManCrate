#include <iostream>
#include "bullets/bullet.hpp"
#include "collisionObject.hpp"
#include "level.hpp"
#include "player.hpp"
#include "physics.hpp"
#include "enemy.hpp"

Physics::Physics(Player &play, Level &level, std::vector<Bullet> &b, std::vector<Enemy> &e) : p(play), l(level), bullets(b), enemies(e) { }


void Physics::update(float dt) {
  // update stuff
  p.update(dt);
  for (int i=0; i<enemies.size(); ++i) 
    enemies[i].update(dt);
  
  // collide stuff
  l.collidesWith(p);   // level - player
  /* TODO:
  level  - enemy
  bullet - enemy
  player - enemy
  */
}

void Physics::addBullet   (Bullet b) { bullets.push_back(b); }
