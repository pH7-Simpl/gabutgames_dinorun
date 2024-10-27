#ifndef DINOGAMEOVERSCREEN_H
#define DINOGAMEOVERSCREEN_H

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"
#include "Dino.h"

namespace Engine {
	class Dino;
	class DinoGameOverScreen :
		public Engine::Screen
	{
	public:
		DinoGameOverScreen(Dino* dinoInstance);
		void Init();
		void Update();
		void Draw();
		void SetBestScoreText();
	private:
		vector<Button*> buttons;
		Text* gameOverText = NULL;
		Text* bestScoreText = NULL;
		int currentButtonIndex = 0;
		Dino* dino;
	};
}

#endif
