#include <iostream>
#include <math.h>
#include "collisionObject.hpp"
#include "player.hpp"
#include "utils.hpp"

#define PLAYER_WALKSPEED 0.005
#define PLAYER_JUMP_STRENGTH 0.27
#define TILE_SIZE 8

Player::Player (const sf::Texture &playerTexture, const sf::Image &lvl) 
 : CollisionObject(0, 0, playerTexture), 
 spawn(lvl, sf::Color::Red), 
 facingLeft(true), 
 freeFly(false) {
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
  playerControl.x = 0;
  playerControl.y = 0;
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
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))  { playerControl.x -= PLAYER_WALKSPEED; facingLeft = true;  }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) { playerControl.x += PLAYER_WALKSPEED; facingLeft = false; }
  }
}

void Player::update(float dt, const Physics &phys) {
  if (!freeFly) {
    inAir = true;
    // calculate vel
    dV += phys.gravity;
    vel += dV * dt;
    vel.x = dV.x * PLAYER_WALKSPEED;
    vel += playerControl * dt;
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
  vel.x -= playerControl.x * dt;
  
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
  vel.y -= playerControl.y * dt;
  
  dV.x=0; dV.y=0; // reset dV (change of velocity)
  
  visual.FlipX(facingLeft);  // TODO: moonWalk
  updateVisual();
}
