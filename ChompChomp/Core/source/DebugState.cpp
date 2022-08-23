#include "../include/DebugState.hpp"

debug::DebugState::DebugState(unsigned width, unsigned height, std::string name) : sf::RenderWindow(sf::VideoMode(width, height), "DebugWindow")
{

     if (!DEFAULT_FONT.loadFromFile(DEFAULT_FONT_FILEPATH))
     {
          // error...
     }

     mousePosText.setFont(DEFAULT_FONT);
     mousePosText.setCharacterSize(DEFAULT_CHAR_SIZE);
     mousePosText.setFillColor(DEFAULT_COLOR);
     mousePosText.setStyle(DEFAULT_TEXT_STYLE);
     mousePosText.setString(MOUSE_POS_MSG);
}

void debug::DebugState::Draw()
{
     clear();
     draw(mousePosText);
     display();
}



void debug::DebugState::UpdateState(core::BasicWindow& gameWindow)
{
     sf::Event event;
     while (this->pollEvent(event))
     {
          if (event.type == sf::Event::Closed)
          {
               this->close();
          }
     }
     std::string temp{ MOUSE_POS_MSG };
     //temp.append(std::format("{}, {}", sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y));

     mousePosText.setString(temp);
    /* debugWindow.clear();
     debugWindow.draw(mousePosText);
     debugWindow.display();*/
}

