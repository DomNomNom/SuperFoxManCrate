#include <SFML/Graphics.hpp>
#include "collisionObject.hpp"

class Box : public CollisionObject {
public:
  sf::Sprite visual;

  Box(float x, float y, sf::Image &pic);
  
  void update(float dt);
  
  void newPosition(float notX, float notY);
  
  bool collidesWith(CollisionObject &o);  
};
