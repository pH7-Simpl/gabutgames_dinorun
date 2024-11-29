#include "Zombie.h"

Engine::Zombie::Zombie(Sprite* sprite, Sprite* hand_sprite)
{
	this->sprite = sprite;
	this->hand_sprite = hand_sprite;
	state = Engine::ZombieState::DIE;
	groundDur = 0;
	groundTime = 1000;
	speed = 1.0f;
}

Engine::Zombie::~Zombie()
{

}

void Engine::Zombie::Update(float deltaTime)
{
	if (state == Engine::ZombieState::DIE) {
		return;
	}

	if (Engine::ZombieState::SPAWN == state && zombie_health <= 0) {
		state = Engine::ZombieState::GROUND;
	}

	if (state == Engine::ZombieState::GROUND) {
		sprite->PlayAnim("die");
		if (groundDur >= groundTime) {
			state = Engine::ZombieState::DIE;
			groundDur = 0;
			
		}
		groundDur += deltaTime;
	}
	sprite->Update(deltaTime);
}

void Engine::Zombie::Draw()
{
	if (state == Engine::ZombieState::DIE) {
		return;
	}

	sprite->Draw();
}

void Engine::Zombie::MoveTo(float target_x, float target_y, float speed)
{
	vec2 position = sprite->GetPosition();
	float x = GetX();
	float y = GetY();
	float deltaX = target_x - x;
	float deltaY = target_y - y;

	// Check if the target is already reached
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	if (distance < 1.0f) { // Threshold to stop moving
		return;
	}
	if (distance != 0) {
		deltaX /= distance;
		deltaY /= distance;
	}

	// Apply movement
	position.x += deltaX * speed;
	position.y += deltaY * speed;
	sprite->SetPosition(position.x, position.y);
}

void Engine::Zombie::MoveTo(float target_x, float target_y, float speed, bool moveAway = false) {
	vec2 position = sprite->GetPosition();
	float x = GetX();
	float y = GetY();
	float deltaX = target_x - x;
	float deltaY = target_y - y;

	// Calculate distance
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

	// Stop moving if close enough (for towards movement)
	if (!moveAway && distance < 1.0f) { // Threshold for stopping
		return;
	}

	// Normalize the movement vector
	if (distance != 0) {
		deltaX /= distance;
		deltaY /= distance;
	}

	// Reverse direction if moving away
	if (moveAway) {
		deltaX = -deltaX;
		deltaY = -deltaY;
	}

	// Apply movement
	position.x += deltaX * speed;
	position.y += deltaY * speed;
	sprite->SetPosition(position.x, position.y);
}



Engine::Zombie* Engine::Zombie::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
	return this;
}

Engine::Zombie* Engine::Zombie::SetHandPosition(float x, float y)
{
	hand_sprite->SetPosition(x, y);
	return this;
}

Engine::Zombie* Engine::Zombie::SetSpawn()
{
	this->state = Engine::ZombieState::SPAWN;
	return this;
}

float Engine::Zombie::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::Zombie::GetHeight()
{
	return sprite->GetScaleHeight();
}

bool Engine::Zombie::IsDie()
{
	return Engine::ZombieState::DIE == state;
}

float Engine::Zombie::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::Zombie::GetY()
{
	return sprite->GetPosition().y;
}

Engine::Sprite* Engine::Zombie::GetSprite() {
	return sprite;
}

Engine::Sprite* Engine::Zombie::GetHandSprite() {
	return hand_sprite;
}

void Engine::Zombie::SetSprite(Sprite* sprite) {
	this->sprite = sprite;
}

Engine::Zombie* Engine::Zombie::SetZombieState(ZombieState state) {
	this->state = state;
	return this;
}

float Engine::Zombie::GetHealth() const {
	return zombie_health;
}

float Engine::Zombie::GetSpeed() const {
	return speed;
}

void Engine::Zombie::SetHealth(float x) {
	zombie_health = x;
	return;
}

void Engine::Zombie::PlayAnim(string x) {
	sprite->PlayAnim(x);
	return;
}