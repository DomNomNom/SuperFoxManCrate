#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "collisionObject.hpp"

class Player {
private:
  sf::Vector2<float> pos;
  sf::Vector2<float> vel;
  sf::Vector2<float> dV;
  bool inAir;
  bool cancleJump;
//  float jumpStartHeight;
//  float jumpStartTime;
  bool facingLeft;
  sf::Sprite img;
  
public:
  Player(float x, float y, const sf::Image &image);
  
  void checkKeys();
  
  void update(float dt);  // dt: delta time => frameTime
  
  bool collidesWith(CollisionObject &o);
  
  sf::Drawable &draw();
};
