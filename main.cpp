#include <SFML/Graphics.hpp>

#include <iostream>
#include "physics.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "utils.hpp"

float scale = 4;  // grobal variable to be written to by main() and read by placeObject()
int screenWd = sf::VideoMode::GetDesktopMode().Width; // faster than calling the function everytime
int screenHt = sf::VideoMode::GetDesktopMode().Height;

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
  
  // bg image
  sf::Image bgImage;
  if (!bgImage.LoadFromFile("images/bg.png")) return -1;
  sf::Sprite bg;
  bg.SetImage(bgImage);
  bg.SetColor(sf::Color::Blue);
  placeObject(bg);
  
  // size triangle
  sf::Color c(sf::Color::Red);
  sf::Shape tri;
  tri.AddPoint(0,   0  ,c,c);
  tri.AddPoint(256, 0  ,c,c);
  tri.AddPoint(128, 160,c,c);
  tri.EnableOutline(true);
  tri.SetOutlineThickness(1);
  tri.EnableFill(false);
  placeObject(tri);
  
  // player
  sf::Image playerImage;
  if (!playerImage.LoadFromFile("images/player_16x16.png")) return -1;
  Player p(WIDTH/2, HEIGHT/2, playerImage);
  
  Physics phys(p);
  
  // main game loop
  while (app.IsOpened()) {
    if (app.GetInput().IsKeyDown(sf::Key::Escape)) app.Close(); 
    if (app.GetInput().IsKeyDown(sf::Key::Space )) usleep(50000);
    // process window events
    
    // game logic
    p.checkKeys(app);
    
    sf::Event event;
    while (app.PollEvent(event)) {
      // check for window exit
      if (event.Type == sf::Event::Closed) app.Close();
    }
    
    float frameTime = app.GetFrameTime();
    phys.update(frameTime);
    
    // draw
    app.Clear();
    app.Draw(bg);
    //app.Draw(tri);
    app.Draw(placeObject(p.draw()));
    
    app.Display();
    
  }
  return EXIT_SUCCESS;
}
