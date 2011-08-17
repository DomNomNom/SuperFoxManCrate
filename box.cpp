#include <math.h>
#include "utils.hpp"
#include "player.hpp"
#include "box.hpp"

#define MIN_DISTANCE 3*TILE_SIZE

Box::Box(float x, float y, sf::Image &pic, const sf::Image &lvl, const Player &play) 
 : CollisionObject(x, y, pic.GetWidth(), 
 pic.GetHeight()), 
 visual(pic), 
 player(play) { 
  vel.y = 0.00001;
  
  // get the spawnPoints from the level
  int imgWd = lvl.GetWidth();
  int imgHt = lvl.GetHeight();
  for (int y=0; y<imgHt; ++y) 
    for (int x=0; x<imgWd; ++x) 
      if (lvl.GetPixel(x, y) == sf::Color::Yellow)
        spawnPoints.push_back(sf::Vector2<float>(x,y));

  newPosition();
  update(0); 
}

void Box::newPosition() {
  do {
    int index = rand() % spawnPoints.size();
    pos.x = spawnPoints[index].x * TILE_SIZE;
    pos.y = spawnPoints[index].y * TILE_SIZE;
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
