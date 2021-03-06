#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <stdio.h>  // for text sprintf()

#include "utils.hpp"
#include "level.hpp"
#include "platform.hpp"
#include "guns/gun.hpp"
#include "bullets/bullet.hpp"
#include "bullets/explosion.hpp"
#include "physics.hpp"
#include "enemy.hpp"
#include "spawner.hpp"
#include "box.hpp"
#include "player.hpp"


float scale = 4;  // grobal variable to be written to by main() and read by placeObject()
int screenWd; // faster than calling the function everytime
int screenHt;

sf::Drawable &placeObject(sf::Drawable &d) {
  d.Scale(scale, scale); // scale size
  d.Move( // scale position
    d.GetPosition().x * (scale-1),
    d.GetPosition().y * (scale-1) 
  );
  d.Move( // shift to game top-left corner
    screenWd/2 - scale*WIDTH/2, 
    screenHt/2 - scale*HEIGHT/2
  );
}

int main() {
  // create the window
  sf::VideoMode screen(sf::VideoMode::GetDesktopMode());
  sf::RenderWindow app(screen, "sfmc", sf::Style::Default);
//  app.SetFramerateLimit(60); // Limit to 60 frames per second
  app.ShowMouseCursor(false);
  app.EnableVerticalSync(true);
  app.EnableKeyRepeat(false);
  scale = std::min(screen.Height / (float)HEIGHT, screen.Width/(float)WIDTH); // dynamic scaling
  //std::cout << "scale: x" << scale << std::endl;
  
  screenWd = sf::VideoMode::GetDesktopMode().Width;
  screenHt = sf::VideoMode::GetDesktopMode().Height;
  
  // bg image
  sf::Texture bgTexture; bgTexture.LoadFromFile("resources/images/bg.png");
  sf::Sprite bg;
  bg.SetTexture(bgTexture);
  placeObject(bg);
  
  // Level 
  sf::Image levelData; levelData.LoadFromFile("resources/levels/level1.png");
  sf::Texture tileTex; tileTex.LoadFromFile("resources/images/platform.png");
  Level level(levelData, tileTex);
  for (int i=0; i<level.platforms.size(); ++i)
    for (int j=0; j<level.platforms[i].tiles.size(); ++j)
      placeObject(level.platforms[i].tiles[j]);
  
  // player
  sf::Texture playerLive; playerLive.LoadFromFile("resources/images/player_8x8.png");
  sf::Texture playerDead; playerDead.LoadFromFile("resources/images/player_fail.png");
  Player p(playerLive, levelData);
  
  // Bullets
  sf::Texture smallBullet; smallBullet.LoadFromFile("resources/images/bullet_4x4.png");
  sf::Texture largeBullet; largeBullet.LoadFromFile("resources/images/bullet_6x6.png");
  sf::Texture rocketShell; rocketShell.LoadFromFile("resources/images/rocket_8x4.png");
  sf::Texture grenadeAmmo; grenadeAmmo.LoadFromFile("resources/images/grenade_4x4.png");
  std::vector<Bullet> bullets;
  
  // Explosions
  std::vector<Explosion> explosions;
  
  // Gun Sounds
  sf::SoundBuffer gunShot; gunShot.LoadFromFile("resources/sound/gunShot.wav");
  
  // Enemies
  std::vector<Enemy> enemies;
  Spawner spawner(enemies, levelData);
  spawner.addEnemy();

  // The fox box
  sf::Texture boxTexture; boxTexture.LoadFromFile("resources/images/foxCrate_7x7.png");
  Box foxBox(WIDTH/2, HEIGHT/2, boxTexture, levelData, p); 

  // Physics
  Physics phys(p, level, bullets, explosions, enemies, foxBox);
  int gravityControlInverse = 0;  // a player preference to choose whether the gravity goes with or against the WASD direction (value is either 0/180)

  // Guns
  Gun *guns[] = {
 // new Gun (bullets, p, <sound>, <bulletTexture>, <coolDn>, <dmg>, <#>, <vel_x/y>, <var_x/y>,  <acc_x/y>, <auto>, <explosive>), // template
    new Gun (bullets, p, gunShot, smallBullet,     100,       1,    1,   0.2,  0,   0,    0,    0,     0,  false,   false ), // pistol
    new Gun (bullets, p, gunShot, largeBullet,     100,       5,    1,   0.2,  0,   0,    0,    0,     0,  false,   false ), // revolver
    new Gun (bullets, p, gunShot, smallBullet,      50,       1,    1,   0.2,  0,   0,    0.02, 0,     0,  true,    false ), // machineGun
    new Gun (bullets, p, gunShot, smallBullet,     500,       1,    6,   0.25, 0,   0.05, 0.05, -.0005,0,  false,   false ), // shotgun
    new Gun (bullets, p, gunShot, grenadeAmmo,    1000,      10,    1,   0.1,  -.1, 0,    0,    0,phys.gravity.y,false,true), // grenadeLauncher
    new Gun (bullets, p, gunShot, rocketShell,    1000,      10,    1,   0.01, 0,   0,    0,    0.0005,0,  false,   true  )  // rocketLauncher
  };
  const int gunCount = 6;
  int gunIndex = 0;
  Gun *gun = guns[gunIndex];

  // leet FPS counter
  char fpsString[15];
  sf::Text fps;
  fps.SetColor(sf::Color(128, 0, 0));
  
  // high score timer
  sf::Clock gameTime;
  int score = 0;
  char scoreString[15];
  bool playerDied = false;
  sf::Text scoreText;
  scoreText.SetCharacterSize(40); 
  scoreText.SetColor(sf::Color(255, 0, 0));
  scoreText.SetPosition(screenWd/2 - 30, 0);
  
  // main game loop
  while (app.IsOpened()) {
    // input
    p.checkKeys();
    //if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Dash)) usleep(50000); // space  => low framerate for testing (~19 fps)

    sf::Event event;  // process window events
    while (app.PollEvent(event)) {
      if (event.Type == sf::Event::Closed) app.Close();  // check for window exit
      else if (event.Type == sf::Event::KeyPressed) {    // check key down events
        if (event.Key.Code == sf::Keyboard::Escape) app.Close();              // escape => exit
        else if (event.Key.Code == sf::Keyboard::Space) gun->trigger = true;  // space  => fire
        else if (event.Key.Code == sf::Keyboard::Return) {                    // enter  => restart the game
          bullets.clear();
          enemies.clear();
          spawner.reset();
          gameTime.Reset();
          playerDied = false;
          p.reset(playerLive);
          foxBox.newPosition();
          score = 0;
        } 
        else if (event.Key.Code == sf::Keyboard::S) phys.rotateGravity(0*90+gravityControlInverse); // note: all angles are in degrees because SFML
        else if (event.Key.Code == sf::Keyboard::D) phys.rotateGravity(1*90+gravityControlInverse);
        else if (event.Key.Code == sf::Keyboard::W) phys.rotateGravity(2*90+gravityControlInverse);
        else if (event.Key.Code == sf::Keyboard::A) phys.rotateGravity(3*90+gravityControlInverse);
      }
      else if (event.Type == sf::Event::KeyReleased)
        if (event.Key.Code == sf::Keyboard::Space) gun->trigger = false;
    }
    
    // game logic
    float frameTime = app.GetFrameTime();
    phys.update(frameTime); // WHERE MOST OF THE WORK IS DONE
    if (foxBox.collidesWith(p)) {
      ++score;
      gun->trigger = false;
      int newIndex = rand()%(gunCount-1); // choose different weapon
      if (gunIndex == newIndex) newIndex = gunCount-1;
      gunIndex = newIndex;
      gun = guns[gunIndex];
      foxBox.newPosition();
    }
    spawner.update();
    gun->update();
    
    // do things with the dead
    if (p.dead) {
      p.reset(playerDead);
      playerDied = true;
    }
    if (!playerDied) {  // note: playerDied != p.dead
      sprintf(scoreString, "%d", score);   
      scoreText.SetString(scoreString);
    }
    
    // draw
    app.Clear(sf::Color(127,127,127));
    app.Draw(bg);
    app.Draw(placeObject(p.visual));      // player
    app.Draw(placeObject(foxBox.visual)); 
    for (int i=0; i<bullets.size(); ++i)  // bullets
      app.Draw(placeObject(bullets[i].visual));
    for (int i=0; i<enemies.size(); ++i)  // enemies
      app.Draw(placeObject(enemies[i].visual));
    for (int i=0; i<level.platforms.size(); ++i)  // level
      for (int j=0; j<level.platforms[i].tiles.size(); ++j)
        app.Draw(level.platforms[i].tiles[j]);  // note: no need to call placeObject as the visual doesn't move.
    for (int i=0; i<explosions.size(); ++i) // explosions
      app.Draw(placeObject(explosions[i].visual));
    
    
    // fps
    sprintf(fpsString, "fps: %.2f", 1000.f/frameTime); 
    fps.SetString(fpsString);
    app.Draw(fps);
    
    // draw score
    app.Draw(scoreText);
    
    app.Display();
    
  } // end of main game loop
 
  for (int i=0; i<gunCount; ++i) delete guns[i];  // deallocate memory
 
  return EXIT_SUCCESS;
}
