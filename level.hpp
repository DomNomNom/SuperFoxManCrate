#include <SFML/Graphics.hpp>
#include <vector>

class Platform; //forward declarations
class Player;

class Level {
  sf::Image platformTexture;
public:
  std::vector<Platform> platforms;
  
  // Constructor
  Level(const char *filePath);
  
  bool collidesWith(Player &p);
};
