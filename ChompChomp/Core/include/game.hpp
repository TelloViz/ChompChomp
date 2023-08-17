#pragma once


#include "BasicWindow.h"
#include "../include/TickClock.hpp"
#include "random.hpp"
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
		void InitDebugFonts();
		void InitDebugWindow();

		void Input(std::vector<sf::Event>& events);
		void Update(float dt);
		void Render();

		void UpdatePlayerMarker(float dt);
		void UpdateFishMarker(float dt);
		void UpdateShrinkingTimerMarker(float dt);

		void PollEvents(std::vector<sf::Event>& eventVec);

		void FishOn() 
		{ 
			if (currState == GameState::OVER_WORLD) currState = GameState::MINI_GAME;
			InitMiniGame();
		}
		void WonLost() 
		{
			if (currState == GameState::MINI_GAME) currState = GameState::OVER_WORLD;
			timeRemaining = DEFAULT_MINI_GAME_START_TIME;
			InitOverWorld();
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

		void SetPlayerAtMaxPosition();
		void SetPlayerAtMinPosition();
		
		enum OverworldQuadrant { TL, TR, BL, BR, NONE };
		OverworldQuadrant activeQuadrant{ NONE };

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

		sf::Color DEFAULT_DARKENED_WATER_COLOR{ sf::Color(0.0f, 0.0f, 0.0f, 75.0f) };


		enum FishDirection{UP=-1, STILL=0, DOWN=1};
		FishDirection currDirection{STILL};
		

		int minFishSpeed{10};
		int maxFishSpeed{30};
		int currFishSpeed{0};

		const sf::Time dtPerDirectionChange{ sf::Time(sf::seconds(90.0f / 60.0f)) };
		sf::Time dtPerDirectionChangeAcuumulator{ sf::Time{} };

		const sf::Time dtPerSpeedChange{ sf::Time(sf::seconds(100.0f / 60.0f)) };
		sf::Time dtPerSpeedChangeAcuumulator{ sf::Time{} };

		std::string DEFAULT_GAME_WINDOW_TITLE{ "Gyo-Fish" };
		GameState currState{ OVER_WORLD };
		core::BasicWindow window;
		sf::Vector2u DEFAULT_WINDOW_SIZE{ 500,500 };

		core::BasicWindow debugWindow;
		sf::Vector2u DEFAULT_DEBUG_WINDOW_SIZE{ 300, 150 };

		core::TickClock clock;
		const sf::Time DEFAULT_MINI_GAME_START_TIME{sf::Time( sf::seconds(20.0f ) )};
		sf::Time timeRemaining;

		sf::Texture pondTexture;
		sf::Sprite pondSprite;
		const sf::Vector2f DEFAULT_POND_SPRITE_SCALE{ 5.0f,5.0f };
		//sf::Vector2f	 prevSpriteScale{ DEFAULT_POND_SPRITE_SCALE };
		//bool shouldIncreaseScale{ false };
		//bool shouldDecreaseScale{ false };

		sf::Texture miniGameTexture;
		sf::Sprite miniGameSprite;
		const sf::Vector2f DEFAULT_MINIGAME_SPRITE_SCALE{ 1.0f , 1.0f };

		sf::Texture fishMarkerTexture;
		sf::Sprite fishMarkerSprite;
		const sf::Vector2f DEFAULT_FISH_MARKER_SCALE{ 1.0f, 1.0f };

		sf::RectangleShape playerMarker;
		const sf::Vector2f DEFAULT_PLAYER_STARTING_POS{ 229.0f,250.0f };
		const sf::Vector2f MAX_UPWARD_MARKER_POS{229.0f, 40.0f};
		const sf::Vector2f MAX_DOWNWARD_MARKER_POS{229.0f, 415.0f};
		const sf::Vector2f DEFAULT_PLAYER_MARKER_SIZE{25.0f, 45.0f};
		const sf::Color DEFAULT_PLAYER_MARKER_COLOR{ sf::Color::Green };
		const sf::Color DEFAULT_PLAYER_MARKER_ACTIVE_COLOR{ sf::Color::Magenta };
		const sf::Vector2f DEFAULT_MARKER_VELOCITY{ 50.0f,70.0f };
		enum MarkerDirection{UP_DIR = -1,NO_DIR =0, DOWN_DIR = 1};
		MarkerDirection currMarkerDirection{ NO_DIR };

		sf::RectangleShape timerMarker;
		const sf::Vector2f DEFAULT_TIMER_STARTING_POS{ 288.0f,32.0f };
		const sf::Vector2f MAX_UPWARD_TIMER_POS{ 288.0f, 32.0f };
		const sf::Vector2f MAX_DOWNWARD_TIMER_POS{ 288.0f, 436.0f };
		const sf::Vector2f DEFAULT_TIMER_MARKER_SIZE{ 8.0f, 436.0f };
		const sf::Color DEFAULT_TIMER_MARKER_COLOR{ sf::Color::Cyan };
		
		
		sf::RectangleShape timerShrinkingMarker;
		const sf::Vector2f DEFAULT_SHRINKING_TIMER_STARTING_POS{ 288.0f,32.0f };
		//const sf::Vector2f MAX_UPWARD_TIMER_POS{ 288.0f, 32.0f };
		//const sf::Vector2f MAX_DOWNWARD_TIMER_POS{ 288.0f, 436.0f };
		const sf::Vector2f DEFAULT_SHRINKING_TIMER_MARKER_SIZE{ 8.0f, 100.0f };
		const sf::Color DEFAULT_SHRINKING_TIMER_MARKER_COLOR{ sf::Color::Magenta };
		const sf::Vector2f DEFAULT_SHRINKING_TIMER_MARKER_VELOCITY{ 0.0f, -5.0f };


		enum TimerMarkerDirection { TIMER_UP_DIR = -1, TIMER_NO_DIR = 0, TIMER_DOWN_DIR = 1 };
		TimerMarkerDirection currTimerMarkerDirection{ TIMER_NO_DIR };


		bool isImagesLoaded{ false };

		void PollDebugEvents();
		void DebugUpdate();
		void DebugRender();


		/* DEBUG FIELDS */
		sf::Font DEFAULT_FONT;
		std::string DEFAULT_FONT_FILEPATH{ "arial.ttf" };
		int DEFAULT_CHAR_SIZE{ 32 };
		sf::Color DEFAULT_COLOR{ sf::Color::White };
		sf::Text::Style DEFAULT_TEXT_STYLE{ sf::Text::Regular };


		std::string MOUSE_POS_MSG{ "Mouse Pos: " };
		sf::Text mousePosText;

		std::string TIMER_COUNTER_MSG{ "Time Left: " };
		sf::Text timerText;
		/* END DEBUG FIELDS */
		
		
	};
}
