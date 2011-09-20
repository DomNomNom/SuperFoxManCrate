#ifndef BOX_HPP
#define BOX_HPP

#include <vector>
#include "collisionObject.hpp"
#include "spawnPoint.hpp"

class Player;

class Box : public CollisionObject {
  const Player &player;
  SpawnPoint spawn;

public:
  Box(float x, float y, sf::Texture &pic, const sf::Image &lvl, const Player &play);
  
  void update(float dt, const Physics &phys);  
  void newPosition();
};


#endif
