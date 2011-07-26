#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include <stdio.h>  // for fps text

#include "level.hpp"
#include "platform.hpp"
#include "guns/gun.hpp"
#include "bullets/bullet.hpp"
#include "physics.hpp"
#include "enemy.hpp"
#include "spawner.hpp"
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
  sf::Image playerLive; playerLive.LoadFromFile("images/player_8x8.png");
  sf::Image playerDead; playerDead.LoadFromFile("images/player_fail.png");
  Player p(WIDTH/2, HEIGHT/2, playerLive);
    
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
  std::vector<Enemy> enemies;
  Spawner spawner(WIDTH/2, 0, enemies);
  spawner.addEnemy();

  // Physics
  Physics phys(p, level, bullets, enemies);

  // leet FPS counter
  char fpsString[15];
  sf::Text fps;
  fps.SetColor(sf::Color(128, 0, 0));
  
  // high score timer
  sf::Clock gameTime;
  char timeString[15];
  bool playerDied = false;
  sf::Text timeText;
  timeText.SetCharacterSize(40);
  timeText.SetColor(sf::Color(200, 0, 0));
  timeText.SetPosition(screenWd/2-30, 0);
  
  // main game loop
  while (app.IsOpened()) {
  
    // input
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Dash)) usleep(50000); // space  => low framerate for testing (~19 fps)
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Return)) { // restart the game
      enemies.clear();
      spawner.reset();
      gameTime.Reset();
      playerDied = false;
      p = Player (WIDTH/2, HEIGHT/2, playerLive);
    }
    
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
    spawner.update();
    
    
    // do things with the dead
    if (p.dead) {
      p = Player(WIDTH/2, HEIGHT/2-4*TILE_SIZE, playerDead);
      playerDied = true;
    }
    if (!playerDied) {
      sprintf(timeString, "%.2f", gameTime.GetElapsedTime()/1000.f);   
      timeText.SetString(timeString);
    }
    
    // draw
    app.Clear();
    app.Draw(bg);
    app.Draw(placeObject(p.draw()));
    for (int i=0; i<enemies.size(); ++i)
      app.Draw(placeObject(enemies[i].tile));
    for (int i=0; i<level.platforms.size(); ++i)
      for (int j=0; j<level.platforms[i].tiles.size(); ++j)
        app.Draw(level.platforms[i].tiles[j]);
    
    // fps
    sprintf(fpsString, "fps: %.2f", 1000.f/frameTime); 
    fps.SetString(fpsString);
    app.Draw(fps);
    
    // record time
    app.Draw(timeText);
    
    app.Display();
    
  }
  return EXIT_SUCCESS;
}
