#include "iostream"
#include "utils.hpp"
#include "platform.hpp"

Platform::Platform(float X, float Y, float wd, float ht, sf::Texture &tex) : CollisionObject(X, Y, tex) {
  sz.x = wd;
  sz.y = ht;
  for (int y=0; y<ht/TILE_SIZE; ++y) {
    for (int x=0; x<wd/TILE_SIZE; ++x) {
      tiles.push_back(sf::Sprite());
      tiles[tiles.size()-1].SetTexture(tex);
      tiles[tiles.size()-1].SetPosition(X+x*TILE_SIZE, Y+y*TILE_SIZE);
    }
  }
}


std::vector<sf::Sprite> *Platform::draw() {
  return &tiles;
}

