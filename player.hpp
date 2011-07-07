#include <SFML/Graphics.hpp>
#include "fvector.hpp"
#include "collisionObject.hpp"

class Player {
private:
  FVector pos;
  FVector vel;
  FVector dV;
  bool inAir;
  bool cancleJump;
  sf::Sprite img;
  
public:
  Player (float x, float y, const sf::Image &image);
  
  void checkKeys(sf::RenderWindow& rw);
  
  void update(int dt);
  
  bool colidesWith(CollisionObject o);
  
  sf::Drawable &draw();
};
