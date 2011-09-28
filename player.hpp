#include "vector2.hpp"
#include <SFML/Window/Event.hpp>  // for keyboard input
#include "physics.hpp"
#include "collisionObject.hpp"
#include "spawnPoint.hpp"

class Player : public CollisionObject {
private:
  SpawnPoint spawn;
  vector2<float> playerControl; // note: playerControl is relative to the players angle
  bool cancleJump;
  bool inAir;
  bool freeFly;
  
  void canGoX(float dt, const Physics &phys);  // helper functions for update()
  void canGoY(float dt, const Physics &phys);
  
public:
  bool facingLeft;
  bool dead;

  Player(const sf::Texture &playerTexture, const sf::Image &lvl);
  
  void reset(const sf::Texture &playerTexture);  
  void checkKeys();
  void update(float dt, const Physics &phys);  // dt: delta time => frameTime
};
