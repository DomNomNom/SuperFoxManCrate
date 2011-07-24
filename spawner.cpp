#include "enemy.hpp"
#include "spawner.hpp"

Spawner::Spawner(int X, int Y, std::vector<Enemy> &e) : x(X), y(Y), enemies(e) { }

void Spawner::update() {

}
