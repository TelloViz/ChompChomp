#include <SFML/Graphics.hpp>

#include "../include/BasicWindow.h"
#include "../include/ImageFileReader.hpp"
#include "../include/TickClock.hpp"
#include "../include/FocusBorder.hpp"
//#include "../include/Grid.hpp"
#include <iostream>
#include <string>
#include <format>


void HandleMouseButtonPressed(core::BasicWindow& win)
{
     
     std::cout << std::format("Mouse Button Pressed at: {},{}", sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y) << std::endl;
     
}

void HandleMouseButtonReleased(core::BasicWindow& win)
{
     std::cout << std::format("Mouse Button Released at: {},{}", sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y) << std::endl;
}

int main()
{
     core::BasicWindow win(500,500);
     core::ImageFileReader imgReader;
     core::TickClock clock;

     sf::Texture myTexture;
     imgReader.ReadImageFile("pond.png", myTexture);

     


     //core::Grid grid(sf::Vector2f(100.0f,50.0f), sf::Vector2f(50.0f, 50.0f), sf::Vector2i(5, 5), 1, sf::Color(255, 0, 0, 255));

     sf::Sprite mySprite;
     mySprite.setTexture(myTexture);
     mySprite.setScale(sf::Vector2f(2.0f, 2.0f));
     mySprite.setPosition(sf::Vector2f(win.GetSize().x / 2 - (myTexture.getSize().x * mySprite.getScale().x) / 2, win.GetSize().y / 2 - (myTexture.getSize().y * mySprite.getScale().y) / 2));


     core::FocusBorder focusBorder(mySprite.getGlobalBounds().width, mySprite.getGlobalBounds().height, mySprite.getGlobalBounds().left, mySprite.getGlobalBounds().top, sf::Color::Red);
     focusBorder.SetEnabled(true);


     while (win.IsOpen())
     {
          auto dt = clock.Restart();          

          sf::Event event;
          while (win.PollEvent(event))
          {
               if (event.type == sf::Event::Closed)
                    win.Close();
               if (event.type == sf::Event::MouseButtonPressed)
               {
                    HandleMouseButtonPressed(win);

                    if (mySprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y)))
                    {
                         focusBorder.SetActive(true);
                    }
               }
               if (event.type == sf::Event::MouseButtonReleased)
               {
                    HandleMouseButtonReleased(win);

                    if (focusBorder.IsActive()) focusBorder.SetActive(false);
               }
          }

          win.Clear(sf::Color::Black);
          win.Draw(mySprite);
          if (focusBorder.IsEnabled() && focusBorder.IsActive()) win.Draw(focusBorder);
          win.Display();
     }

     return 0;
}