#include <iostream>
#include <algorithm>  // for min and max
#include "collisionObject.hpp"

CollisionObject::CollisionObject(float x, float y, const sf::Texture &tex) : pos(x, y), visual(tex), vel(0, 0), sz(tex.GetWidth(), tex.GetHeight()) {
  updateVisual();
}

void CollisionObject::update(float dt) {
  pos += vel * dt;
  updateVisual();
}

void CollisionObject::updateVisual() {
  visual.SetPosition(pos.x, pos.y);
  visual.SetScale(1, 1);
}

void CollisionObject::rotate(float angle) {
  angle *= -1;
  visual.SetOrigin(0, 0);
  visual.SetRotation(angle);
  visual.SetOrigin( // make it seem as if rotating around the centre of the object
    sz.x/2 - (sqrt(2))*(sz.x/2)*sin((angle+45)*2*M_PI/360.0), 
    sz.y/2 - (sqrt(2))*(sz.y/2)*cos((angle+45)*2*M_PI/360.0)
  );
}

float CollisionObject::testX(const CollisionObject &o) const {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.y, o.pos.y + o.sz.y);
  if ((left < right) && (top < bottom)) {  // If the intersection is valid (positive non zero area), then there is an intersection
    if (o.vel.x < 0)      return (pos.x + sz.x) - o.pos.x;  // if moving left,  push right
    else if (o.vel.x > 0) return (pos.x-o.sz.x) - o.pos.x;  // if moving right, push left
    else { // if not moving at all, PANIC!?
      std::cout << "Collision panic X" << std::endl; 
      return -0.1; 
    }    
  }
  else return 0;
}

float CollisionObject::testY(const CollisionObject &o) const {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.y, o.pos.y + o.sz.y);
  if ((left < right) && (top < bottom)) {  // If the intersection is valid (positive non zero area), then there is an intersection
    if (o.vel.y < 0)      return (pos.y + sz.y) - o.pos.y;  // if moving left,  push right
    else if (o.vel.y > 0) return (pos.y-o.sz.y) - o.pos.y;  // if moving right, push left
    else { // if not moving at all, PANIC!?
      std::cout << "Collision panic Y" << std::endl; 
      return -0.1; 
    }    
  }
  else return 0;
}

bool CollisionObject::collidesWith(const CollisionObject &o) const {
    // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + sz.x, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + sz.y, o.pos.y + o.sz.y);
  return ((left < right) && (top < bottom));  // If the intersection is valid (positive non zero area), then there is an intersection
}

// adds dX and dY to the vector with respect to the angle
void CollisionObject::add(sf::Vector2<float> &vector, float dX, float dY, int angle) {
  switch (angle) {
    case 0*90:
      vector.x += dX;
      vector.y += dY;
      break;
    case 1*90:
      vector.x += dY;
      vector.y -= dX;
      break;
    case 2*90:
      vector.x -= dX;
      vector.y -= dY;
      break;
    case 3*90:
      vector.x -= dY;
      vector.y += dX;
      break;
    default:
      vector.x = NAN;
      vector.y = NAN;
  }
}

void CollisionObject::set(sf::Vector2<float> &vector, float x, float y, int angle) {
  setX(vector, x, angle);
  setY(vector, y, angle);
}

void CollisionObject::setX(sf::Vector2<float> &vector, float x, int angle) {
  switch (angle) {
    case 0*90:  vector.x =  x;  break;
    case 1*90:  vector.y =  x;  break;
    case 2*90:  vector.x = -x;  break;
    case 3*90:  vector.y = -x;  break;
    default:    vector.x = NAN;
  }
}

void CollisionObject::setY(sf::Vector2<float> &vector, float y, int angle) {
  switch (angle) {
    case 0*90:  vector.y =  y;  break;
    case 1*90:  vector.x = -y;  break;  
    case 2*90:  vector.y = -y;  break;
    case 3*90:  vector.x =  y;  break;
    default:    vector.y = NAN;
  }
}


float CollisionObject::getX(const sf::Vector2<float> &vector, int angle) {
  switch (angle) {
    case 0*90:  return  vector.x;
    case 1*90:  return  vector.y;
    case 2*90:  return -vector.x;
    case 3*90:  return -vector.y;
    default:    return NAN;
  }
}

float CollisionObject::getY(const sf::Vector2<float> &vector, int angle) {
  switch (angle) {
    case 0*90:  return  vector.y;
    case 1*90:  return  vector.x;
    case 2*90:  return -vector.y;
    case 3*90:  return -vector.x;
    default:    return NAN;
  }
}

