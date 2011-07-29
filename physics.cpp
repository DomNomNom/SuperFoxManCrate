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
  for (int i=0; i<enemies.size(); ++i) enemies[i].update(dt);
  for (int i=0; i<bullets.size(); ++i) bullets[i].update(dt);
  
  // check for death
  for (int i=0; i<bullets.size(); ++i) {
    if (bullets[i].dead) {
      enemies.erase(enemies.begin() + i);
      --i;
    }
  }
  
  // collide stuff
  l.collidesWith(p);   // level - player
  for (int i=0; i<enemies.size(); ++i) l.collidesWith(enemies[i]);  // level - enemy

  // player - enemy
  for (int i=0; i<enemies.size(); ++i) {
    if (p.collidesWith(enemies[i])) {
      p.dead = true;
      break;
    }
  }  
  
  /* TODO:
  level - bullet
  bullet - enemy
  */
}
