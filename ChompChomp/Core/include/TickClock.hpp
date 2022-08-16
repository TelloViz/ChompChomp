#pragma once
#include <SFML/System/Clock.hpp>

namespace core
{
     class TickClock
     {
     public:
          TickClock() {}
          sf::Time GetElapsedTime() const { return clock.getElapsedTime(); }
          sf::Time Restart() { return clock.restart(); }
     private:
          sf::Clock clock;

     };
}