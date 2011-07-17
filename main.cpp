#include <SFML/Graphics.hpp>

#include <iostream>

#include "level.hpp"
#include "platform.hpp"
#include "physics.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "utils.hpp"


float scale = 4;  // grobal variable to be written to by main() and read by placeObject()
int screenWd; // faster than calling the function everytime
int screenHt;

sf::Drawable &placeObject(sf::Drawable &d) {
  d.SetScale(scale, scale);
  d.Move(
    d.GetPosition().x * (scale-1),
    d.GetPosition().y * (scale-1) 
  );
  d.Move( // translation
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
  if (!bgImage.LoadFromFile("images/bg.png")) return -1;
  sf::Sprite bg;
  bg.SetImage(bgImage);
  bg.SetColor(sf::Color::Blue);
  placeObject(bg);
  
  // player
  sf::Image playerImage;
  if (!playerImage.LoadFromFile("images/player_8x8.png")) return -1;
  Player p(WIDTH/2, HEIGHT/2, playerImage);
    
  // Level
  Level level("levels/test.lvl");
  for (int i=0; i<level.tiles.size(); ++i) placeObject(*level.tiles[i]);
  
  // Physics
  Physics phys(p, level);

  // main game loop
  while (app.IsOpened()) {
  
    // input
    p.checkKeys();    // gets more raw keyboard input
    sf::Event event;  // process window events
    while (app.PollEvent(event)) {
      if (event.Type == sf::Event::Closed) app.Close(); // check for window exit
      else if(event.Type == sf::Event::KeyPressed) {    // check key events
        if (event.Key.Code == sf::Keyboard::Escape) app.Close();       // escape => exit
        else if (event.Key.Code == sf::Keyboard::Space) usleep(50000); // space  => low framerate (for testing)
        //else if (p.checkKeys(event.Key.Code));
      }
    }
    
    // game logic
    float frameTime = app.GetFrameTime();
    phys.update(frameTime);
    //std::cout << "Framerate: " << 1000.f/frameTime << std::endl;
    
    // draw
    app.Clear();
    app.Draw(bg);
    app.Draw(placeObject(p.draw()));
    for (int i=0; i<level.tiles.size(); ++i) {
      app.Draw(*level.tiles[i]);
    }
    
    app.Display();
    
  }
  return EXIT_SUCCESS;
}
