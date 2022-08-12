#include <SFML/Graphics.hpp>
int main()
{
     sf::RenderWindow window(sf::VideoMode(600, 600), "Codename: ChompChomp!");
     sf::RectangleShape shape;
     shape.setSize(sf::Vector2f(500.0f, 500.0f));
     shape.setPosition(sf::Vector2f(window.getSize().x / 2.0f - shape.getSize().x / 2.0f, window.getSize().y / 2.0f - shape.getSize().y / 2.0f));
     shape.setFillColor(sf::Color(175,175,175,255));

     sf::RectangleShape water;
     water.setSize(sf::Vector2f(250.0f, 250.0f));
     water.setPosition(sf::Vector2f(window.getSize().x / 2.0f - water.getSize().x / 2.0f, window.getSize().y / 2.0f - water.getSize().y / 2.0f));
     water.setFillColor(sf::Color(0, 175, 175, 255));

     while (window.isOpen())
     {
          
          sf::Event event;
          while (window.pollEvent(event))
          {
               if (event.type == sf::Event::Closed)
                    window.close();
          }

          window.clear();
          window.draw(shape);
          window.draw(water);
          window.display();
     }

     return 0;
}