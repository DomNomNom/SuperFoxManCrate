#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <stdio.h>  // for text sprintf()

#include "level.hpp"
#include "platform.hpp"
#include "guns/gun.hpp"
#include "bullets/bullet.hpp"
#include "bullets/explosion.hpp"
#include "physics.hpp"
#include "enemy.hpp"
#include "spawner.hpp"
#include "player.hpp"
#include "utils.hpp"


float scale = 4;  // grobal variable to be written to by main() and read by placeObject()
int screenWd; // faster than calling the function everytime
int screenHt;

sf::Drawable &placeObject(sf::Drawable &d) {
  d.Scale(scale, scale); // scale size
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
  app.ShowMouseCursor(false);
  app.EnableVerticalSync(true);
  app.EnableKeyRepeat(false);
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
  sf::Image smallBullet; smallBullet.LoadFromFile("images/bullet_4x4.png");
  sf::Image largeBullet; largeBullet.LoadFromFile("images/bullet_8x8.png");
  sf::Image rocketShell; rocketShell.LoadFromFile("images/rocket_8x4.png");
  std::vector<Bullet> bullets;
  
  // Explosions
  std::vector<Explosion> explosions;
  
  // Guns
  //  <GunClass>     (bullets, p, <bulletImage>, <coolDn>, <dmg>, <#>, <vel_x/y>, <var_x/y>,  <acc_x/y>, <auto>, <explosive> );
  Gun pistol         (bullets, p, smallBullet,   100,       1,    1,   0.2,  0,   0,    0,    0,     0,  false,   false );
  Gun revolver       (bullets, p, largeBullet,   100,       5,    1,   0.2,  0,   0,    0,    0,     0,  false,   false );
  Gun shotgun        (bullets, p, smallBullet,   500,       1,    6,   0.2,  0,   0.05, 0.05, 0,     0,  false,   false );
  Gun mg             (bullets, p, smallBullet,    50,       1,    1,   0.2,  0,   0,    0.02, 0,     0,  true,    false );
  Gun rocketLauncher (bullets, p, rocketShell,  1000,      10,    1,   0.0,  0,   0,    0,    0.0005,0,  false,   true  );
  Gun *gun = &rocketLauncher;
    
  // Enemies
  std::vector<Enemy> enemies;
  Spawner spawner(WIDTH/2, 0, enemies);
  spawner.addEnemy();

  // Physics
  Physics phys(p, level, bullets, explosions, enemies);

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
    p.checkKeys();
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Dash)) usleep(50000); // space  => low framerate for testing (~19 fps)
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Return)) { // restart the game
      bullets.clear();
      enemies.clear();
      spawner.reset();
      gameTime.Reset();
      playerDied = false;
      p = Player (WIDTH/2, HEIGHT/2, playerLive);
    }
    
    sf::Event event;  // process window events
    while (app.PollEvent(event)) {
      if (event.Type == sf::Event::Closed) app.Close(); // check for window exit
      else if (event.Type == sf::Event::KeyPressed) {    // check key events
        if (event.Key.Code == sf::Keyboard::Escape) app.Close();       // escape => exit
        else if (event.Key.Code == sf::Keyboard::Space) gun->trigger = true;       // space => fire
        else if (event.Key.Code == sf::Keyboard::Num1) gun = &pistol;        // 1 => pistol
        else if (event.Key.Code == sf::Keyboard::Num2) gun = &revolver;      // 2 => revolver
        else if (event.Key.Code == sf::Keyboard::Num3) gun = &shotgun;       // 3 => shotgun
        else if (event.Key.Code == sf::Keyboard::Num4) gun = &mg;            // 4 => machine gun
        else if (event.Key.Code == sf::Keyboard::Num5) gun = &rocketLauncher;// 5 => rocket launcher
      }
      else if (event.Type == sf::Event::KeyReleased)
        if (event.Key.Code == sf::Keyboard::Space) gun->trigger = false;
    }
    
    // game logic
    float frameTime = app.GetFrameTime();
    phys.update(frameTime);
    spawner.update();
    gun->update();
    
    // do things with the dead
    if (p.dead) {
      p = Player(WIDTH/2, HEIGHT/2-4*TILE_SIZE, playerDead);
      playerDied = true;
    }
    if (!playerDied) {  // note playerDied != p.dead
      sprintf(timeString, "%.2f", gameTime.GetElapsedTime()/1000.f);   
      timeText.SetString(timeString);
    }
    
    // draw
    app.Clear();
    app.Draw(bg);
    app.Draw(placeObject(p.draw()));
    for (int i=0; i<bullets.size(); ++i)  // draw bullets
      app.Draw(placeObject(bullets[i].visual));
    for (int i=0; i<enemies.size(); ++i)  // draw enemies
      app.Draw(placeObject(enemies[i].tile));
    for (int i=0; i<level.platforms.size(); ++i)  // draw level
      for (int j=0; j<level.platforms[i].tiles.size(); ++j)
        app.Draw(level.platforms[i].tiles[j]);  // note: no need to call placeObject as the visual doesn't move.
    for (int i=0; i<explosions.size(); ++i) // draw explosions
      app.Draw(placeObject(explosions[i].visual));
    
    
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
