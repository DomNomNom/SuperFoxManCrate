#include <fstream>
#include <iostream>
#include "platform.hpp"
#include "player.hpp"
#include "level.hpp"
#include "utils.hpp"

Level::Level(sf::Image &lvl) {
  platformTexture.LoadFromFile("images/platform.png");
  
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
        int minHt = imgHt;
        int wd;
        // find the rectangle width
        for (wd=0; x+wd<imgWd && lvl.GetPixel(x+wd, y) == sf::Color::Black; ++wd){
          // find the minimum rectangle height
          int ht=1;
          while (y+ht<imgHt && lvl.GetPixel(x+wd, y+ht) == sf::Color::Black) ++ht;
          if (ht < minHt) minHt = ht;
        }
        // mark the platfom area as processed
        for (int x2=0; x2<x+wd; ++x2) {
          for (int ht=0; ht<minHt; ++ht) {
            isWall[x2][y+ht] = true;
          }
        }
        // construct platforms
        platforms.push_back(Platform(x*TILE_SIZE, y*TILE_SIZE, wd*TILE_SIZE, minHt*TILE_SIZE, platformTexture));  
      }
    }
  }
}

bool Level::collidesWith(CollisionObject &p) {
  int collision = false;
  for (int i=0; i<platforms.size(); ++i) {
    if (p.collidesWith(platforms[i])) collision = true;
  }
  return collision;
}
