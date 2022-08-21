#include "../include/BasicWindow.h"

#include <format>
#include <iostream>
#include <string>

core::BasicWindow::BasicWindow(unsigned width, unsigned height, std::string name = "Basic Window") : name(name)
{
     window.create(sf::VideoMode(width, height), name, sf::Style::Titlebar | sf::Style::Close);
   
     
     //window.setFramerateLimit(60);
}


bool core::BasicWindow::PollEvent(sf::Event& event)
{
     if (window.pollEvent(event))
     {
          return true;
     }
     else return false;
     
}

void core::BasicWindow::OnClicked()
{
}

std::string core::BasicWindow::Name() const
{
     return name;
}
