#include "enemy.hpp"
#include "utils.hpp"

Enemy::Enemy(float x, float y, sf::Image &pic) : CollisionObject(x, y, TILE_SIZE, TILE_SIZE), tile(pic) {
  vel.x = 0.005;
}

void Enemy::update(float dt) {
  pos += vel * dt;
  tile.SetPosition(pos.x, pos.y);
}
