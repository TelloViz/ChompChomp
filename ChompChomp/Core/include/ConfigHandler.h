/* This class should handle read/write to/from the config file for fish */



#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "Fish.h"

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::map;  using std::ifstream; 
using std::vector; using std::fstream;


struct UI_Config_State
{
     string
          canvasWidth{},
          canvasHeight{},
          canvas_X{},
          canvas_Y{},
          windowWidth,
          windowHeight,
          frame;

     sf::Texture frameTexture;
     sf::RectangleShape canvasShape;
     sf::Sprite frameSprite;

     string timer_X, timer_Y,
          timerWidth, timerMinHeight, timerMaxHeight,
          timer_R, timer_G, timer_B, timer_A;

};

struct Player_Config_State
{
     string
          player_W,
          player_H,
          player_X,
          player_Y,
          player_R,
          player_G,
          player_B,
          player_A,
          player_active_R,
          player_active_G,
          player_active_B,
          player_active_A,
          markerTopLimit,
          markerBottomLimit;
     sf::RectangleShape playerMarker;
};

struct Fish_Config_State
{
     Fish fish;
     sf::Texture fishTexture;
     string fishIconPath;
};


class FishGameApp_ConfigHandler
{
public:
     bool ReadConfigFile();
     bool WriteConfigFile();
     bool FindConfig(string key, string& value);
     bool AlterValue(string key, string newVal);




     bool Init_UI_Variables(FishGameApp_ConfigHandler& hCfg, UI_Config_State& UIConfig, Fish_Config_State& fCfg);
     bool Init_Player_Variables(FishGameApp_ConfigHandler& cfgHandler, Player_Config_State& plCfg);
     bool Init_Fish_Variables(FishGameApp_ConfigHandler& hCfg, Fish_Config_State& fishCfg);

private:
     bool ParseConfigFile(const vector<string>& lines);
     map<string, string> configValueMap;
     vector<string> keys;



};

