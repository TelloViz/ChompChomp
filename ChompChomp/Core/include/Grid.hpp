#pragma once
#include <SFML/Graphics.hpp>
namespace core
{
     class Grid : public sf::Drawable
     {
     public:

          Grid(sf::Vector2f position, sf::Vector2f increment, sf::Vector2i numLines, float weight, sf::Color color) : position(position), increment(increment), numLines(numLines), weight(weight), color(color)
          {
               if (!gridTexture.create(increment.x * numLines.x, increment.y * numLines.y))
               {
                    // error...
               }
               gridTexture.clear(sf::Color::Transparent);
               
               
               vertLineRect.setSize(sf::Vector2f(weight, increment.y * numLines.y));
               horizLineRect.setSize(sf::Vector2f(increment.x * numLines.x, weight));

               

               for (int i = 0; i <= numLines.x; i++)
               {
                    vertLineRect.setPosition(increment.x * i,0.0f);
                    gridTexture.draw(vertLineRect);
               }

               for (int j = 0; j <= numLines.y; j++)
               {
                    horizLineRect.setPosition(0.0f, increment.y * j);
                    gridTexture.draw(horizLineRect);
               } 

               gridSprite.setTexture(gridTexture.getTexture());
               gridSprite.setPosition(position);

          }

          virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
          {
               
               target.draw(gridSprite, states);
               
               
          }


          sf::RenderTexture gridTexture;
          sf::Sprite gridSprite;
          sf::RectangleShape vertLineRect;
          sf::RectangleShape horizLineRect;
          sf::Vector2f position;
          sf::Vector2f increment;
          sf::Vector2i numLines;
          float weight;
          sf::Color color;
     };
}