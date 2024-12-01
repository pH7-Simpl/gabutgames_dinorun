#ifndef BROKENHEART_H
#define BROKENHEART_H

#include "Sprite.h"

namespace Engine {
	class BrokenHeart
	{
	public:
		BrokenHeart(Sprite* sprite);
		~BrokenHeart();
		void Update(float deltaTime, float x, float y);
		void ShowBrokenHeart();
		void Draw();
		float GetWidth();
		float GetHeight();
		float GetX();
		float GetY();
	protected:
		Sprite* sprite = NULL;
		float lerp_duration = 0, f = 0;
	};
}

#endif