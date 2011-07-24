#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include <stdio.h>  // for fps text

#include "level.hpp"
#include "platform.hpp"
#include "guns/gun.hpp"
#include "bullet.hpp"
#include "physics.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "utils.hpp"


float scale = 4;  // grobal variable to be written to by main() and read by placeObject()
int screenWd; // faster than calling the function everytime
int screenHt;

sf::Drawable &placeObject(sf::Drawable &d) {
  d.SetScale(scale, scale); // scale size
  d.Move( // scale position
    d.GetPosition().x * (scale-1),
    d.GetPosition().y * (scale-1) 
  );
  d.Move( // shift to game top-left cornet
    screenWd/2 - scale*WIDTH/2, 
    screenHt/2 - scale*HEIGHT/2
  );
}

int main() {
  // create the window
  sf::VideoMode screen(sf::VideoMode::GetDesktopMode());
  sf::RenderWindow app(screen, "Hi World?", sf::Style::Fullscreen);
  app.SetFramerateLimit(60); // Limit to 60 frames per second
  app.EnableVerticalSync(true);
  //scale = screen.Height / (float)HEIGHT; // (un-)comment this line to enable/disable dynamic scaling
  //std::cout << "scale: x" << scale << std::endl;
  
  screenWd = sf::VideoMode::GetDesktopMode().Width;
  screenHt = sf::VideoMode::GetDesktopMode().Height;
  
  // bg image
  sf::Image bgImage;
  bgImage.LoadFromFile("images/bg.png");
  sf::Sprite bg;
  bg.SetImage(bgImage);
  bg.SetColor(sf::Color::Blue);
  placeObject(bg);
  
  // player
  sf::Image playerImage;
  playerImage.LoadFromFile("images/player_8x8.png");
  Player p(WIDTH/2, HEIGHT/2, playerImage);
    
  // Level
  Level level("levels/level1.png");
  for (int i=0; i<level.platforms.size(); ++i) {
    for (int j=0; j<level.platforms[i].tiles.size(); ++j) {
      placeObject(level.platforms[i].tiles[j]);
    }
  }
  
  // Bullets
  std::vector<Bullet> bullets;
  
  // Enemies
  sf::Image enemyTile;
  enemyTile.LoadFromFile("images/enemy.png");
  Enemy e1(WIDTH/2+2, 0, enemyTile);
  std::vector<Enemy> enemies;
  enemies.push_back(e1);  

  // Physics
  Physics phys(p, level, bullets, enemies);

  // leet FPS counter
  char fpsString[15]  = "";
  sf::Text fps;
  fps.SetColor(sf::Color(128, 0, 0));

  // main game loop
  while (app.IsOpened()) {
  
    // input
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Space)) usleep(50000); // space  => low framerate for testing (~19 fps)
    p.checkKeys();    // gets more raw keyboard input
    sf::Event event;  // process window events
    while (app.PollEvent(event)) {
      if (event.Type == sf::Event::Closed) app.Close(); // check for window exit
      else if(event.Type == sf::Event::KeyPressed) {    // check key events
        if (event.Key.Code == sf::Keyboard::Escape) app.Close();       // escape => exit
      }
    }
    
    // game logic
    float frameTime = app.GetFrameTime();
    phys.update(frameTime);
    
    // draw
    app.Clear();
    app.Draw(bg);
    app.Draw(placeObject(p.draw()));
    for (int i=0; i<enemies.size(); ++i)
      app.Draw(placeObject(enemies[i].tile));
    for (int i=0; i<level.platforms.size(); ++i)
      for (int j=0; j<level.platforms[i].tiles.size(); ++j)
        app.Draw(level.platforms[i].tiles[j]);
    
    sprintf(fpsString, "%.1f", 1000.f/frameTime); // fps
    fps.SetString(fpsString);
    app.Draw(fps);
    
    app.Display();
    
  }
  return EXIT_SUCCESS;
}
