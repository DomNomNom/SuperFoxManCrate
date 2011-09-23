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
  setX(vel, 0, phys.gravAngle);
  vel += phys.gravity * dt;
//  pos += vel * dt;
  
  if ((phys.gravAngle+0)%180 == 0) {
    canGoX(dt, phys);
      canGoY(dt, phys);
  }
  else {
      canGoX(dt, phys);
      canGoY(dt, phys);
  }
  
  updateVisual();
}

void Box::canGoX(float dt, const Physics &phys) {
  pos.x += vel.x * dt;
  for (float changeX = phys.testX(*this); changeX!=0; changeX = phys.testX(*this)) {  // as long as there are collisions, keep checking
    pos.x += changeX;
    vel.x = 0;
  }
  if (phys.testBoundsX(*this) != 0) {
    pos.x += phys.testBoundsX(*this);
    vel.x = 0;
  }
}

void Box::canGoY(float dt, const Physics &phys) {
  pos.y += vel.y * dt;
  for (float changeY = phys.testY(*this); changeY!=0; changeY = phys.testY(*this)) {
    pos.y += changeY; 
    vel.y = 0;
  }
}
