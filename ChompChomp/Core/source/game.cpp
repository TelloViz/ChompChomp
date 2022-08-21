#include "../include/game.hpp"
#include "../include/ImageFileReader.hpp"

game::Game::Game() : window(500, 500,"Chomp Chomp")
{

}

void game::Game::Run()
{
     InitOverWorld();  


     
     while (window.IsOpen())
     {
          std::vector<sf::Event> events;
          PollEvents(events);
          Input(events);
          Update();
          Render();
     }
}

void game::Game::InitOverWorld()
{
     if (!isImagesLoaded)
     {
          core::ImageFileReader imgReader;

          if (!imgReader.ReadImageFile("pond.png", pondTexture))
          {

          }
     }
     pondSprite.setTexture(pondTexture);
     pondSprite.setScale(DEFAULT_POND_SPRITE_SCALE);
     pondSprite.setPosition(window.GetSize().x / 2.0f - (pondTexture.getSize().x * pondSprite.getScale().x)/ 2.0f, window.GetSize().y / 2.0f - (pondTexture.getSize().y * pondSprite.getScale().y) / 2.0f);

     //overworld_drawables.push_back(pondSprite);

}

void game::Game::InitMiniGame()
{
}

void game::Game::Input(std::vector<sf::Event>& events)
{
     for (sf::Event& i : events)
     {
          switch (i.type)
          {
          case sf::Event::Closed:
               OnClose(i);
               break;
          case sf::Event::Resized:
               std::cout << "Resized Window to " << i.size.width << ", " << i.size.height << std::endl;
               OnResized(i);
               break;
          case sf::Event::EventType::LostFocus:
               OnLostFocus(i);
               break;
          case sf::Event::EventType::GainedFocus:
               OnGainedFocus(i);
               break;
          case sf::Event::EventType::KeyPressed:
               OnKeyPressed(i);
               break;
          case sf::Event::EventType::KeyReleased:
               OnKeyReleased(i);
               break;
          case sf::Event::EventType::MouseButtonPressed:
               OnMouseButtonPressed(i);
               break;
          case sf::Event::EventType::MouseButtonReleased:
               OnMouseButtonReleased(i);
               break;
          case sf::Event::EventType::MouseMoved:
               OnMouseMoved(i);
               break;
          case sf::Event::EventType::MouseEntered:
               OnMouseEntered(i);
               break;
          case sf::Event::EventType::MouseLeft:
               OnMouseLeft(i);
               break;
          default:
               break;
          }
     }
}

void game::Game::Update()
{
     if (pondSprite.getScale().x != DEFAULT_POND_SPRITE_SCALE.x || pondSprite.getScale().y != DEFAULT_POND_SPRITE_SCALE.y)
     {
          //pondSprite.setScale(DEFAULT_POND_SPRITE_SCALE);
          pondSprite.setPosition(window.GetSize().x / 2.0f - pondSprite.getGlobalBounds().width / 2.0f, window.GetSize().y / 2.0f - pondSprite.getGlobalBounds().height / 2.0f);
          std::cout << std::format("Pond Sprite Scale Set to {}, {}", DEFAULT_POND_SPRITE_SCALE.x, DEFAULT_POND_SPRITE_SCALE.y) << std::endl;
     }
     
}

void game::Game::Render()
{
     window.Clear();
     window.Draw(pondSprite);

     if (currState == GameState::MINI_GAME)
     {
          
     }
     window.Display();
}

void game::Game::PollEvents(std::vector<sf::Event>& eventVec)
{
     sf::Event event;
     while (window.PollEvent(event))
     {
          eventVec.push_back(event);
     }
}

void game::Game::OnClose(sf::Event& event)
{
     window.Close();
}

void game::Game::OnResized(sf::Event& event)
{
         
}

void game::Game::OnLostFocus(sf::Event& event)
{
}

void game::Game::OnGainedFocus(sf::Event& event)
{
}

void game::Game::OnKeyPressed(sf::Event& event)
{
}

void game::Game::OnKeyReleased(sf::Event& event)
{
     switch (currState)
     {
     case game::OVER_WORLD:
          if (event.key.code == sf::Keyboard::Key::P)
          {
               pondSprite.setScale(sf::Vector2f(pondSprite.getScale().x + 0.50f, pondSprite.getScale().y + 0.50f));
                      
          }
          if (event.key.code == sf::Keyboard::Key::M)
          {
               pondSprite.setScale(sf::Vector2f(pondSprite.getScale().x - 0.50f, pondSprite.getScale().y - 0.50f));
          }
         
               
          break;
     case game::MINI_GAME:
          break;
     default:
          break;
     }
}

void game::Game::OnMouseButtonPressed(sf::Event& event)
{ 
     switch (currState)
     {
     case game::OVER_WORLD:
          OnOverWorld_MousePressed(event);
          break;
     case game::MINI_GAME:
          break;
     default:
          break;
     }
}

void game::Game::OnMouseButtonReleased(sf::Event& event)
{
     switch (currState)
     {
     case game::OVER_WORLD:
          break;
     case game::MINI_GAME:
          break;
     default:
          break;
     }
}

void game::Game::OnMouseMoved(sf::Event& event)
{
     switch (currState)
     {
     case game::OVER_WORLD:
          break;
     case game::MINI_GAME:
          break;
     default:
          break;
     }
}

void game::Game::OnMouseEntered(sf::Event& event)
{
     switch (currState)
     {
     case game::OVER_WORLD:
          break;
     case game::MINI_GAME:
          break;
     default:
          break;
     }
}

void game::Game::OnMouseLeft(sf::Event& event)
{
     switch (currState)
     {
     case game::OVER_WORLD:
          break;
     case game::MINI_GAME:
          break;
     default:
          break;
     }
}

void game::Game::OnOverWorld_MousePressed(sf::Event& event)
{
}

void game::Game::OnOverWorld_MouseReleased(sf::Event& event)
{
}

void game::Game::OnMiniGame_MousePressed(sf::Event& event)
{
}

void game::Game::OnMiniGame_MouseReleased(sf::Event& event)
{
}
