
#include "fvector.hpp"
#include "collisionObject.hpp"

class Player {
private:
  FVector pos;
  FVector vel;
  FVector dV;
  bool inAir;
public:
  Player (float x, float y);
  
  void checkKeys(sf::RenderWindow& rw);
  
  void update(int dt);
  
  
  bool colidesWith(CollisionObject o);
};
