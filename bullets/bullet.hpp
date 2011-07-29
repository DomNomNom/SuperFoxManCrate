#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "../collisionObject.hpp"

class Bullet : CollisionObject {
public:
  bool dead;
  sf::Sprite visual;
  Bullet(float x, float y, float v_x, float v_y, sf::Image &texture);
  void update(float dt);
};
