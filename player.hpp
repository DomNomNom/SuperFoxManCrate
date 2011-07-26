#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class CollisionObject;

class Player : public CollisionObject {
private:
  sf::Vector2<float> dV;
  bool cancleJump;
  bool facingLeft;
  bool inAir;
  sf::Sprite img;
  
public:
  bool dead;

  Player(float x, float y, sf::Image &tile);
  
  void checkKeys();
  
  void update(float dt);  // dt: delta time => frameTime
  
  bool collidesWith(CollisionObject &o);
  
  sf::Drawable &draw();
};
