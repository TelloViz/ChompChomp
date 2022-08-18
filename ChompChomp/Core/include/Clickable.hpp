#pragma once
#include "BasicWindow.h"
#include <SFML/Graphics.hpp>

namespace core
{
     class Clickable
     {
     public:
          virtual ~Clickable() {}
          virtual void OnClicked() = 0;
     };
}