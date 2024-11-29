#ifndef ITEM_H
#define ITEM_H

#include "Sprite.h"
#include "AShroudedTomb_VeiledTruth.h"

namespace Engine {
	class AShroudedTomb_VeiledTruth;
	class Item
	{
	public:
		Item(string itemName, Sprite* sprite, AShroudedTomb_VeiledTruth* instance);
		~Item();
		virtual void Init();
		void Update(float deltaTime);
		void Draw();
		Item* SetPosition(float x, float y);
		void MoveUpdown(float speed);
		float GetWidth();
		float GetHeight();
		float GetX();
		float GetY();
		Sprite* GetSprite();
		void SetSprite(Sprite* sprite);
		string GetName() const { return item_name; }

	protected:
		AShroudedTomb_VeiledTruth* astvt = NULL;
		Sprite* sprite = NULL;
		Sprite* text_box_sprite = NULL;
		Text* text_inside_box = NULL;
		float lerp_movement = 0, f = 0, mul = -1;
		string item_name = "";
	};

}

#endif