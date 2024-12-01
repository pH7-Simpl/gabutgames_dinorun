#include "BrokenHeart.h"

Engine::BrokenHeart::BrokenHeart(Sprite* sprite)
{
	this->sprite = sprite;
}

Engine::BrokenHeart::~BrokenHeart()
{

}

void Engine::BrokenHeart::Update(float deltaTime, float x, float y)
{
	if (f >= 0) {
		if (lerp_duration >= 10.0f) {
			f -= 0.06f;
			sprite->SetColor(1.0f, 1.0f, 1.0f, f);
			y -= f * 10;
			sprite->SetPosition(x, y);
			lerp_duration = 0;
		}
	}
	else {
		if ((sprite->GetPosition().x != -300) && (sprite->GetPosition().y != -300)) {
			sprite->SetPosition(-300, -300);
		}
	}
	lerp_duration += deltaTime;
	sprite->Update(deltaTime);
}

void Engine::BrokenHeart::ShowBrokenHeart()
{
	f = 1.0f;
}

void Engine::BrokenHeart::Draw()
{
	if (f >= 0) {
		sprite->Draw();
	}
}

float Engine::BrokenHeart::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::BrokenHeart::GetHeight()
{
	return sprite->GetScaleHeight();
}

float Engine::BrokenHeart::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::BrokenHeart::GetY()
{
	return sprite->GetPosition().y;
}
