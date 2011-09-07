#include <math.h>
#include "utils.hpp"
#include "player.hpp"
#include "spawnPoint.hpp"
#include "box.hpp"

#define MIN_DISTANCE 3*TILE_SIZE

Box::Box(float x, float y, sf::Texture &pic, const sf::Image &lvl, const Player &play) 
 : CollisionObject(x, y, pic.GetWidth(), 
 pic.GetHeight()), 
 visual(pic), 
 player(play),
 spawn(lvl, sf::Color::Yellow) { 
  newPosition();
  visual.SetPosition(pos.x, pos.y);
}

void Box::newPosition() {
  vel.y = 0.00001;
  do {
    pos = spawn.getPos();
  } while(hypot(pos.x-player.pos.x, pos.y-player.pos.y) < MIN_DISTANCE);
}

void Box::update(float dt, const Physics &phys) {
  vel.y += GRAVITY * dt;
  pos += vel * dt;
  for (float changeY = phys.testY(*this); changeY!=0; changeY = phys.testY(*this)) {
    pos.y += phys.testY(*this); 
    vel.y = 0;
  }
  if (phys.testBoundsY(*this) != 0) newPosition();
  
  visual.SetPosition(pos.x, pos.y);
  visual.SetScale(1, 1);
}
