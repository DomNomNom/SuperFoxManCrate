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
  
  bool collidesWith(CollisionObject &p);
};
