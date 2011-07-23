#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class CollisionObject;

class Player {
private:
  sf::Vector2<float> pos;
  sf::Vector2<float> vel;
  sf::Vector2<float> dV;
  bool cancleJump;
  bool facingLeft;
  bool inAir;
  sf::Sprite img;
  
public:
  Player(float x, float y, const sf::Image &image);
  
  void checkKeys();
  
  void update(float dt);  // dt: delta time => frameTime
  
  bool collidesWith(CollisionObject &o);
  
  sf::Drawable &draw();
};
