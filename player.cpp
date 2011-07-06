#include <SFML/Graphics.hpp>
#include "player.hpp"


#define PLAYER_WALKSPEED 1
#define PLAYER_GRAVITY 1

Player::Player (float x, float y) {
  pos.x=x; pos.y=y;
  vel.x=0; vel.y=0;
  dV.x =0; dV.y =0;
}

void Player::checkKeys(sf::RenderWindow& rw) {
  if (rw.GetInput().IsKeyDown(sf::Key::Up))    if (!inAir) dV.y -= PLAYER_GRAVITY;
  if (rw.GetInput().IsKeyDown(sf::Key::Down))  ;
  if (rw.GetInput().IsKeyDown(sf::Key::Left))  dV.x -= PLAYER_WALKSPEED;
  if (rw.GetInput().IsKeyDown(sf::Key::Right)) dV.x += PLAYER_WALKSPEED;
}

void Player::update(int dt) {
  dV.y += PLAYER_GRAVITY;

  FVector acceleration = dV;
  acceleration *= dt;
  vel += acceleration;
  FVector dx = vel;
  dx *= dt;
  pos += dx;
  
  if (pos.y > 256) pos.y = 256;
}

