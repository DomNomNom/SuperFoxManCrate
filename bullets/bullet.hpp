#include <SFML/System/Vector2.hpp>

#include "../collisionObject.hpp"

class Bullet : CollisionObject {
  Bullet(float x, float y, float v_x, float v_y);
};
