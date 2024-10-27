#ifndef DINOGAMESCREEN_H
#define DINOGAMESCREEN_H

#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Cactus.h"
#include "Text.h"
#include <vector>
#include "Screen.h"
#include "ScreenManager.h"
#include "Dino.h"

namespace Engine {
	class Dino;
	class DinoGameScreen :
		public Engine::Screen
	{
	public:
		DinoGameScreen(Dino* dinoInstance);
		void Init();
		void Update();
		void Draw();
		void GameOver();
	private:
		Texture* texture = NULL;
		Sprite* sprite = NULL;
		float yVelocity = 0, gravity = 0;
		bool jump = false, debug = false;
		Texture* cactus_texture = NULL;
		Engine::Sprite* CreateCactusSprite();
		void SpawnCacti();
		void ScorePerDuration(float seconds);
		vector<Engine::Cactus*> cacti;
		float spawnCactusDuration = 0, maxCactusSpawnTime = 0, numCactusInPool = 0, numCactusPerSpawn = 0, scoreDuration = 0;
		Text* scoreText = NULL;
		Dino* dino;
		vector<Sprite*> backgrounds, middlegrounds, foregrounds;
		void MoveLayer(vector<Sprite*>& bg, float speed);
		void DrawLayer(vector<Sprite*>& bg);
		void AddToLayer(vector<Sprite*>& bg, string name);
		void PlayJumpAnim();
		float offset = 0;
		bool paused = false;
		float speed = 0.2f;
		float speedIncrease = 0.1f;
	};
}

#endif

