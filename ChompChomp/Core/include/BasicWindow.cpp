#include "BasicWindow.h"

core::BasicWindow::BasicWindow(unsigned width, unsigned height)
{
     window.create(sf::VideoMode(width, height), "Basic Window");
     window.setFramerateLimit(60);
}


bool core::BasicWindow::PollEvent(sf::Event& event)
{
     return window.pollEvent(event);
}
