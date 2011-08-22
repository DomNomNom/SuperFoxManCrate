#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "collisionObject.hpp"
#include "spawnPoint.hpp"

class Player : public CollisionObject {
private:
  SpawnPoint spawn;
  sf::Vector2<float> dV;
  bool cancleJump;
  bool inAir;
  bool freeFly;
  sf::Sprite visual;
  
public:
  bool facingLeft;
  bool dead;

  Player(const sf::Texture &playerTexture, const sf::Image &lvl);
  
  void reset(const sf::Texture &playerTexture);
  
  void checkKeys();
  
  void update(float dt);  // dt: delta time => frameTime
  
  bool collidesWith(CollisionObject &o);
  
  sf::Drawable &draw();
};
