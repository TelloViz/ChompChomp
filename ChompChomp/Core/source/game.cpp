#include "../include/game.hpp"

game::Game::Game() : window(500, 500,"Chomp Chomp")
{

}

void game::Game::Run()
{
     while (window.IsOpen())
     {
          Update();
          Render();
     }
}

void game::Game::Input()
{
}

void game::Game::Update()
{
     sf::Event event;
     while (window.PollEvent(event))
     {
         if (event.type == sf::Event::Closed)
               window.Close();
         /*if (event.type == sf::Event::MouseButtonPressed)
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
          }*/
     }
}

void game::Game::Render()
{
     window.Clear();
     window.Display();
}
