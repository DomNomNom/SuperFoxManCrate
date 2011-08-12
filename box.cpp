#include "math.h"
#include "utils.hpp"
#include "box.hpp"

#define MIN_DISTANCE 3*TILE_SIZE

Box::Box(float x, float y, sf::Image &pic) : CollisionObject(x, y, pic.GetWidth(), pic.GetHeight()), visual(pic) { 
  vel.y = 0.00001;
  update(0); 
}

void Box::newPosition(float notX, float notY) {
  while(hypot(pos.x-notX, pos.y-notY) < MIN_DISTANCE) {
    pos.x = rand() % (WIDTH -TILE_SIZE);
    pos.y = rand() % (HEIGHT-TILE_SIZE);
  }  
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
