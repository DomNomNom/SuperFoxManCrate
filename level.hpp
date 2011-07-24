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
  Level(const char *filePath);
  
  bool collidesWith(CollisionObject &p);
};
