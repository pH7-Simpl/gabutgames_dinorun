#include "ZenGame.h"

Engine::ZenGame::ZenGame(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Zen Game hehehehehehe";
}

Engine::ZenGame::~ZenGame()
{
}

void Engine::ZenGame::Init()
{
	r = 255;
	g = 255;
	b = 255;
	mul = 1;
}

void Engine::ZenGame::Update()
{
	if (color_duration >= 50) {
		/*if (r <= 0 || r >= 255) {
			mul *= -1;
		}*/
		//mul *= (r <= 0 || r >= 255) ? -1 : 1;
		//r += mul * 5;
		r += (mul *= (r <= 0 || r >= 255) ? -1 : 1) * 5;
		SetBackgroundColor(r, g, b);
		g += (mul *= (g <= 0 || g >= 255) ? -1 : 1) * 5;
		SetBackgroundColor(r, g, b);
		b += (mul *= (b <= 0 || b >= 255) ? -1 : 1) * 5;
		SetBackgroundColor(r, g, b);
		color_duration = 0;
	}
	color_duration += GetGameTime();
}

void Engine::ZenGame::Render()
{

}