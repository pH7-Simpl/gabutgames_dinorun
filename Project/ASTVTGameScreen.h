#ifndef ASTVTGAMESCREEN_H
#define ASTVTGAMESCREEN_H

#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Text.h"
#include "Screen.h"
#include "ScreenManager.h"
#include "Zombie.h"
#include "AShroudedTomb_VeiledTruth.h"
#include "Sound.h"
#include "BrokenHeart.h"

namespace Engine {
	class AShroudedTomb_VeiledTruth;
	class BrokenHeart;
	class ASTVTGameScreen :
		public Engine::Screen
	{
	public:
		ASTVTGameScreen(AShroudedTomb_VeiledTruth* instance);
		void Init();
		void Update();
		void Draw();
		int Lerp(float a, float b, float f);
		void ShowNaration();
		void Narrate(string input);
		void NarrationFadeIn(float lerp_speed);
		void NarrationFadeOut(float lerp_speed);
		void NarrationRegulator();
		void ZombieRegulator();
		void EndSceneRegulator();
		void CharacterMovement();
		float GetHitCooldown() const { return hitCooldown; }
		void SetHitCooldown(float cooldown) { hitCooldown = cooldown; }
		bool IsHit() const { return hit; }
		void SetHit(bool hitt) { hit = hitt; }
		void PlayerHitMechanism();
		int Clamp(int value, int min, int max);
	private:
		bool debug = false;
		Texture* dotTexture = NULL;
		Texture* sword_texture = NULL;
		Sprite* sword_sprite = NULL;
		AShroudedTomb_VeiledTruth* astvt;
		Text* debugText = NULL;
		float x = 0, y = 0, attack_cooldown = 0, lerp_duration = 0, master_time = 0.0f;
		int current_page_index = 0;
		bool attacking = false, fade_in = false;
		vector<Sprite*> dotSprites;
		void SwordMovement(int direction);
		string full_narration;
		string displayed_naration;
		float text_display_speed = 50.0f, read_time = 3000.0f;
		float time_since_last_character = 0.0f;
		int current_character_index = 0;
		Text* narration_text = NULL;
		vector<string> narration_pages;
		Texture* zombie_texture = NULL;
		float spawnZombieDuration = 0, maxZombieSpawnTime = 500, numZombieInPool = 100;
		Engine::Sprite* CreateZombieSprite();
		void SpawnZombies();
		void KillAllZombies();
		float hitCooldown = 0;
		float colorLerpDuration = 0;
		bool hit = false;
		Sound* item_drop = NULL;
		Sound* mc_damage = NULL;
		Sound* death = NULL;
		Sound* mc_walk = NULL;
		Sound* sword_swing_hit = NULL;
		Sound* sword_swing_miss = NULL;
		Sprite* heart_sprite = NULL;
		Text* player_hp_text = NULL;
		Sprite* skull_sprite = NULL;
		Text* zombie_count = NULL;
		BrokenHeart* player_broken_heart = NULL;
	};
}

#endif

