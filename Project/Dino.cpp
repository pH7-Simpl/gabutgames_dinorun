#include "Dino.h"

Engine::Dino::Dino(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Dino Game";
}

Engine::Dino::~Dino()
{
}

void Engine::Dino::Init()
{
	Engine::ScreenManager::GetInstance(this)->AddScreen("dino", new DinoGameScreen(this))
		->AddScreen("mainmenu", new DinoMainMenuScreen())->AddScreen("dinoover", new DinoGameOverScreen(this))
		->AddScreen("dinopause", new DinoPauseScreen())->SetCurrentScreen("mainmenu");
	score = 0;
	music = (new Music("2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.ogg"))->SetVolume(40)->Play(true);

	sound = (new Sound("jump.wav"))->SetVolume(100);
}

void Engine::Dino::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::Dino::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}

int Engine::Dino::GetScore() const {
	return score;
}

void Engine::Dino::SetScore(int x) {
	score = x;
}

int Engine::Dino::GetBestScore() const {
	return bestScore;
}

void Engine::Dino::SetBestScore(int x) {
	bestScore = x;
}



