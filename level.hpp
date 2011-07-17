#include <SFML/Graphics.hpp>
#include <vector>

class Platform; //forward declarations
class Player;

class Level {
  sf::Image platformTexture;
  std::vector<Platform> platforms;
public:
  Level(const char *filePath);
  
  std::vector<sf::Sprite*> tiles;
  
  bool collidesWith(Player &p);
};
