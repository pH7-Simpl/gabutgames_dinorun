#ifndef ASTVTMAINMENUSCREEN_H
#define ASTVTMAINMENUSCREEN_H

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"

namespace Engine {
	class ASTVTMainMenuScreen :
		public Engine::Screen
	{
	public:
		ASTVTMainMenuScreen();
		void Init();
		void Update();
		void Draw();
	private:
		Sprite* backgroundSprite = NULL;
		vector<Button*> buttons;
		Text* text;
		int currentButtonIndex = 0;
	};
}

#endif
