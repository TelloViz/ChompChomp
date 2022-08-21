#pragma once
#include <vector>
#include <iostream>
#include <format>
#include "SFML/Graphics.hpp"
#include "../../Core/include/BasicWindow.h"

namespace game
{


	enum GameState{OVER_WORLD, MINI_GAME};
	enum GameStateTransition{FISH_ON, WIN_LOSE};

	class Game
	{
	public:
		Game();
		void Run();


	private:


		void InitOverWorld();
		void InitMiniGame();

		void Input(std::vector<sf::Event>& events);
		void Update();
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
		
		enum OverworldQuadrant { TL, TR, BL, BR };
		bool is_TL_Active{ false };
		bool is_TR_Active{ false };
		bool is_BL_Active{ false };
		bool is_BR_Active{ false };

		std::vector<sf::FloatRect> overworldQuadrantVec;

		GameState currState{ OVER_WORLD };
		core::BasicWindow window;
		sf::Vector2f DEFAULT_WINDOW_SIZE{ 500.0f,500.0f };
		sf::Texture pondTexture;
		sf::Sprite pondSprite;
		const sf::Vector2f DEFAULT_POND_SPRITE_SCALE{ 1.0f, 1.0f };

		std::vector<sf::Sprite> overworld_drawables;
		std::vector<sf::Sprite> minigame_drawables;

		bool isImagesLoaded{ false };

		sf::RectangleShape darkenedWaterOverlayShape; // TODO make a semi-transparent layer for the water tiles when fish is below surface.

	};
}
