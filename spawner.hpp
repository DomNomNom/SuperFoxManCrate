#include <SFML/Graphics.hpp>
#include "spawnPoint.hpp"

class Enemy;

class Spawner {
  SpawnPoint spawn;
  sf::Image enemyTile;
  sf::Image largeTile;
  sf::Clock spawnTime;  // in millis
  std::vector<Enemy> &enemies;
public:
  Spawner(std::vector<Enemy> &e, const sf::Image &lvl);
  void addEnemy();
  void update();
  void reset();
};
