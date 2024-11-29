#ifndef ASTVTPAUSESCREEN_H
#define ASTVTPAUSESCREEN_H

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
	class ASTVTPauseScreen :
		public Engine::Screen
	{
	public:
		ASTVTPauseScreen(AShroudedTomb_VeiledTruth* instance);
		void Init();
		void Update();
		void Draw();
	private:
		AShroudedTomb_VeiledTruth* astvt;
		Sprite* backgroundSprite = NULL;
		vector<Button*> buttons;
		Text* text;
		int currentButtonIndex = 0;
	};
}

#endif
