#include <iostream>
#include <math.h>
#include "collisionObject.hpp"
#include "player.hpp"
#include "utils.hpp"

#define PLAYER_WALKSPEED 0.1
#define PLAYER_JUMP_STRENGTH 0.27
#define TILE_SIZE 8

Player::Player (const sf::Image &playerImage, const sf::Image &lvl) : CollisionObject(0, 0, TILE_SIZE, TILE_SIZE), spawn(lvl, sf::Color::Red), facingLeft(true), freeFly(false) {
  reset(playerImage);
}

void Player::reset(const sf::Image &playerImage) {
  visual.SetImage(playerImage);
  pos = spawn.getPos();
  vel.x=0; vel.y=0;
  dV.x =0; dV.y =0;
  inAir = true;
  dead = false;
}

void Player::checkKeys() {
  if (freeFly) {
    vel.x=0; vel.y=0;
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))    { vel.y -= PLAYER_WALKSPEED; }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))  { vel.y += PLAYER_WALKSPEED; }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))  { vel.x -= PLAYER_WALKSPEED; facingLeft = true;  }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) { vel.x += PLAYER_WALKSPEED; facingLeft = false; }
  }
  else {
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
}

void Player::update(float dt) {
  if (!freeFly){
    inAir = true;
    // calculate vel
    dV.y += GRAVITY;
    vel += dV * dt;
    vel.x = dV.x * PLAYER_WALKSPEED;
    if (inAir && vel.y<0 && cancleJump) vel.y = 0;  // cancle the jump if possible
    cancleJump = true;
  }
  
  // calculate pos
  pos += vel * dt;
  
  dV.x=0; dV.y=0; // reset dV
  
  if (pos.x > WIDTH -TILE_SIZE) { pos.x = WIDTH -TILE_SIZE;  vel.x=0; }
  if (pos.y > HEIGHT-TILE_SIZE) { pos.y = HEIGHT-TILE_SIZE; vel.y=0; inAir=false; dead=true; }
  if (pos.x < 0) { pos.x=0; vel.x=0; }
  if (pos.y < 0) { pos.y=0; vel.y=0; }
  visual.SetPosition(pos.x, pos.y);
}

sf::Drawable &Player::draw() {
  visual.FlipX(facingLeft);  // TODO: moonWalk
  visual.SetScale(1, 1);
  sf::Drawable &d = visual;
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
