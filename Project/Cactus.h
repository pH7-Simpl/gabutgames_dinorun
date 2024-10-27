#ifndef CACTUS_H
#define CACTUS_H

#include "Sprite.h"

namespace Engine {
	enum class CactusState {
		SPAWN,
		GROUND,
		DIE
	};
	class Cactus
	{
	public:
		Cactus(Sprite* sprite);
		~Cactus();
		void Update(float deltaTime);
		void Draw();
		Cactus* SetPosition(float x, float y);
		Cactus* SetSpawn();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		float GetX();
		float GetY();
		Sprite* GetSprite();
		Cactus* SetCactusState(CactusState state);
		float GetXVelocity() const;
		void SetXVelocity(float x);
	protected:
		Sprite* sprite = NULL;
		CactusState state;
		float groundDur = 0, groundTime = 0, x = 0, y = 0;
		float xVelocity = 0.2f;
	};

}

#endif