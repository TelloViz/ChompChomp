#pragma once
#include <SFML/Graphics.hpp>


namespace core
{

     class FocusBorder : public sf::Drawable
     {
     public:
          FocusBorder(float width, float height, float x, float y, sf::Color color)
          {
               border.setSize(sf::Vector2f(width, height));
               border.setPosition(sf::Vector2f(x, y));

               border.setFillColor(sf::Color::Transparent);
               border.setOutlineColor(color);
               border.setOutlineThickness(2.0f);
          }

          void SetEnabled(bool enabled) { isEnabled = enabled; }
          bool IsEnabled() { return isEnabled; }

          void SetActive(bool active) { isActive = active; }
          bool IsActive() { return isActive; }

          void draw(sf::RenderTarget& target, sf::RenderStates states) const
          {
               if (isActive)
                    target.draw(border, states);
          }


     private:
          sf::RectangleShape border;
          bool isActive{ false };
          bool isEnabled{ false };
     };
}