#include <SFML/Graphics.hpp>

class Enemy;

class Spawner {
  int x, y;
  sf::Image enemyTile;
  sf::Clock spawnTime;  // in millis
  std::vector<Enemy> &enemies;
public:
  Spawner(int X, int Y, std::vector<Enemy> &e);
  void addEnemy();
  void update();
};
