#include <SFML/Graphics.hpp>

#define WIDTH 256 //16x10 tiles with soze of 16x16
#define HEIGHT 160

// Coordiante system: Cartesian with +x going right and +y going down

float scale = 4;  // grobal variable to be written to by main() and read by placeObject()
int screenWd = sf::VideoMode::GetDesktopMode().Width; // faster than calling the function everytime
int screenHt = sf::VideoMode::GetDesktopMode().Height;

