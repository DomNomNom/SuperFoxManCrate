#include <iostream>
#include <math.h>
#include "collisionObject.hpp"
#include "player.hpp"
#include "utils.hpp"

#define PLAYER_WALKSPEED 0.1
#define PLAYER_JUMP_STRENGTH 0.27
#define TILE_SIZE 8

Player::Player (float x, float y, sf::Image &playerImage) : CollisionObject(x, y, TILE_SIZE, TILE_SIZE), dead(false) {
  pos.x=x; pos.y=y;
  vel.x=0; vel.y=0;
  dV.x =0; dV.y =0;
  inAir = true;
  img.SetImage(playerImage);
}

void Player::checkKeys() {
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up)) {
    if (!inAir) { 
      vel.y -= PLAYER_JUMP_STRENGTH; 
      inAir = true; 
    }
    cancleJump = false;
  }
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))  ;
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))  { --dV.x; facingLeft = true;  }
  if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) { ++dV.x; facingLeft = false; }
}

void Player::update(float dt) {
  inAir = true;
  // calculate vel
  dV.y += GRAVITY;
  vel += dV * dt;
  vel.x = dV.x * PLAYER_WALKSPEED;
  if (inAir && vel.y<0 && cancleJump) vel.y = 0;  // cancle the jump if possible
  cancleJump = true;
  
  // calculate pos
  pos += vel * dt;
  
  dV.x=0; dV.y=0; // reset dV
  
  if (pos.x > WIDTH -TILE_SIZE) { pos.x = WIDTH -TILE_SIZE;  vel.x=0; }
  if (pos.y > HEIGHT-TILE_SIZE) { pos.y = HEIGHT-TILE_SIZE; vel.y=0; inAir=false; dead=true; }
  if (pos.x < 0) { pos.x=0; vel.x=0; }
  if (pos.y < 0) { pos.y=0; vel.y=0; }
}

sf::Drawable &Player::draw() {
  img.FlipX(facingLeft);  // TODO: moonWalk
  img.SetPosition(pos.x, pos.y);
  sf::Drawable &d = img;
  return d;
}

bool Player::collidesWith(CollisionObject &o) {
  // Compute the intersection boundaries
  float left   = std::max(pos.x,        o.pos.x);
  float top    = std::max(pos.y,        o.pos.y);
  float right  = std::min(pos.x + TILE_SIZE, o.pos.x + o.sz.x);
  float bottom = std::min(pos.y + TILE_SIZE, o.pos.y + o.sz.y);
  // If the intersection is valid (positive non zero area), then there is an intersection
  if ((left < right) && (top < bottom)) {
    if (vel.y > 0) {
      pos.y = o.pos.y - TILE_SIZE;
      vel.y = 0;
      inAir=false;
    }
    else {
      pos.y = o.pos.y + o.sz.y;
      vel.y = 0;
      inAir=true;
    }
    return true;
  }
  else return false;
}
