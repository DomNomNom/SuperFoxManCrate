#include <iostream>
#include "player.hpp"

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
        playerControl.y = -PLAYER_JUMP_STRENGTH;
        inAir = true;
      }
      cancleJump = false;
    }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))  ;
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))  { playerControl.x -= PLAYER_WALKSPEED; facingLeft = true;  }
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) { playerControl.x += PLAYER_WALKSPEED; facingLeft = false; }
  }
}

void Player::canGoX(float dt, const Physics &phys) {
  pos.x += vel.x * dt;
  for (float changeX = phys.testX(*this); changeX!=0; changeX = phys.testX(*this)) {  // as long as there are collisions, keep checking
    pos.x += changeX;
    vel.x = 0;
    if (changeX*cos(phys.gravAngle/180*M_PI) < 0 && abs(changeX)<=abs(phys.testY(*this))) inAir = false;
  }
  if (phys.testBoundsX(*this) != 0) {
    pos.x += phys.testBoundsX(*this);
    vel.x = 0;
  }
}

void Player::canGoY(float dt, const Physics &phys) {
  pos.y += vel.y * dt;
  for (float changeY = phys.testY(*this); changeY!=0; changeY = phys.testY(*this)) {
    pos.y += changeY; 
    vel.y = 0;
    if (changeY*cos(phys.gravAngle/180*M_PI) < 0 && abs(changeY)<=abs(phys.testX(*this))) inAir = false;
  }
  if (phys.testBoundsY(*this) < 0) {  // when fallen into the pit
    dead = true;  // indicate death to reset
  }
}

void Player::update(float dt, const Physics &phys) {
  if (!freeFly) {
    inAir = true;
    vel += phys.gravity * dt;
    
    setX(vel, 0, phys.gravAngle);
    add(vel, (playerControl*dt).x, (playerControl).y, phys.gravAngle); 
    
    if (inAir && getY(vel, phys.gravAngle)<0 && cancleJump) setY(vel, 0, phys.gravAngle);  // cancle the jump if possible
    cancleJump = true;
  }
  
  // calculate posistion

  // check X-direction
  if ((phys.gravAngle+0)%180 == 0) {
    canGoX(dt, phys);
    canGoY(dt, phys);
  }
  else {
    canGoY(dt, phys);
    canGoX(dt, phys);
  }  
  // check Y-direction
  
  visual.FlipX(facingLeft);  // TODO: moonWalk
  updateVisual();
}
