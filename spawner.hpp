
class Enemy;

class Spawner {
  int x, y;
  std::vector<Enemy> &enemies;
public:
  Spawner(int X, int Y, std::vector<Enemy> &e);
  void update();
};
