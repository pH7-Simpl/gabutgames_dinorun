#include "DinoGameScreen.h"

Engine::DinoGameScreen::DinoGameScreen(Dino* dinoInstance) : dino(dinoInstance)
{
	
}

void Engine::DinoGameScreen::Init()
{
	Texture* texture = new Texture("monster.png");
	sprite = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	sprite->SetPosition(200, 0)->SetNumXFrames(6)->SetNumYFrames(3)->SetAnimationDuration(70)->SetScale(2.0f)->AddAnimation("attack", 13, 14)->AddAnimation("idle", 0, 3)->AddAnimation("run", 6, 11);
	sprite->SetBoundingBoxSize(sprite->GetScaleWidth() - (16 * sprite->GetScale()),
		sprite->GetScaleHeight() - (4 * sprite->GetScale()));

	//Paralax
	for (int i = 0; i <= 4; i++) {
		AddToLayer(backgrounds, "bg0" + to_string(i) + ".png");
	}
	for (int i = 5; i <= 8; i++) {
		AddToLayer(middlegrounds, "bg0" + to_string(i) + ".png");
	}
	for (int i = 9; i <= 9; i++) {
		AddToLayer(foregrounds, "bg0" + to_string(i) + ".png");
	}

	offset = 2;

	// Add input mapping 
	game->GetInputManager()->AddInputMapping("pause", SDLK_ESCAPE)->AddInputMapping("Jump", SDLK_SPACE);

	// Spawn cactus setting
	maxCactusSpawnTime = 500;
	numCactusPerSpawn = 1;
	numCactusInPool = 100;

	// Cactus Texture
	cactus_texture = new Texture("turtles.png");
	for (int i = 0; i < numCactusInPool; i++) {
		Cactus* c = new Cactus(CreateCactusSprite());
		cacti.push_back(c);
	}

	scoreText = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	scoreText->SetScale(2.2f)->SetColor(64, 64, 64)->SetPosition((game->GetSettings()->screenWidth)/2, game->GetSettings()->screenHeight - (scoreText->GetFontSize() * scoreText->GetScale()) - 100);

}

void Engine::DinoGameScreen::Update()
{
	// Backrounds
	MoveLayer(backgrounds, speed * 0.025f);
	MoveLayer(middlegrounds, speed * 0.15f);
	MoveLayer(foregrounds, speed * 1.0f);
	// If user press "Quit" key then exit
	if (game->GetInputManager()->IsKeyReleased("pause")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("dinopause");
	}

	vec2 oldMonsterPos = sprite->GetPosition();
	float x = oldMonsterPos.x, y = oldMonsterPos.y;

	sprite->PlayAnim("run")->SetFlipHorizontal(false);
	sprite->Update(game->GetGameTime());

	if (game->GetInputManager()->IsKeyPressed("Jump") && !jump) {
		//Set gravity and yVelocity
		float ratio = (game->GetGameTime() / 16.7f);
		gravity = 0.08f * ratio;
		yVelocity = 1.4f;
		jump = true;
		PlayJumpAnim();
		dino->sound->Play(false);
	}

	if (y > 0) {
		yVelocity -= gravity;
	}
	else if (y < 0) {
		jump = false;
		yVelocity = 0;
		y = 0;
	}


	y += yVelocity * game->GetGameTime();
	sprite->SetPosition(x, y);

	// Time to spawn objects
	if (spawnCactusDuration >= maxCactusSpawnTime) {
		SpawnCacti();
		spawnCactusDuration = 0;
		int min = (speed >= 3) ? 300 : 1000;
		int max = (speed >= 3) ? min : 4000 - speed * 1000;
		maxCactusSpawnTime = (float)(rand() % (max - min + 1) + min);
	}
	ScorePerDuration(1);

	// Update all objects
	for (Cactus* c : cacti) {
		c->Update(game->GetGameTime());
	}
	for (Cactus* c : cacti) {
		if (c->GetSprite()->GetBoundingBox()->CollideWith(sprite->GetBoundingBox())) {
			GameOver();
		}
	}

	scoreDuration += game->GetGameTime();
	spawnCactusDuration += game->GetGameTime();
	scoreText->SetText(to_string(dino->GetScore()));
}

int lastSpeedIncreaseScore = 0;

void Engine::DinoGameScreen::ScorePerDuration(float seconds) {
	seconds *= 1000;
	if (scoreDuration >= seconds) {
		dino->SetScore(dino->GetScore() + 1);
		scoreDuration = 0;
	}
	if (dino->GetScore() % 10 == 0 && dino->GetScore() > lastSpeedIncreaseScore) {
		speed += speedIncrease;
		//Increase the speed of all cacti in the object pool
		lastSpeedIncreaseScore = dino->GetScore();  // Update the last score when speed increased
		for (Cactus* c : cacti) {
			c->SetXVelocity(c->GetXVelocity() + speedIncrease);
		}
	}
}

void Engine::DinoGameScreen::GameOver() {
	speed = 0.2f;
	for (Cactus* cactus : cacti) {
		float x = game->GetSettings()->screenWidth + cactus->GetWidth();
		float y = 1;
		cactus->SetPosition(x, y);
		cactus->SetXVelocity(speed);
		cactus->SetCactusState(Engine::CactusState::DIE);
	}
	maxCactusSpawnTime = 500;
	numCactusPerSpawn = 1;
	numCactusInPool = 100;
	scoreDuration = 0;
	lastSpeedIncreaseScore = 0;
	if (dino->GetScore() > dino->GetBestScore()) {
		dino->SetBestScore(dino->GetScore());
	}
	dino->SetScore(0);
	DinoGameOverScreen* gameOverScreen = dynamic_cast<DinoGameOverScreen*>(ScreenManager::GetInstance(game)->GetScreen("dinoover"));
	if (gameOverScreen) {
		gameOverScreen->SetBestScoreText();
	}
	ScreenManager::GetInstance(game)->SetCurrentScreen("dinoover");
	return;
}

void Engine::DinoGameScreen::Draw()
{
	DrawLayer(backgrounds);
	DrawLayer(middlegrounds);
	DrawLayer(foregrounds);
	sprite->Draw();
	for (Cactus* c : cacti) {
		c->Draw();
	}
	scoreText->Draw();
}

Engine::Sprite* Engine::DinoGameScreen::CreateCactusSprite()
{
	return (new Sprite(cactus_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetNumXFrames(14)->SetNumYFrames(4)->AddAnimation("hit", 2, 4)->AddAnimation("spikes", 5, 12)->AddAnimation("idle-1", 14, 27)->AddAnimation("idle-2", 28, 41)->AddAnimation("spikes-out", 42, 49)->PlayAnim("idle-1")->SetScale(1.5)->SetAnimationDuration(100)
		->SetBoundingBoxSize(sprite->GetScaleWidth() - (16 * sprite->GetScale()),
		sprite->GetScaleHeight() - (8 * sprite->GetScale()));;
}

void Engine::DinoGameScreen::SpawnCacti()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (Cactus* c : cacti) {
		if (spawnCount == numCactusPerSpawn) {
			break;
		}
		if (c->IsDie()) {
			// Set state to spawn
			c->SetSpawn();
			//// Right spawn position
			//int min = 0;
			//int max = (int)(setting->screenHeight - o->GetHeight());
			float x = game->GetSettings()->screenWidth + c->GetWidth();
			float y = 1;
			c->SetPosition(x, y);
			spawnCount++;
		}
	}
}

void Engine::DinoGameScreen::MoveLayer(vector<Sprite*>& bg, float speed)
{
	for (Sprite* s : bg) {
		if (s->GetPosition().x < - game->GetSettings()->screenWidth + offset) {
			s->SetPosition(game->GetSettings()->screenWidth + offset - 3, 0);
		}
		s->SetPosition(s->GetPosition().x - speed * game->GetGameTime(), s->GetPosition().y);
		s->Update(game->GetGameTime());
	}
}

void Engine::DinoGameScreen::DrawLayer(vector<Sprite*>& bg)
{
	for (Sprite* s : bg) {
		s->Draw();
	}
}

void Engine::DinoGameScreen::AddToLayer(vector<Sprite*>& bg, string name)
{
	Texture* texture = new Texture(name);

	Sprite* s = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s->SetSize(game->GetSettings()->screenWidth + offset, game->GetSettings()->screenHeight);
	bg.push_back(s);

	Sprite* s2 = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s2->SetSize(game->GetSettings()->screenWidth + offset, game->GetSettings()->screenHeight)->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
	bg.push_back(s2);
}

void Engine::DinoGameScreen::PlayJumpAnim()
{
	float duration = 70;
	while (duration >= 0) {
		sprite->PlayAnim("Jump");
		duration--;
	}
}