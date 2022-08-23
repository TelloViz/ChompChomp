#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <format>
#include "BasicWindow.h"


namespace debug
{
     class DebugState : public sf::RenderWindow
     {
     public:
          DebugState(unsigned width, unsigned height, std::string name);
          
          void Draw();

          void UpdateState(core::BasicWindow& gameWindow);
     private:
          //void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
          sf::Font DEFAULT_FONT;
          std::string DEFAULT_FONT_FILEPATH{ "arial.ttf" };
          int DEFAULT_CHAR_SIZE{ 32 };
          sf::Color DEFAULT_COLOR{ sf::Color::White };
          sf::Text::Style DEFAULT_TEXT_STYLE{ sf::Text::Regular };
          std::string MOUSE_POS_MSG{ "Mouse Pos: " };
          sf::Text mousePosText;



          
     };



}