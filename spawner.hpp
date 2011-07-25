#include <SFML/Graphics.hpp>

class Enemy;

class Spawner {
  int x, y;
  std::vector<Enemy> &enemies;
  sf::Image enemyTile;
public:
  Spawner(int X, int Y, std::vector<Enemy> &e);
  void update();
};
