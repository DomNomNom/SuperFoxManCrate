#include <cmath>
#include <iostream>

#include "explosion.hpp"

#define MAX_RADIUS 20
#define SPREAD_SPEED 0.05
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
    visual.SetPosition(pos.x-radius, pos.y-radius);
    visual.SetScale(radius*2, radius*2);
  }
}

bool Explosion::collidesWith(CollisionObject &o) {
//  std::cout << "collision :" << hypot(pos.x - (o.pos.x), pos.y - (o.pos.y)) << " - " << radius << std::endl;
  if (hypot(pos.x - (o.pos.x+o.sz.x/2), pos.y - (o.pos.y+o.sz.y/2)) <= radius) return true;  // radius * constant ?? wtf?
  return false;
}

