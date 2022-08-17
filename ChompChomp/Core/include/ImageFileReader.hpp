#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace core
{
     class ImageFileReader
     {
     public:

          bool ReadImageFile(const sf::String& fPath, sf::Texture& texture)
          {
               if (!texture.loadFromFile(fPath))
               {
                    return false;
                    // error...
               }
               return true;
          }
     };
}