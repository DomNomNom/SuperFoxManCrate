#include <stdlib.h>

#include "enemy.hpp"
#include "spawner.hpp"

#define SPAWN_INTERVAL 1500

Spawner::Spawner(std::vector<Enemy> &e, const sf::Image &lvl) : enemies(e), spawn(lvl, sf::Color::Green) {  
  enemyTile.LoadFromFile("resources/images/enemy.png");
  largeTile.LoadFromFile("resources/images/enemy_16x16.png");
}

void Spawner::update() {
  if (spawnTime.GetElapsedTime() > SPAWN_INTERVAL) {
    addEnemy();
    spawnTime.Reset();
  }
  for (int i=0; i<enemies.size(); ++i) {
    if (enemies[i].dead) {
      enemies[i].dead = false; // respawn =]
      enemies[i].pos = spawn.getPos();
    }
  }
}

void Spawner::addEnemy() { 
  sf::Vector2<float> pos = spawn.getPos();
  // 25% chance of a big one spawning
  if (rand()%4==0) enemies.push_back(Enemy(pos.x, pos.y, 10, largeTile)); 
  else             enemies.push_back(Enemy(pos.x, pos.y,  2, enemyTile)); 
}

void Spawner::reset() { spawnTime.Reset(); }
