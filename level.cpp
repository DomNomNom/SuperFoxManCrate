#include <fstream>
#include <iostream>
#include "platform.hpp"
#include "player.hpp"
#include "level.hpp"
#include "utils.hpp"

Level::Level(const char *filePath) {
  platformTexture.LoadFromFile("images/platform.png");
  std::ifstream levelFile;
  levelFile.open(filePath);
  if (levelFile.is_open()) {
    for(int x,y,wd,ht; levelFile>>x && levelFile>>y && levelFile>>wd && levelFile>>ht; ) {   // read the file
      platforms.push_back(Platform(x*TILE_SIZE, y*TILE_SIZE, wd*TILE_SIZE, ht*TILE_SIZE, platformTexture));  // construct platforms
    }
    levelFile.close();
  }
}

bool Level::collidesWith(Player &p) {
  int collision = false;
  for (int i=0; i<platforms.size(); ++i) {
    if (p.collidesWith(platforms[i])) collision = true;
  }
  return collision;
}
