#include <iostream>

#include "explosion.hpp"

#define MAX_RADIUS 15
#define SPREAD_SPEED 0.05
#define OUTLINE_RATIO 4

Explosion::Explosion(float x, float y) : CollisionObject(x, y, 1, 1), dead(false), radius(0) {
  timer.Reset(); 
  visual = sf::Shape::Circle(0,0, OUTLINE_RATIO, sf::Color(255, 255, 0), true, sf::Color(0, 0, 0));
  visual.SetOrigin(0, 0);
  update(0);
}

void Explosion::update(float dt) {
  if (radius > MAX_RADIUS) dead = true;
  else {
    radius += SPREAD_SPEED * dt;
    visual.SetScale(radius*2/OUTLINE_RATIO, radius*2/OUTLINE_RATIO);
    visual.SetPosition(pos.x-radius/OUTLINE_RATIO, pos.y-radius/OUTLINE_RATIO);
  }
}

bool Explosion::collidesWith(CollisionObject &o) {
  return true; // i pwn everything =p
}

