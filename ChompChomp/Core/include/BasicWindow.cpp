#include "BasicWindow.h"

core::BasicWindow::BasicWindow(sf::Vector2u size)
{
     window.create(sf::VideoMode(size.x, size.y), "Basic Window");
}

bool core::BasicWindow::PollEvent(sf::Event& event)
{
     return window.pollEvent(event);
}
