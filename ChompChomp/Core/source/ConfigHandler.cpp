#include "../include/ConfigHandler.h"

bool FishGameApp_ConfigHandler::ReadConfigFile()
{
     string filename("config.txt");
     vector<string> lines{};
     string line{};

     ifstream input_file(filename);
     if (!input_file.is_open()) {
          cerr << "Could not open the file - '"
               << filename << "'" << endl;
          return EXIT_FAILURE;
     }

     
     while (getline(input_file, line)) {
          if(!line.empty() && line.front() != '\n' && line.front() != '/')
               lines.push_back(line);          
     }

    /* for (const auto& i : lines)
          cout << i << endl;*/

     input_file.close();

     ParseConfigFile(lines);

     return EXIT_SUCCESS;
}

bool FishGameApp_ConfigHandler::WriteConfigFile()
{
     string filename("config.txt");
     fstream file_out;

     file_out.open(filename, std::ios_base::out);
     if (!file_out.is_open()) {
          cout << "failed to open " << filename << '\n';
     }
     else {
                 
          for (auto const& x : keys)
          {
               file_out << x  // string (key)
                    << '='
                    << configValueMap.at(x) // string's value 
                    << std::endl;
          }
          
          file_out.close();
          cout << "Done Writing!" << endl;
     }

     return EXIT_SUCCESS;
}

bool FishGameApp_ConfigHandler::FindConfig(string key, string& value)
{
     if (configValueMap.empty()) return false;
     try
     {
          value = configValueMap.at(key);
     }
     catch (const std::exception&)
     {

     }
     
     return true;
}

bool FishGameApp_ConfigHandler::AlterValue(string key, string newVal)
{
     configValueMap.at(key) = newVal;
     return true;
}

bool FishGameApp_ConfigHandler::ParseConfigFile(const vector<string>& lines)
{
     string k{}, v{};
     bool equalsFound = false;
     for (auto const& line : lines)
     {
          for (auto const& i : line)
          {
               if(i == '=')
               {
                    equalsFound = true;
               }
               else
               {    
                    if (equalsFound)
                    {
                         v.push_back(i);
                    }
                    else
                    {
                        k.push_back(i);
                    }
               }            
               
               
          }
          keys.push_back(k);
          configValueMap.insert(std::pair<string, string>(k, v));
          v = k = string{};
          equalsFound = false;


          
     }


     return true;
}

bool FishGameApp_ConfigHandler::Init_UI_Variables(FishGameApp_ConfigHandler& hCfg, UI_Config_State& UIConfig, Fish_Config_State& fCfg)
{
     hCfg.FindConfig("DEFAULT_WINDOW_WIDTH", UIConfig.windowWidth);
     hCfg.FindConfig("DEFAULT_WINDOW_HEIGHT", UIConfig.windowHeight);
     hCfg.FindConfig("BG_IMAGE_PATH", UIConfig.frame);
     if (!UIConfig.frameTexture.loadFromFile(UIConfig.frame))
     {
          // error ...
     }

     hCfg.FindConfig("DEFAULT_CANVAS_WIDTH", UIConfig.canvasWidth);
     hCfg.FindConfig("DEFAULT_CANVAS_HEIGHT", UIConfig.canvasHeight);
     hCfg.FindConfig("CANVAS_X_POS", UIConfig.canvas_X);
     hCfg.FindConfig("CANVAS_Y_POS", UIConfig.canvas_Y);


     UIConfig.canvasShape.setSize(sf::Vector2f(stoi(UIConfig.canvasWidth), stoi(UIConfig.canvasHeight)));
     UIConfig.canvasShape.setFillColor(sf::Color::Transparent);
     UIConfig.canvasShape.setOutlineThickness(1.0f);
     UIConfig.canvasShape.setOutlineColor(sf::Color(255, 255, 255, 255));
     UIConfig.canvasShape.setPosition(stoi(UIConfig.canvas_X), stoi(UIConfig.canvas_Y));

     UIConfig.frameSprite.setTexture(UIConfig.frameTexture);
     UIConfig.frameSprite.setPosition(stoi(UIConfig.canvas_X), stoi(UIConfig.canvas_Y));

     hCfg.FindConfig("TIMER_X", UIConfig.timer_X);
     hCfg.FindConfig("TIMER_Y", UIConfig.timer_Y);
     hCfg.FindConfig("DEFAULT_TIMER_WIDTH", UIConfig.timerWidth);
     hCfg.FindConfig("MIN_TIMER_HEIGHT", UIConfig.timerMinHeight);
     hCfg.FindConfig("MAX_TIMER_HEIGHT", UIConfig.timerMaxHeight);
     hCfg.FindConfig("DEFAULT_TIMER_COLOR_R", UIConfig.timer_R);
     hCfg.FindConfig("DEFAULT_TIMER_COLOR_G", UIConfig.timer_G);
     hCfg.FindConfig("DEFAULT_TIMER_COLOR_B", UIConfig.timer_B);
     hCfg.FindConfig("DEFAULT_TIMER_COLOR_A", UIConfig.timer_A);

     return true;
}
bool FishGameApp_ConfigHandler::Init_Player_Variables(FishGameApp_ConfigHandler& hCfg, Player_Config_State& playerConfig)
{
     hCfg.FindConfig("PLAYER_INDICATOR_WIDTH", playerConfig.player_W);
     hCfg.FindConfig("PLAYER_INDICATOR_HEIGHT", playerConfig.player_H);
     hCfg.FindConfig("PLAYER_X_POS", playerConfig.player_X);
     hCfg.FindConfig("PLAYER_Y_POS", playerConfig.player_Y);
     hCfg.FindConfig("DEFAULT_PLAYER_INDICATOR_COLOR_R", playerConfig.player_R);
     hCfg.FindConfig("DEFAULT_PLAYER_INDICATOR_COLOR_G", playerConfig.player_G);
     hCfg.FindConfig("DEFAULT_PLAYER_INDICATOR_COLOR_B", playerConfig.player_B);
     hCfg.FindConfig("DEFAULT_PLAYER_INDICATOR_COLOR_A", playerConfig.player_A);
     hCfg.FindConfig("POSITIVE_INDICATOR_COLOR_R", playerConfig.player_active_R);
     hCfg.FindConfig("POSITIVE_INDICATOR_COLOR_G", playerConfig.player_active_G);
     hCfg.FindConfig("POSITIVE_INDICATOR_COLOR_B", playerConfig.player_active_B);
     hCfg.FindConfig("POSITIVE_INDICATOR_COLOR_A", playerConfig.player_active_A);

     playerConfig.playerMarker.setSize(sf::Vector2f(stoi(playerConfig.player_W), stoi(playerConfig.player_H)));
     playerConfig.playerMarker.setPosition(stoi(playerConfig.player_X), stoi(playerConfig.player_Y));
     playerConfig.playerMarker.setFillColor(sf::Color(stoi(playerConfig.player_R), stoi(playerConfig.player_G), stoi(playerConfig.player_B), stoi(playerConfig.player_A)));


     hCfg.FindConfig("MARKER_TOP_LIMIT", playerConfig.markerTopLimit);
     hCfg.FindConfig("MARKER_BOTTOM_LIMIT", playerConfig.markerBottomLimit);


     return true;
}
bool FishGameApp_ConfigHandler::Init_Fish_Variables(FishGameApp_ConfigHandler& hCfg, Fish_Config_State& fishCfg)
{
     hCfg.FindConfig("FISH_ICON_PATH", fishCfg.fishIconPath);
     string fish_X, fish_Y, fishDif;

     hCfg.FindConfig("DEFAULT_FISH_X_POS", fish_X);
     hCfg.FindConfig("DEFAULT_FISH_Y_POS", fish_Y);
     hCfg.FindConfig("FISH_DIFFICULTY", fishDif);

     switch (stoi(fishDif))
     {
     case 1:
          fishCfg.fish.setDifficulty(Fish::DifficultyTier::EASY);
          break;
     case 2:
          fishCfg.fish.setDifficulty(Fish::DifficultyTier::MEDIUM);
          break;
     case 3:
          fishCfg.fish.setDifficulty(Fish::DifficultyTier::HARD);
          break;
     default:
          break;
     }

     if (!fishCfg.fishTexture.loadFromFile(fishCfg.fishIconPath))
     {
          // error...
          return false;
     }


     fishCfg.fish.setTexture(fishCfg.fishTexture);
     fishCfg.fish.setPosition(stoi(fish_X), stoi(fish_Y));




     return true;
}