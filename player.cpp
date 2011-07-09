#include <iostream>
#include <math.h>
#include "player.hpp"
#include "utils.hpp"

#define PLAYER_WALKSPEED 0.3
#define PLAYER_GRAVITY 0.002
#define PLAYER_JUMP_STRENGTH 0.03
#define PLAYER_SIZE 16

Player::Player (float x, float y, const sf::Image &image) {
  pos.x=x; pos.y=y;
  vel.x=0; vel.y=0;
  dV.x =0; dV.y =0;
  inAir = true;
  img.SetImage(image);
  img.SetBlendMode(sf::Blend::Mode(3));
}

void Player::checkKeys(sf::RenderWindow& rw) {
  if (rw.GetInput().IsKeyDown(sf::Key::Up)) {
    if (!inAir) { 
      dV.y -= PLAYER_JUMP_STRENGTH; 
      inAir = true; 
    }
    cancleJump = false;
  }
  if (rw.GetInput().IsKeyDown(sf::Key::Down))  ;
  if (rw.GetInput().IsKeyDown(sf::Key::Left))  --dV.x;
  if (rw.GetInput().IsKeyDown(sf::Key::Right)) ++dV.x;
}

void Player::update(float dt) {
  
  dV.y += PLAYER_GRAVITY;

  // calculate vel
  vel += dV*dt;
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
  img.FlipX(vel.x<0);
  img.SetPosition(pos.x, pos.y);
  sf::Drawable &d = img;
  return d;
}
