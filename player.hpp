#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "physics.hpp"
#include "collisionObject.hpp"
#include "spawnPoint.hpp"

class Player : public CollisionObject {
private:
  Physics *phys;
  SpawnPoint spawn;
  sf::Vector2<float> dV;
  bool cancleJump;
  bool inAir;
  bool freeFly;
  
public:
  bool facingLeft;
  bool dead;
  sf::Sprite visual;

  Player(const sf::Texture &playerTexture, const sf::Image &lvl);
  void attachPhysics(Physics &p); // MUST be called after initialization of physics. (can't be called before since physics needs to know about the player),
  
  void reset(const sf::Texture &playerTexture);  
  void checkKeys();
  void update(float dt);  // dt: delta time => frameTime
  bool collidesWith(CollisionObject &o);
};
