#include <SFML/Graphics.hpp>
#include <vector>

class CollisionObject; //forward declarations
class Platform;
class Player;

class Level {
  sf::Texture platformSprite;
public:
  std::vector<Platform> platforms;
  
  // Constructor
  Level(sf::Image &lvl);
  
  float testX(const CollisionObject &o) const;
  float testY(const CollisionObject &o) const;
  bool collidesWith(const CollisionObject &p) const;
};
