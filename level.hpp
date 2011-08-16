#include <SFML/Graphics.hpp>
#include <vector>

class CollisionObject; //forward declarations
class Platform;
class Player;

class Level {
  sf::Image platformTexture;
public:
  std::vector<Platform> platforms;
  
  // Constructor
  Level(sf::Image &lvl);
  
  bool collidesWith(CollisionObject &p);
};
