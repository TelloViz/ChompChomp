#pragma once
#include <SFML/System/Clock.hpp>


class TickClock
{
public:
     TickClock() {}
     sf::Time GetElapsedTime() const {}
     sf::Time Restart() {}
private:
     sf::Clock clock;

};