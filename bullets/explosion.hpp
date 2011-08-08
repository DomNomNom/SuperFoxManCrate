#include <SFML/Graphics.hpp>

#include "../collisionObject.hpp"

class Explosion : public CollisionObject {
  sf::Clock timer;
  float radius;
public:
  sf::Shape visual;
  bool dead;
  Explosion(float x, float y);
  void update(float dt);
  bool collidesWith(CollisionObject &o);
};
