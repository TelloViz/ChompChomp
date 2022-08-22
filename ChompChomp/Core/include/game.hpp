#pragma once


#include "BasicWindow.h"
#include "../include/TickClock.hpp"
#include "../deps/random.hpp"
#include "../include/ConfigHandler.h"

#include <vector>
#include <iostream>
#include <format>
#include <string>
#include "SFML/Graphics.hpp"

namespace game
{

	

	enum GameState{OVER_WORLD, MINI_GAME};
	enum GameStateTransition{FISH_ON, WIN_LOSE};

	class Game
	{
		//friend class core::DebugState;
	public:
		Game();
		void Run();


	private:

		void LoadConfig();
		void InitOverWorld();
		void InitMiniGame();

		void Input(std::vector<sf::Event>& events);
		void Update(float dt);
		void Render();

		void PollEvents(std::vector<sf::Event>& eventVec);

		void FishOn() 
		{ 
			if (currState == GameState::OVER_WORLD) currState = GameState::MINI_GAME;
		}
		void WonLost() 
		{
			if (currState == GameState::MINI_GAME) currState = GameState::OVER_WORLD;
		}

		int RandomInt(int min, int max)
		{
			return effolkronium::random_static::get(min, max);
		}

		void OnClose(sf::Event& event);
		void OnResized(sf::Event& event);
		void OnLostFocus(sf::Event& event);
		void OnGainedFocus(sf::Event& event);
		void OnKeyPressed(sf::Event& event);
		void OnKeyReleased(sf::Event& event);
		void OnMouseButtonPressed(sf::Event& event);
		void OnMouseButtonReleased(sf::Event& event);
		void OnMouseMoved(sf::Event& event);
		void OnMouseEntered(sf::Event& event);
		void OnMouseLeft(sf::Event& event);

		void OnOverWorld_MousePressed(sf::Event& event);
		void OnOverWorld_MouseReleased(sf::Event& event);
		
		void OnMiniGame_MousePressed(sf::Event& event);
		void OnMiniGame_MouseReleased(sf::Event& event);
		
		enum OverworldQuadrant { TL, TR, BL, BR, NONE };
		OverworldQuadrant activeQuadrant{ TL };
		bool is_TL_Active{ false };
		bool is_TR_Active{ false };
		bool is_BL_Active{ false };
		bool is_BR_Active{ false };

		std::vector<OverworldQuadrant> overworldEnumVec
		{
			OverworldQuadrant::TL,
			OverworldQuadrant::TR,
			OverworldQuadrant::BL,
			OverworldQuadrant::BR
		};

		std::vector<sf::FloatRect> overworldQuadrantVec
		{
			sf::FloatRect(sf::Vector2f(128.0f,128.0f), sf::Vector2f(120.0f,120.0f)),
			sf::FloatRect(sf::Vector2f(253.0f, 128.0f), sf::Vector2f(120.0f, 120.0f)),
			sf::FloatRect(sf::Vector2f(128.0f, 253.0f), sf::Vector2f(120.0f,120.0f)),
			sf::FloatRect(sf::Vector2f(253.0f, 253.0f), sf::Vector2f(120.0f, 120.0f))
		};
		
		sf::RectangleShape darkenedWaterOverlayShape; // TODO make a semi-transparent layer for the water tiles when fish is below surface.
		const sf::Time dtPerDarkenedPool{ sf::Time(sf::seconds(120.0f / 60.0f)) };
		sf::Time dtPerPoolAccumulator{ sf::Time{} };

		GameState currState{ OVER_WORLD };
		core::BasicWindow window;
		sf::Vector2f DEFAULT_WINDOW_SIZE{ 500.0f,500.0f };

		core::BasicWindow debugWindow;
		sf::Vector2f DEFAULT_DEBUG_WINDOW_SIZE{ 300.0f, 150.0f };

		core::TickClock clock;

		sf::Texture pondTexture;
		sf::Sprite pondSprite;
		const sf::Vector2f DEFAULT_POND_SPRITE_SCALE{ 5.0f,5.0f };
		sf::Vector2f	 prevSpriteScale{ DEFAULT_POND_SPRITE_SCALE };

		bool shouldIncreaseScale{ false };
		bool shouldDecreaseScale{ false };

		std::vector<sf::Sprite> overworld_drawables;
		std::vector<sf::Sprite> minigame_drawables;

		bool isImagesLoaded{ false };

		void PollDebugEvents();
		void DebugUpdate();
		void DebugRender();


		sf::Font DEFAULT_FONT;
		std::string DEFAULT_FONT_FILEPATH{ "arial.ttf" };
		int DEFAULT_CHAR_SIZE{ 32 };
		sf::Color DEFAULT_COLOR{ sf::Color::White };
		sf::Text::Style DEFAULT_TEXT_STYLE{ sf::Text::Regular };
		std::string MOUSE_POS_MSG{ "Mouse Pos: " };
		sf::Text mousePosText;

		
		
	};
}
