#include <math.h>
#include "utils.hpp"
#include "player.hpp"
#include "spawnPoint.hpp"
#include "box.hpp"

#define MIN_DISTANCE 3*TILE_SIZE

Box::Box(float x, float y, sf::Image &pic, const sf::Image &lvl, const Player &play) 
 : CollisionObject(x, y, pic.GetWidth(), 
 pic.GetHeight()), 
 visual(pic), 
 player(play),
 spawn(lvl, sf::Color::Yellow) { 
  vel.y = 0.00001;
  
  newPosition();
  update(0); 
}

void Box::newPosition() {
  do {
    pos = spawn.getPos();
  } while(hypot(pos.x-player.pos.x, pos.y-player.pos.y) < MIN_DISTANCE);
}

void Box::update(float dt) {
  vel.y += GRAVITY * dt;
  pos += vel * dt;
  
  visual.SetPosition(pos.x, pos.y);
  visual.SetScale(1, 1);
}

bool Box::collidesWith(CollisionObject &o) {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.x, o.pos.y + o.sz.y);
  // If the intersection is valid (positive non zero area), then there is an intersection
  if ((left < right) && (top < bottom)) {
    if (vel.y > 0) {
      pos.y = o.pos.y - sz.y;
      vel.y = 0;
    }
    else {
      pos.y = o.pos.y + o.sz.y;
      vel.y = 0;
    }
    return true;
  }
  else return false;
}
