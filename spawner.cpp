#include "enemy.hpp"
#include "spawner.hpp"

Spawner::Spawner(int X, int Y, std::vector<Enemy> &e) : x(X), y(Y), enemies(e) {  
  enemyTile.LoadFromFile("images/enemy.png");
}

void Spawner::update() {
  if (spawnTime.GetElapsedTime() > 1000) {
    addEnemy();
    spawnTime.Reset();
  }
  for (int i=0; i<enemies.size(); ++i) {
    if (enemies[i].dead) {  // respawn =]
      enemies[i] = Enemy(x, y, enemyTile);
    }
  }
}

void Spawner::addEnemy() { enemies.push_back(Enemy(x, y, enemyTile)); }
