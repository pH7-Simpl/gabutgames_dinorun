#include "Cactus.h"

Engine::Cactus::Cactus(Sprite* sprite)
{
	this->sprite = sprite;
	state = Engine::CactusState::DIE;
	groundDur = 0;
	groundTime = 1000;
}

Engine::Cactus::~Cactus()
{

}

void Engine::Cactus::Update(float deltaTime)
{
	if (state == Engine::CactusState::DIE) {
		return;
	}

	float x = GetX();
	float y = GetY();

	if (Engine::CactusState::SPAWN == state && x <= -70) {
		state = Engine::CactusState::GROUND;
	}

	if (state == Engine::CactusState::GROUND) {
		if (groundDur >= groundTime) {
			state = Engine::CactusState::DIE;
			groundDur = 0;
		}
		groundDur += deltaTime;
	}

	x -= xVelocity * deltaTime;
	sprite->SetPosition(x, y);
	sprite->Update(deltaTime);
}

void Engine::Cactus::Draw()
{
	if (state == Engine::CactusState::DIE) {
		return;
	}

	sprite->Draw();
}



Engine::Cactus* Engine::Cactus::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	return this;
}

Engine::Cactus* Engine::Cactus::SetSpawn()
{
	this->state = Engine::CactusState::SPAWN;
	return this;
}

float Engine::Cactus::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::Cactus::GetHeight()
{
	return sprite->GetScaleHeight();
}

bool Engine::Cactus::IsDie()
{
	return Engine::CactusState::DIE == state;
}

float Engine::Cactus::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::Cactus::GetY()
{
	return sprite->GetPosition().y;
}

Engine::Sprite* Engine::Cactus::GetSprite() {
	return sprite;
}

Engine::Cactus* Engine::Cactus::SetCactusState(CactusState state) {
	this->state = state;
	return this;
}

float Engine::Cactus::GetXVelocity() const {
	return xVelocity;
}
void Engine::Cactus::SetXVelocity(float x) {
	xVelocity = x;
	return;
}