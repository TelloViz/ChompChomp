#include "../include/game.hpp"
#include "../include/ImageFileReader.hpp"

//#include "../include/DebugState.hpp"


game::Game::Game() : window(500, 500, "Gyo-Fish"), debugWindow(300,150, "DebugState")
{
     darkenedWaterOverlayShape.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, 75.0f));
     darkenedWaterOverlayShape.setSize(sf::Vector2f(overworldQuadrantVec[activeQuadrant].width, overworldQuadrantVec[activeQuadrant].height));
     darkenedWaterOverlayShape.setPosition(sf::Vector2f(overworldQuadrantVec[activeQuadrant].left, overworldQuadrantVec[activeQuadrant].top));
}

void game::Game::Run()
{
     LoadConfig();
     InitOverWorld(); 

     //debug::DebugState debState(300, 150, "DebugWindow");

     if (!DEFAULT_FONT.loadFromFile(DEFAULT_FONT_FILEPATH))
     {
          // error...
     }

     mousePosText.setFont(DEFAULT_FONT);
     mousePosText.setCharacterSize(DEFAULT_CHAR_SIZE);
     mousePosText.setFillColor(DEFAULT_COLOR);
     mousePosText.setStyle(DEFAULT_TEXT_STYLE);
     mousePosText.setString(MOUSE_POS_MSG);

     float fps = 1.0f / 60.0f;
     sf::Time elapsed;
     while (window.IsOpen())
     {
          elapsed += clock.Restart();
          std::vector<sf::Event> events;
          PollEvents(events);
          Input(events);

          while(elapsed.asSeconds() > fps)
          {

               Update(1.0f/60.0f);
               DebugUpdate();
               elapsed -= sf::Time(sf::seconds(fps));
          }
          

          DebugRender();
          Render();
     }
}

void game::Game::LoadConfig()
{
     FishGameApp_ConfigHandler configHandler;
     configHandler.ReadConfigFile();
     std::string configVal;
     if (!configHandler.FindConfig("DEFAULT_WINDOW_WIDTH", configVal))
     {
          std::cout << "Config Not Loaded" << std::endl;
     }
     std::cout << configVal << std::endl;
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

void game::Game::Update(float dt)
{
     //darkenedWaterOverlayShape.setPosition(overworldQuadrantVec[activeQuadrant].left, overworldQuadrantVec[activeQuadrant].top);
     dtPerPoolAccumulator += sf::Time(sf::seconds(dt));
     if (dtPerPoolAccumulator.asSeconds() >= dtPerDarkenedPool.asSeconds())
     {
          dtPerPoolAccumulator -= dtPerDarkenedPool;
          
          activeQuadrant = OverworldQuadrant(RandomInt(0, 3));
          
          darkenedWaterOverlayShape.setPosition(overworldQuadrantVec[activeQuadrant].left, overworldQuadrantVec[activeQuadrant].top);
          
     }
     
}

void game::Game::Render()
{
     window.Clear();

     if (currState == GameState::OVER_WORLD)
     {
          window.Draw(pondSprite);
          window.Draw(darkenedWaterOverlayShape);

          
          /*for (auto i : overworldQuadrantVec)
          {
               darkenedWaterOverlayShape.setPosition(sf::Vector2f(i.left, i.top));
               window.Draw(darkenedWaterOverlayShape);
          }*/

     }
     if (currState == GameState::MINI_GAME)
     {
          
     }
     window.Display();
}

void game::Game::DebugRender()
{
     debugWindow.Clear();
     debugWindow.Draw(mousePosText);
     debugWindow.Display();
}
void game::Game::PollEvents(std::vector<sf::Event>& eventVec)
{
     sf::Event event;
     while (window.PollEvent(event))
     {
          eventVec.push_back(event);
     }
}

void game::Game::PollDebugEvents()
{
     sf::Event event;
     while (debugWindow.PollEvent(event))
     {
          if (event.type == sf::Event::Closed)
          {
               debugWindow.Close();
          }
     }
}

void game::Game::DebugUpdate()
{
     std::string temp{ MOUSE_POS_MSG };
     //temp.append(std::format("{}, {}", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

     //mousePosText.setString(temp);
     mousePosText.setString(std::format("{}, {}", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
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
               shouldIncreaseScale = true;
                      
          }
          if (event.key.code == sf::Keyboard::Key::M)
          {
               shouldDecreaseScale = true;
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
          OnMiniGame_MousePressed(event);
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
          OnOverWorld_MouseReleased(event);
          break;
     case game::MINI_GAME:
          OnMiniGame_MouseReleased(event);
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
          //std::cout << "Mouse at: " << sf::Mouse::getPosition(window).x << ", " << sf::Mouse::getPosition(window).y << std::endl;
          break;
     case game::MINI_GAME:
          //std::cout << "Mouse at: " << sf::Mouse::getPosition(window).x << ", " << sf::Mouse::getPosition(window).y << std::endl;
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
     if (darkenedWaterOverlayShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
     {
          currState = GameState::MINI_GAME;
     }
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


