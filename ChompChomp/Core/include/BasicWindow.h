#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace core
{
     class BasicWindow
     {
     public:

          BasicWindow(sf::Vector2u size);

          void Clear() { window.clear(); }
          void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default) { window.draw(drawable); }
          void Display() { window.display(); }

          sf::Vector2u GetSize() const { return window.getSize(); }
          sf::Vector2i GetPosition() const { return window.getPosition(); }
          void SetPosition(const sf::Vector2i& position) { window.setPosition(position); }
          void SetSize(const sf::Vector2u& size) { window.setSize(size); }

          void setTitle(const sf::String& title) { window.setTitle(title); }

          bool IsOpen() { return window.isOpen(); }
          bool PollEvent(sf::Event& event);
          void Close() { window.close(); }
          
     private:
          sf::RenderWindow window;
     };
}