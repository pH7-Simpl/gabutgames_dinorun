#include "Item.h"

Engine::Item::Item(string itemName, Sprite* sprite, AShroudedTomb_VeiledTruth* instance) : astvt(instance)
{
	this->sprite = sprite;
	item_name = itemName;
}

Engine::Item::~Item()
{

}

void Engine::Item::Init()
{
	sprite->SetScale(0.7f)->SetBoundingBoxSize(sprite->GetScaleWidth() - (9 * sprite->GetScale()), sprite->GetScaleHeight() - (10 * sprite->GetScale()))->SetPosition(-300, -300);
	Texture* text_box_texture = new Texture("chatbox.png");
	text_box_sprite = (new Sprite(text_box_texture, astvt->GetDefaultSpriteShader(), astvt->GetDefaultQuad()))->SetScale(0.07f);
	text_inside_box = (new Text("lucon.ttf", 10, astvt->GetDefaultTextShader()))->SetScale(1.0f)->SetColor(0, 0, 0)->SetText("Press (F)\nto collect");
}

void Engine::Item::Update(float deltaTime)
{
	if (sprite->GetBoundingBox()->CollideWith(astvt->mc_sprite1->GetBoundingBox())) {
		if (astvt->GetInputManager()->IsKeyReleased("pick_up")) {
			astvt->AddItem(this);
			SetPosition(-300, -300);
		}
	}
	sprite->Update(deltaTime);
	MoveUpdown(deltaTime);
}

void Engine::Item::Draw()
{
	if (sprite->GetBoundingBox()->CollideWith(astvt->mc_sprite1->GetBoundingBox())) {
		text_box_sprite->Draw();
		text_inside_box->Draw();
	}
	sprite->Draw();
}

void Engine::Item::MoveUpdown(float deltaTime)
{
	float x = GetX();
	float y = GetY();

	// Apply movement
	if (lerp_movement >= 50.0f) {
		y += (mul *= (f <= 0.0f || f >= 1.0f) ? -1 : 1) * 0.02f;
	}
	lerp_movement += deltaTime;
	sprite->SetPosition(x, y);
}



Engine::Item* Engine::Item::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	text_box_sprite->SetPosition(x + sprite->GetScaleWidth() / 4, y + sprite->GetScaleHeight() / 2);
	text_inside_box->SetPosition(x + sprite->GetScaleWidth() / 1.8, y + sprite->GetScaleHeight() * 2.2);
	return this;
}

float Engine::Item::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::Item::GetHeight()
{
	return sprite->GetScaleHeight();
}

float Engine::Item::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::Item::GetY()
{
	return sprite->GetPosition().y;
}

Engine::Sprite* Engine::Item::GetSprite() {
	return sprite;
}

void Engine::Item::SetSprite(Sprite* sprite) {
	this->sprite = sprite;
}