#pragma once
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
		void Input();
		void Update();
		void Render();

		void FishOn() 
		{ 
			if (currState == GameState::OVER_WORLD) currState = GameState::MINI_GAME;
		}
		void WonLost() 
		{
			if (currState == GameState::MINI_GAME) currState = GameState::OVER_WORLD;
		}


		GameState currState{ OVER_WORLD };
		core::BasicWindow window;

	};
}
