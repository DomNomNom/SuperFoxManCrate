#include <vector>
#include "collisionObject.hpp"


struct Platform : public CollisionObject {
  std::vector<sf::Sprite> tiles;
  Platform(float x, float y, float wd, float ht, const sf::Texture &tex);
};
