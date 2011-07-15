#include <SFML/Graphics.hpp>

#include <iostream>

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
  
  Physics phys(p);
  
  // Level
  sf::Image platformTexture;
  if (!platformTexture.LoadFromFile("images/platform.png")) return -1;
  Platform platform1(WIDTH/2, HEIGHT/2, TILE_SIZE*4, TILE_SIZE, platformTexture);
  phys.addPlatform(&platform1);
  std::vector<sf::Sprite> *level = platform1.draw();
  for (int i=0; i<level->size(); ++i) {
    placeObject((*level)[i]);
  }
  
  // main game loop
  while (app.IsOpened()) {
    // input
    if (app.GetInput().IsKeyDown(sf::Key::Escape)) app.Close(); 
    if (app.GetInput().IsKeyDown(sf::Key::Space )) usleep(50000); // create artificially low frame rate
    p.checkKeys(app);
    
    // process window events
    sf::Event event;
    while (app.PollEvent(event)) if (event.Type == sf::Event::Closed) app.Close(); // check for window exit
    
    // game logic
    float frameTime = app.GetFrameTime();
    phys.update(frameTime);
    //std::cout << "Framerate: " << 1000.f/frameTime << std::endl;
    
    // draw
    app.Clear();
    app.Draw(bg);
    app.Draw(placeObject(p.draw()));
    for (int i=0; i<level->size(); ++i) {
      app.Draw((*level)[i]);
    }
    
    app.Display();
    
  }
  return EXIT_SUCCESS;
}
