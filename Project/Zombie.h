#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Sprite.h"

namespace Engine {
	enum class ZombieState {
		SPAWN,
		GROUND,
		DIE
	};
	class Zombie
	{
	public:
		Zombie(Sprite* sprite, Sprite* hand_sprite);
		~Zombie();
		void Update(float deltaTime);
		void Draw();
		Zombie* SetPosition(float x, float y);
		Zombie* SetHandPosition(float x, float y);
		Zombie* SetSpawn();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		float GetX();
		float GetY();
		Sprite* GetSprite();
		Sprite* GetHandSprite();
		void SetSprite(Sprite* sprite);
		Zombie* SetZombieState(ZombieState state);
		float GetHealth() const;
		void SetHealth(float x);
		void MoveTo(float x, float y, float speed);
		void MoveTo(float target_x, float target_y, float speed, bool moveAway);
		void PlayAnim(string x);
		float GetHitCooldown() const { return hitCooldown; }
		void SetHitCooldown(float cooldown) { hitCooldown = cooldown; }
		float colorLerpDuration = 0.0f;
		float GetSpeed() const;
	protected:
		Sprite* sprite = NULL;
		Sprite* hand_sprite = NULL;
		ZombieState state;
		float groundDur = 0, groundTime = 0;
		int zombie_health = 100;
		float x = 0, y = 0;
		float hitCooldown = 0.0f;
		float speed = 0.0f;
	};

}

#endif