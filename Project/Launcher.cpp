#include "Setting.h"
#include "Game.h"

#include "Lesson01_BgColor.h"
#include "Lesson02_Lerp.h"
#include "Lesson03_Animation.h"
#include "Lesson04_Movement.h"
#include "Lesson05_Input.h"
#include "Lesson06_ObjectPool.h"
#include "Lesson07_GUI.h"
#include "Lesson08_Rotation.h"
#include "Lesson09_Bullet.h"
#include "Lesson10_Platform.h"
#include "Lesson11_ParallaxScrolling.h"
#include "Zengame.h"
#include "Dino.h"
#include "AShroudedTomb_VeiledTruth.h"

#include "LessonAI01_SteeringBehaviors.h"
#include "LessonAI02_NPCWave.h"

int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->screenWidth = 1280;
	setting->screenHeight = 720;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 75;
	//Engine::Game* game = new Engine::Dino(setting);
	Engine::Game* game = new Engine::AShroudedTomb_VeiledTruth(setting);
	//Engine::Game* game = new Engine::Lesson10_Platform(setting);
	//Engine::Game* game = new Engine::Lesson06_ObjectPool(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
