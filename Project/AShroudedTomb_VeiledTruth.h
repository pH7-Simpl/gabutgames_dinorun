#ifndef ASHROUDEDTOMB_VEILEDTRUTH_H
#define ASHROUDEDTOMB_VEILEDTRUTH_H

#include "Game.h"
#include "Sound.h"
#include "Music.h"
#include "Setting.h"
#include "ASTVTGameScreen.h"
#include "ASTVTMainMenuScreen.h"
#include "ASTVTPauseScreen.h"
#include "ASTVTGameOverScreen.h"
#include "Zombie.h"
#include "Item.h"
#include "json.hpp"
#include <fstream>

namespace Engine {
	class Item;
	class AShroudedTomb_VeiledTruth :public Engine::Game
	{
	public:
		AShroudedTomb_VeiledTruth(Setting* setting);
		~AShroudedTomb_VeiledTruth();
		virtual void Init();
		virtual void Update();
		virtual void Render();
		void SaveGame();
		void LoadGame();
		void ResetGame();
		void SaveSettings();
		void LoadSettings();
		void SetPlayerSpeed(float x);
		float GetPlayerSpeed() const;
		void GameOver();
		void AddItem(Item* itemname);
		bool HaveItem(string itemName) const;
		void SetStoryPhase(float x);
		float GetStoryPhase() const;
		void SetZombieCount(float x);
		int GetZombieCount() const;
		void SetPlayerHealth(float x);
		int GetPlayerHealth() const;
		int GetSwordDamage() const;
		int GetZombieDamage() const;
		vector<Zombie*> zombies;
		vector<Item*> items;
		vector<Item*> items_to_collect;
		bool narrating = false;
		float GetPlayerDyingDuration() const { return player_dying_duration; }
		void SetPlayerDyingDuration(float cooldown) { player_dying_duration = cooldown; }
		int GetZombiePerSpawn() const { return zombie_per_spawn; }
		int GetZombieToDefeatPerWave() const { return zombie_to_defeat_per_wave; }
		Sprite* mc_sprite1 = NULL;
		Sprite* mc_sprite2 = NULL;
		Texture* mc_texture1 = NULL;
		Texture* mc_texture2 = NULL;
	private:
		string playerName = "Adaline";
		int playerHealth = 100;
		float playerSpeed = 2.0f;
		int story_phase = 0;
		float player_dying_duration = 0;
		int zombie_count = 0;
		int swordDamage = 25;
		int zombie_per_spawn = 2;
		int zombie_to_defeat_per_wave = 10;
		int zombieDamage = 10;
	};
}

#endif

