#include "utils.hpp"
#include "spawnPoint.hpp"

SpawnPoint::SpawnPoint(const sf::Image &lvl, const sf::Color &c) {
  
  int imgWd = lvl.GetWidth();
  int imgHt = lvl.GetHeight();
      
  for (int y=0; y<imgHt; ++y)
    for (int x=0; x<imgWd; ++x)
      if (lvl.GetPixel(x, y) == c) points.push_back(sf::Vector2<float>(x*TILE_SIZE, y*TILE_SIZE));
    
  if (points.size() < 1) points.push_back(sf::Vector2<float>(0, 0));  // ensure at least one item is in points
}

sf::Vector2<float> &SpawnPoint::getPos() {
  int index = rand() % points.size();
  sf::Vector2<float> &position = points[index];
  return position;
}
