#include <SFML/Graphics.hpp>

#include <iostream>
#include "player.hpp"
#include "utils.hpp"

void placeObject(sf::Drawable& d) {
  d.SetScale(scale, scale);
  d.SetPosition(
    screenWd/2 - scale*WIDTH/2, 
    screenHt/2 - scale*HEIGHT/2
  );
}

int main() {
  // create the window
  sf::VideoMode screen(sf::VideoMode::GetDesktopMode());
  sf::RenderWindow app(screen, "Hi World?", sf::Style::Fullscreen);
  app.SetFramerateLimit(60); // Limit to 60 frames per second
  
  scale = screen.Height / (float)HEIGHT; // (un-)comment this line to enable/disable dynamic scaling
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
  Player p(WIDTH/2, HEIGHT/2);
  
  // main game loop
  while (app.IsOpened()) {
    if (app.GetInput().IsKeyDown(sf::Key::Escape)) app.Close(); 
    // process window events
    sf::Event event;
    while (app.PollEvent(event)) {
      // check for window exit
      if (event.Type == sf::Event::Closed) app.Close();
    }
    
    // game logic
    p.checkKeys(app);
    
    
    // draw
    app.Clear();
    app.Draw(bg);
    app.Draw(tri);
    
    app.Display();
    
  }
  return EXIT_SUCCESS;
}
