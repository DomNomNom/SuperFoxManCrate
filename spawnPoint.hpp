#ifndef SPAWN_POINT_HPP
#define SPAWN_POINT_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class SpawnPoint {
  std::vector<sf::Vector2<float> > points;

public:
  SpawnPoint(const sf::Image &lvl, const sf::Color &c);
  
  sf::Vector2<float> &getPos();
};

#endif
