#include <SFML/Graphics.hpp>
#include <vector>

class Platform; //forward declarations
class Player;

class Level {
  sf::Image platformTexture;
public:
  Level(const char *filePath);
  std::vector<Platform> platforms;
  
  //std::vector<sf::Sprite*> tiles;
  
  bool collidesWith(Player &p);
};
