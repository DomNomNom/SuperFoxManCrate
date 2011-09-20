#include "utils.hpp"
#include "player.hpp"
#include "spawnPoint.hpp"
#include "box.hpp"

#define MIN_DISTANCE 4*TILE_SIZE

Box::Box(float x, float y, sf::Texture &pic, const sf::Image &lvl, const Player &play) 
 : CollisionObject(x, y, pic),  
 player(play),
 spawn(lvl, sf::Color::Yellow) { 
  newPosition();
}

void Box::newPosition() {
  vel.y = 0.00001;
  vel.x = 0;
  do {
    pos = spawn.getPos();
  } while(hypot(pos.x-player.pos.x, pos.y-player.pos.y) < MIN_DISTANCE);
}

void Box::update(float dt, const Physics &phys) {
  vel += phys.gravity * dt;
  pos += vel * dt;
  for (float changeY = phys.testY(*this); changeY!=0; changeY = phys.testY(*this)) {
    pos.y += phys.testY(*this); 
    vel.y = 0;
  }
  if (phys.testBoundsY(*this) != 0) newPosition();
  pos.x += phys.testBoundsX(*this);
  
  updateVisual();
}
