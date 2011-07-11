
#include "collisionObject.hpp"

class Platform : public CollisionObject {
  //  collisionObject
  sf::Rect<float> box;
public:
  Platform(float x, float y, float wd, float ht);
  bool collidesWith(CollisionObject o);
};
