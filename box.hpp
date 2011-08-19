#ifndef BOX_HPP
#define BOX_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "collisionObject.hpp"
#include "spawnPoint.hpp"

class Player;

class Box : public CollisionObject {
  const Player &player;
  SpawnPoint spawn;
public:
  sf::Sprite visual;

  Box(float x, float y, sf::Image &pic, const sf::Image &lvl, const Player &play);
  
  void update(float dt);
  
  void newPosition();
  
  bool collidesWith(CollisionObject &o);  
};


#endif
