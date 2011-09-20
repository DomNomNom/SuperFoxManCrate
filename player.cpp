#include <iostream>
#include <math.h>
#include "collisionObject.hpp"
#include "player.hpp"
#include "utils.hpp"

#define PLAYER_WALKSPEED 0.1
#define PLAYER_JUMP_STRENGTH 0.27
#define TILE_SIZE 8

Player::Player (const sf::Texture &playerTexture, const sf::Image &lvl) : CollisionObject(0, 0, TILE_SIZE, TILE_SIZE), spawn(lvl, sf::Color::Red), facingLeft(true), freeFly(false) {
  reset(playerTexture);
}

void Player::reset(const sf::Texture &playerTexture) {
  visual.SetTexture(playerTexture);
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

void Player::update(float dt, const Physics &phys) {
  if (!freeFly) {
    inAir = true;
    // calculate vel
    dV += phys.gravity;
    vel += dV * dt;
    vel.x = dV.x * PLAYER_WALKSPEED;
    if (inAir && vel.y<0 && cancleJump) vel.y = 0;  // cancle the jump if possible
    cancleJump = true;
  }
  
  // calculate pos

  // check X-direction
  pos.x += vel.x * dt;
  for (float changeX = phys.testX(*this); changeX!=0; changeX = phys.testX(*this)) {  // as long as there are collisions, keep checking
    pos.x += changeX;
    vel.x = 0;
  }
  pos.x += phys.testBoundsX(*this);
  
  // check Y-direction
  pos.y += vel.y * dt;
  for (float changeY = phys.testY(*this); changeY!=0; changeY = phys.testY(*this)) {
    pos.y += phys.testY(*this); 
    vel.y = 0;
    if (changeY < 0) inAir = false;
  }
  if (phys.testBoundsY(*this) < 0) {  // when fallen into the pit
    dead = true;  // indicate death to reset
  }
  
  dV.x=0; dV.y=0; // reset dV (change of velocity)
  
  // update the visual
  visual.SetPosition(pos.x, pos.y);
  visual.FlipX(facingLeft);  // TODO: moonWalk
  visual.SetScale(1, 1);
}

void Player::rotate(float angle) {
  visual.SetOrigin(0, 0);
  visual.SetRotation(angle);
  visual.SetOrigin( // make it seem as if rotating around the centre of the object
    sz.x/2 - (sqrt(2))*(sz.x/2)*sin((angle+45)*2*M_PI/360.0), 
    sz.y/2 - (sqrt(2))*(sz.y/2)*cos((angle+45)*2*M_PI/360.0)
  );
}
