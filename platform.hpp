#include <SFML/Graphics.hpp>
#include <vector>
#include "collisionObject.hpp"


class Platform : public CollisionObject {
  std::vector<sf::Sprite> tiles;
public:
  Platform(float x, float y, float wd, float ht, sf::Image &texture);
  bool collidesWith(CollisionObject o);
  std::vector<sf::Sprite> *draw();
};