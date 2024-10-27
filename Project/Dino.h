#ifndef DINO_H
#define DINO_H

#include "Game.h"
#include "Sound.h"
#include "Music.h"
#include "Setting.h"
#include "DinoMainMenuScreen.h"
#include "DinoGameScreen.h"
#include "DinoGameOverScreen.h"
#include "DinoPauseScreen.h"

namespace Engine {
	class Dino :public Engine::Game
	{
	public:
		Dino(Setting* setting);
		~Dino();
		virtual void Init();
		virtual void Update();
		virtual void Render();
		int GetScore() const;
		void SetScore(int x);
		int GetBestScore() const;
		void SetBestScore(int x);
		Music* music = NULL;
		Sound* sound = NULL;
	private:
		int score = 0;
		int bestScore = 0;
	};
}

#endif

