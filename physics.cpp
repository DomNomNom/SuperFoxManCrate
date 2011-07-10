#include <iostream>
#include "collisionObject.hpp"
#include "player.hpp"
#include "physics.hpp"

Physics::Physics(Player& play) : p(play) { }

void Physics::update(float dt) {
  p.update(dt);
  std::cout << dt << std::endl;
  //TODO: collisions
}

void Physics::addPlatform(CollisionObject *platform) {   level.push_back(platform); }
void Physics::addEnemy   (CollisionObject *enemy   ) { enemies.push_back(enemy   ); }
void Physics::addBullet  (CollisionObject *bullet  ) { bullets.push_back(bullet  ); }

