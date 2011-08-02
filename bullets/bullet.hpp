#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "../collisionObject.hpp"

class Bullet : public CollisionObject {
public:
  bool dead;
  int damadge;
  sf::Sprite visual;
  Bullet(float x, float y, float v_x, float v_y, sf::Image &tex, int dmg);
  void update(float dt);
  bool collidesWith(CollisionObject &o);
};
