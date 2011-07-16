#include <iostream>
#include "collisionObject.hpp"
#include "level.hpp"
#include "player.hpp"
#include "physics.hpp"

Physics::Physics(Player &play, Level &level) : p(play), l(level) { }

void Physics::update(float dt) {
  p.update(dt);
  
  // level - player
  l.collidesWith(p);
  
  /* TODO:
  level  - enemy
  bullet - enemy
  player - enemy
  */
}

//void Physics::addPlatform(CollisionObject *platform) {   level.push_back(platform); }
void Physics::addEnemy   (CollisionObject *enemy   ) { enemies.push_back(enemy   ); }
void Physics::addBullet  (CollisionObject *bullet  ) { bullets.push_back(bullet  ); }

