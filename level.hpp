#include <SFML/Graphics.hpp>
#include <vector>

class CollisionObject; //forward declarations
class Platform;
class Player;

class Level {
public:
  std::vector<Platform> platforms;
  
  // Constructor
  Level(const sf::Image &lvl, const sf::Texture &tileTex);
  
  float testX(const CollisionObject &o) const;
  float testY(const CollisionObject &o) const;
  bool collidesWith(const CollisionObject &p) const;
};
