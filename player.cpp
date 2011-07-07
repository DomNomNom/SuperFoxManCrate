#include <iostream>

#include "player.hpp"
#include "utils.hpp"

#define PLAYER_WALKSPEED 0.01
#define PLAYER_GRAVITY 0.001
#define PLAYER_SIZE 16
#define PLAYER_GROUND_FRICTION 0.5

Player::Player (float x, float y, const sf::Image &image) {
  pos.x=x; pos.y=y;
  vel.x=0; vel.y=0;
  dV.x =0; dV.y =0;
  img.SetImage(image);
  //img.SetBlendMode(sf::Blend::Mode(2));
}

void Player::checkKeys(sf::RenderWindow& rw) {
  if (rw.GetInput().IsKeyDown(sf::Key::Up)) {
    if (!inAir) { 
      dV.y -= 20*PLAYER_GRAVITY; 
      inAir = true; 
    }
    cancleJump = false;
  }
  if (rw.GetInput().IsKeyDown(sf::Key::Down))  ;
  if (rw.GetInput().IsKeyDown(sf::Key::Left))  dV.x -= PLAYER_WALKSPEED;
  if (rw.GetInput().IsKeyDown(sf::Key::Right)) dV.x += PLAYER_WALKSPEED;
}

void Player::update(int dt) {
  dV.y += PLAYER_GRAVITY;
  
  // calculate vel
  FVector acceleration = dV;
  acceleration *= dt;
  vel += acceleration;
  vel.x *= (1.f-PLAYER_GROUND_FRICTION);
  if (inAir && vel.y<0 && cancleJump) vel.y = 0;
  cancleJump = true;
  
  // calculate pos
  FVector dx = vel;
  dx *= dt;
  pos += dx;
  
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
