#include <iostream>
#include <math.h>
#include "player.hpp"
#include "utils.hpp"

#define PLAYER_WALKSPEED 0.3
#define PLAYER_GRAVITY 0.005
#define PLAYER_JUMP_STRENGTH 0.8
#define PLAYER_SIZE 16

Player::Player (float x, float y, const sf::Image &image) {
  pos.x=x; pos.y=y;
  vel.x=0; vel.y=0;
  dV.x =0; dV.y =0;
  inAir = true;
  img.SetImage(image);
}

void Player::checkKeys(sf::RenderWindow& rw) {
  if (rw.GetInput().IsKeyDown(sf::Key::Up)) {
    if (!inAir) { 
      vel.y -= PLAYER_JUMP_STRENGTH; 
      inAir = true; 
    }
    cancleJump = false;
  }
  if (rw.GetInput().IsKeyDown(sf::Key::Down))  ;
  if (rw.GetInput().IsKeyDown(sf::Key::Left))  { --dV.x; facingLeft = true;  }
  if (rw.GetInput().IsKeyDown(sf::Key::Right)) { ++dV.x; facingLeft = false; }
}

void Player::update(float dt) {
  //vel.y += dt * PLATER_GRAVITY
  // calculate vel
  dV.y += PLAYER_GRAVITY;
  vel += dV * dt;
  vel.x = dV.x * PLAYER_WALKSPEED;
  if (inAir && vel.y<0 && cancleJump) vel.y = 0;  // cancle the jump if possible
  cancleJump = true;
  
  // calculate pos
  pos += vel * dt;
  
  dV.x=0; dV.y=0;
  
  if (pos.x > WIDTH -PLAYER_SIZE) { pos.x = WIDTH -PLAYER_SIZE;  vel.x=0; }
  if (pos.y > HEIGHT-PLAYER_SIZE) { pos.y = HEIGHT-PLAYER_SIZE; vel.y=0; inAir=false; }
  if (pos.x < 0) { pos.x=0; vel.x=0; }
  if (pos.y < 0) { pos.y=0; vel.y=0; }
}

sf::Drawable &Player::draw() {
  img.FlipX(facingLeft);  // TODO: moonWalk
  img.SetPosition(pos.x, pos.y);
  sf::Drawable &d = img;
  return d;
}
