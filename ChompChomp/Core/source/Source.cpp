#include <SFML/Graphics.hpp>

#include "../include/BasicWindow.h"
int main()
{
     core::BasicWindow win(sf::Vector2u(600,600));
   

     while (win.IsOpen())
     {
          
          sf::Event event;
          while (win.PollEvent(event))
          {
               if (event.type == sf::Event::Closed)
                    win.Close();
          }

          win.Clear();
          //win.Draw(shape);
          //win.Draw(water);
          win.Display();
     }

     return 0;
}