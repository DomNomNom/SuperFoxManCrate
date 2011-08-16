#include <vector>
#include <SFML/Graphics.hpp>
#include "collisionObject.hpp"

class Player;

class Box : public CollisionObject {
  const Player &player;
  std::vector<sf::Vector2<float> > spawnPoints;
public:
  sf::Sprite visual;

  Box(float x, float y, sf::Image &pic, const sf::Image &lvl, const Player &play);
  
  void update(float dt);
  
  void newPosition();
  
  bool collidesWith(CollisionObject &o);  
};
