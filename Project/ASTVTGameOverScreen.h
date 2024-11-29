#ifndef ASTVTGAMEOVERSCREEN_H
#define ASTVTGAMEOVERSCREEN_H

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"
#include "AShroudedTomb_VeiledTruth.h"

namespace Engine {
	class AShroudedTomb_VeiledTruth;
	class ASTVTGameOverScreen :
		public Engine::Screen
	{
	public:
		ASTVTGameOverScreen(AShroudedTomb_VeiledTruth* instance);
		void Init();
		void Update();
		void Draw();
		void SetBestScoreText();
	private:
		vector<Button*> buttons;
		Text* gameOverText = NULL;
		Text* bestScoreText = NULL;
		int currentButtonIndex = 0;
		AShroudedTomb_VeiledTruth* astvt;
	};
}

#endif
