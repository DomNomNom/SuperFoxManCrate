#include <stdlib.h>

#include "enemy.hpp"
#include "spawner.hpp"

Spawner::Spawner(int X, int Y, std::vector<Enemy> &e) : x(X), y(Y), enemies(e) {  
  enemyTile.LoadFromFile("images/enemy.png");
  largeTile.LoadFromFile("images/enemy_16x16.png");
}

void Spawner::update() {
  if (spawnTime.GetElapsedTime() > 1500) {
    addEnemy();
    spawnTime.Reset();
  }
  for (int i=0; i<enemies.size(); ++i) {
    if (enemies[i].dead) {
      enemies[i].dead = false; // respawn =]
      enemies[i].pos.x = x;
      enemies[i].pos.y = y;
    }
  }
}

void Spawner::addEnemy() { 
  // 25% chance of a big one spawning
  if (rand()%4==0) enemies.push_back(Enemy(x, y, 10, largeTile)); 
  else             enemies.push_back(Enemy(x, y,  2, enemyTile)); 
}

void Spawner::reset() { spawnTime.Reset(); }
