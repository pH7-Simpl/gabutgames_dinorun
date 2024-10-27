#ifndef ZENGAME_H
#define ZENGAME_H

#include "Game.h"
#include "Setting.h"

namespace Engine {
	class ZenGame :public Engine::Game
	{
	public:
		ZenGame(Setting* setting);
		~ZenGame();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		float color_duration;
		int r, g, b;
		int mul;
	};
}

#endif

