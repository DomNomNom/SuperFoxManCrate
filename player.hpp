#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "collisionObject.hpp"

class Player : public CollisionObject {
private:
  sf::Vector2<float> dV;
  bool cancleJump;
  bool inAir;
  bool freeFly;
  sf::Sprite visual;
  
public:
  bool facingLeft;
  bool dead;

  Player(float x, float y, sf::Image &tile);
  
  void checkKeys();
  
  void update(float dt);  // dt: delta time => frameTime
  
  bool collidesWith(CollisionObject &o);
  
  sf::Drawable &draw();
};
