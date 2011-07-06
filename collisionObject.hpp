class CollisionObject {
  FVector pos;
  FVector vel;
  float wd;
  float ht;
  
  virtual bool collideWith(CollisionObject o);
  
};
