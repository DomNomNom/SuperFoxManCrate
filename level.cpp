#include <fstream>
#include <iostream>
#include "platform.hpp"
#include "player.hpp"
#include "level.hpp"
#include "utils.hpp"

Level::Level(sf::Image &lvl) {
  platformSprite.LoadFromFile("resources/images/platform.png");
  
  int imgWd = lvl.GetWidth();
  int imgHt = lvl.GetHeight();
  
  bool isWall[imgWd][imgHt];
  for (int y=0; y<imgHt; ++y) 
    for (int x=0; x<imgWd; ++x) 
      isWall[x][y] = false;
      
  for (int y=0; y<imgHt; ++y) {
    for (int x=0; x<imgWd; ++x) {
      // search for new platfomrs
      if (!isWall[x][y] && lvl.GetPixel(x, y) == sf::Color::Black) {
        // figure out the collision rectangles
        int minHt = imgHt+1;
        int wd;
        // find the maximum rectangle width
        for (wd=0; x+wd<imgWd && lvl.GetPixel(x+wd, y) == sf::Color::Black; ++wd){
          // find the minimum rectangle height
          int ht=0;
          while (y+ht<imgHt && lvl.GetPixel(x+wd, y+ht) == sf::Color::Black) ++ht;
          if (ht < minHt) minHt = ht;
        }
        
        // mark the platfom area as processed
        for (int x2=x; x2<x+wd; ++x2) {
          for (int ht=0; ht<minHt; ++ht) {
            isWall[x2][y+ht] = true;
          }
        }
        
        // construct platforms
        platforms.push_back(Platform(x*TILE_SIZE, y*TILE_SIZE, wd*TILE_SIZE, minHt*TILE_SIZE, platformSprite));  
      }
    }
  }
}

float Level::testX(const CollisionObject &o) const {
  for (int i=0; i<platforms.size(); ++i) {
    if (platforms[i].testX(o) != 0) return platforms[i].testX(o);
  }
  return 0;
}

float Level::testY(const CollisionObject &o) const {
  for (int i=0; i<platforms.size(); ++i) {
    if (platforms[i].testY(o) != 0) return platforms[i].testY(o);
  }
  return 0;
}

bool Level::collidesWith(const CollisionObject &p) const {
  int collision = false;
  for (int i=0; i<platforms.size(); ++i) {
    if (p.collidesWith(platforms[i])) collision = true;
  }
  return collision;
}
