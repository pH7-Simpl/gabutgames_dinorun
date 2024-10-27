#include "DinoGameOverScreen.h"

Engine::DinoGameOverScreen::DinoGameOverScreen(Dino* dinoInstance) : dino(dinoInstance)
{

}

void Engine::DinoGameOverScreen::Init()
{
	// Create a Texture
	Texture* texture = new Texture("buttons2.png");

	// Create Sprites
	Sprite* retrySprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 9, 9)->AddAnimation("hover", 10, 11)
		->AddAnimation("press", 10, 11)->SetAnimationDuration(400);

	Sprite* mainMenuSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 1, 2)
		->AddAnimation("press", 1, 2)->SetAnimationDuration(400);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 12, 12)->AddAnimation("hover", 13, 14)
		->AddAnimation("press", 13, 14)->SetAnimationDuration(400);

	//Create Buttons
	Button* retryButton = new Button(retrySprite, "retry");
	retryButton->SetPosition((game->GetSettings()->screenWidth / 2) - (retrySprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(retryButton);

	Button* mainMenuButton = new Button(mainMenuSprite, "mainmenu");
	mainMenuButton->SetPosition((game->GetSettings()->screenWidth / 2) - (mainMenuSprite->GetScaleWidth() / 2),
		300);
	buttons.push_back(mainMenuButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		200);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Game Over Text
	gameOverText = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Game Over")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 500, game->GetSettings()->screenHeight - 100.0f)->SetColor(235, 229, 52);

	// Create Game Over Text
	bestScoreText = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Your Best Score is " + to_string(dino->GetBestScore()))->SetPosition(game->GetSettings()->screenWidth * 0.5f - 500, game->GetSettings()->screenHeight - 150.0f)->SetColor(235, 229, 52);

	// Add input mappings
	game->GetInputManager()->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);

}


void Engine::DinoGameOverScreen::Update()
{
	// Set background
	game->SetBackgroundColor(52, 155, 235);

	if (game->GetInputManager()->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("retry" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("dino");
		}
		else if ("mainmenu" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
		}
		else if ("exit" == b->GetButtonName()) {
			game->SetState(Engine::State::EXIT);
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::DinoGameOverScreen::Draw()
{
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	gameOverText->Draw();
	bestScoreText->Draw();
}

void Engine::DinoGameOverScreen::SetBestScoreText() {
	bestScoreText->SetText("Your Best Score is " + to_string(dino->GetBestScore()));
}