#include <cmath>
#include <iostream>

#include "explosion.hpp"

#define MAX_RADIUS 40
#define SPREAD_SPEED 0.1
#define INIT_RADIUS 1

Explosion::Explosion(float x, float y) : CollisionObject(x, y, 1, 1), dead(false), radius(INIT_RADIUS) {
  timer.Reset();
  visual = sf::Shape::Circle(0, 0, INIT_RADIUS, sf::Color(255, 255, 0), false, sf::Color(0, 0, 0));
  visual.SetOrigin(0, 0);
  update(0);
}

void Explosion::update(float dt) {
  if (radius > MAX_RADIUS) dead = true;
  else {
    radius += SPREAD_SPEED * dt;
    visual.SetPosition(pos.x, pos.y);
    visual.SetScale(radius, radius);
  }
}

bool Explosion::collidesWith(CollisionObject &o) {
//  std::cout << "collision :" << hypot(pos.x - (o.pos.x), pos.y - (o.pos.y)) << " - " << radius << std::endl;
  if ( // any of the four corners are within the circle
    hypot(pos.x - (o.pos.x       ), pos.y - (o.pos.y       )) <= radius  ||
    hypot(pos.x - (o.pos.x+o.sz.x), pos.y - (o.pos.y       )) <= radius  ||
    hypot(pos.x - (o.pos.x       ), pos.y - (o.pos.y+o.sz.y)) <= radius  ||
    hypot(pos.x - (o.pos.x+o.sz.x), pos.y - (o.pos.y+o.sz.y)) <= radius 
  ) return true;  // radius * constant ?? wtf?
  return false;
}

