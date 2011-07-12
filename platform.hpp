
#include "collisionObject.hpp"

class Platform : public CollisionObject {
  //  collisionObject
public:
  Platform(float x, float y, float wd, float ht);
  bool collidesWith(CollisionObject o);
};
